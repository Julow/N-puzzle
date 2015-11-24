// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bookmark.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/15 09:15:02 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 11:20:56 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "libftui_extend/Bookmark.hpp"
#include "ftui/ACanvas.hpp"
#include "ftui/Button.hpp"

using BM = Bookmark;
using BMVH = Bookmark::ViewHolder;

#define BM_WIDTHI 140
#define BM_HEIGHTI 32
#define BMTXT_POSXI 4
#define BMDEL_PAD 7

#define BMDEL_WIDTHI (BM_HEIGHTI - BMDEL_PAD * 2)
#define BMDEL_POSYI ((BM_HEIGHTI - BMDEL_WIDTHI) / 2)
#define BMDEL_POSXI (BM_WIDTHI - BMDEL_WIDTHI - BMDEL_PAD)

// ========================================================================== //
// CONSTRUCTION
//

void			BM::declare_libftui(void)
{
	AView::defineView("Bookmark", "AView", &BM::createView);
	return ;
}

ftui::AView		*BM::createView(
	ftui::Activity &act, ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return new Bookmark(act, id);
	return new Bookmark(act, *xml);
}

void			BM::_genSlaveButton(void)
{
	ftui::Button	*del = new ftui::Button(this->_act, nullptr);
	ftui::Button	*sel = new ftui::Button(this->_act, nullptr);

	del->setNormalParams({0xFFFF0000, 0xFFBB0000, 1, 0});
	del->setPushedParams({0xFFFF0000, 0xFFBB0000, 2, 0});
	del->setHighlightParams({0, 0x40FFFF00, 2, 0});
	this->_delHolder = new BM::ViewHolder(this, del);
	this->_delHolder->setSize({BMDEL_WIDTHI, BMDEL_WIDTHI});
	this->_delHolder->setPos({BMDEL_POSXI, BMDEL_POSYI});
	del->setViewHolder(this->_delHolder);

	sel->setNormalParams({0xFFAAAAAA, 0xFF3d3838, 1, 0});
	sel->setPushedParams({0xFFAAAAAA, 0xFF3d3838, 2, 0});
	sel->setHighlightParams({0, 0x10FFFF00, 2, 0});
	this->_selHolder = new BM::ViewHolder(this, sel);
	this->_selHolder->setSize({BM_WIDTHI, BM_HEIGHTI});
	this->_selHolder->setPos({0, 0});
	sel->setViewHolder(this->_selHolder);
	return ;
}

BM::Bookmark(ftui::Activity &act, ft::XmlParser const &xml)
	: ALayout(act, xml)
	, _text("Hello world")
	, _selHolder(nullptr)
	, _delHolder(nullptr)
{
	FTASSERT(false, "This constructor should not be used");
	this->_genSlaveButton();
	return ;
}

BM::Bookmark(ftui::Activity &act, std::string const *id
			 , std::string const &viewName /* = "Bookmark" */)
    : ALayout(act, id, viewName)
	, _text("Hello world")
	, _selHolder(nullptr)
	, _delHolder(nullptr)
{
	this->_genSlaveButton();
	return ;
}

BM::~Bookmark()
{ }

// ========================================================================== //
// DRAW
//

void			BM::onUpdate(void)
{
	return ;
}

void			BM::onMeasure(void)
{
	_holder->setRequestedSize({BM_WIDTHI, BM_HEIGHTI});
	return ;
}

void			BM::onDraw(ftui::ACanvas &can)
{
	FTASSERT(_selHolder != nullptr && _delHolder != nullptr);
	ft::Vec2<int> const	size = this->_holder->getSize();
	ft::Vec2<int> const	tsize = can.measureText(_text, {0, 0, 12, 0});
	ft::Vec2<int> const	oldOrigin = can.getOrigin();
	ViewHolder *const	delVh = this->_delHolder;
	ftui::AView *const	del = delVh->getView();
	ViewHolder *const	selVh = this->_selHolder;
	ftui::AView *const	sel = selVh->getView();

	FTASSERT(sel != nullptr && del != nullptr);
	sel->onDraw(can);
	can.drawText({BMTXT_POSXI, size.y / 2.f - tsize.y / 2},
				 _text, {0x0, 0xFFAAAAAA, 12, 0});
	AView::onDraw(can);
	can.applyOrigin(delVh->getPos());
	can.setClip(delVh->getSize());
	del->onDraw(can);
	can.setOrigin(oldOrigin);
	return ;
}

// void			BM::onAttach(void)
// {
// 	AView::onAttach();
// 	this->_selHolder->getView()->setViewHolder(this->_selHolder);
// 	this->_delHolder->getView()->setViewHolder(this->_delHolder);
// 	return ;
// }

// void			BM::onDetach(void)
// {
// 	this->_selHolder->getView()->setViewHolder(this->_selHolder);
// 	this->_delHolder->getView()->setViewHolder(this->_delHolder);
// 	return ;
// }

// ========================================================================== //
// ALAYOUT LEGACY
//

void			BM::addView(ftui::AView *v)
{
	FTASSERT(false, "Should not be called");
	(void)v;
	return ;
}

ftui::AView		*BM::popView(ftui::AView *v)
{
	FTASSERT(false, "Should not be called");
	(void)v;
	return nullptr;
}

ftui::AView		*BM::at(int i)
{
	FTASSERT(i == 0 || i == 1);
	if (i == 0)
		return this->_selHolder->getView();
	return this->_delHolder->getView();
}

ftui::AView const	*BM::at(int i) const
{
	FTASSERT(i == 0 || i == 1);
	if (i == 0)
		return this->_selHolder->getView();
	return this->_delHolder->getView();
}

int				BM::size(void) const
{
	return 2;
}

ftui::IViewHolder	*BM::holderAt(int i)
{
	FTASSERT(i == 0 || i == 1);
	if (i == 0)
		return this->_selHolder;
	return this->_delHolder;
}

bool				BM::onMouseDown(int x, int y, int button, int mods)
{
	AView	*sel = this->_selHolder->getView();
	AView	*del = this->_delHolder->getView();

	if (del->isMouseCaptureTargeted())
		return del->onMouseDown(x, y, button, mods);
	else if (sel->isMouseCaptureTargeted())
		return sel->onMouseDown(x, y, button, mods);
	else if (del->isMouseOver())
		return del->onMouseDown(x, y, button, mods);
	return sel->onMouseDown(x, y, button, mods);
}
bool				BM::onMouseUp(int x, int y, int button, int mods)
{
	AView	*sel = this->_selHolder->getView();
	AView	*del = this->_delHolder->getView();

	if (del->isMouseCaptureTargeted())
		return del->onMouseUp(x, y, button, mods);
	else if (sel->isMouseCaptureTargeted())
		return sel->onMouseUp(x, y, button, mods);
	else if (del->isMouseOver())
		return del->onMouseUp(x, y, button, mods);
	return sel->onMouseUp(x, y, button, mods);
}

// ========================================================================== //
// HOLDER
//

BMVH::ViewHolder(Bookmark *p, AView *v)
	: _view(v), _parent(p)
{

}
BMVH::~ViewHolder()
{
	return ;
}

ftui::AView		*BMVH::getView(void)
{
	return this->_view;
}

ftui::AView const	*BMVH::getView(void) const
{
	return this->_view;
}

ftui::ALayout	*BMVH::getParent(void)
{
	return this->_parent;
}
ftui::ALayout const	*BMVH::getParent(void) const
{
	return this->_parent;
}

ft::Vec2<int>	BMVH::getPos(void) const
{
	return _pos;
}
ft::Vec2<int>	BMVH::getSize(void) const
{
	return _size;
}

ft::Vec2<int>	BMVH::getRequestedSize(void) const
{
	FTASSERT(false, "Should not be called");
	return {};
}
void			BMVH::setRequestedSize(ft::Vec2<int> size)
{
	FTASSERT(false, "Should not be called");
	(void)size;
	return ;
}

void			BMVH::setParam(std::string const &k,
								std::string const &v)
{
	FTASSERT(false, "Should not be called");
	(void)k;
	(void)v;
	return ;
}

void			BMVH::setSize(ft::Vec2<int> sz)
{ this->_size = sz; }
void			BMVH::setPos(ft::Vec2<int> pos)
{ this->_pos = pos; }
