// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bookmark.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/15 09:15:02 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/16 15:52:41 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "libftui_extend/Bookmark.hpp"
#include "ftui/Canvas.hpp"
#include "ftui/Button.hpp"

using BM = Bookmark;
using BMVH = Bookmark::ViewHolder;

// ========================================================================== //
// CONSTRUCTION
//

void			BM::declare_libftui(void)
{
	AView::defineView("Bookmark", "AView", &BM::createView);
	return ;
}

ftui::AView		*BM::createView(ftui::XmlParser const &xml, ftui::Activity &act)
{
	return new Bookmark(xml, act);
}

BM::Bookmark(ftui::XmlParser const &xml, ftui::Activity &act)
	: ALayout(xml, act)
	, _text("Hello world")
	, _buttonHolder(nullptr)
{
	ftui::Button		*b = new ftui::Button(act, nullptr);
	this->_buttonHolder	= new BM::ViewHolder(this, b);
	return ;
}

BM::~Bookmark()
{ }

void			BM::setViewHolder(ftui::IViewHolder *holder)
{
	//TODO: onViewHolderChange
	AView::setViewHolder(holder);
	this->_buttonHolder->getView()->setViewHolder(this->_buttonHolder);
	return ;
}

// ========================================================================== //
// DRAW
//

void			BM::onUpdate(void)
{
	return ;
}

void			BM::onMeasure(void)
{
	_holder->setRequestedSize({100, 32});
	return ;
}

void			BM::onDraw(ftui::Canvas &can)
{
	ft::Vec2<int> const	size = this->_holder->getSize();
	ft::Vec2<int> const	tsize = can.measureText(_text, {0, 0, 12, 0});
	float const			oldAlpha = can.getAlpha();
	ft::Vec2<int>		oldOrigin = can.getOrigin();
	ViewHolder *const	bvh = this->_buttonHolder;
	ftui::AView *const	b = bvh->getView();

	can.drawRect({{0, 0}, size}, {0xFFAAAAAA, 0xFF3d3838, 2, 0});
	can.drawText({4, size.y / 2.f - tsize.y / 2}, _text, {0x0, 0xFFAAAAAA, 12, 0});
	AView::onDraw(can);
	can.applyAlpha(b->getAlpha());
	can.applyOrigin(bvh->getPos());
	can.setClip(bvh->getSize());
	b->onDraw(can);
	can.setOrigin(oldOrigin);
	can.setAlpha(oldAlpha);
	return ;
}

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
	FTASSERT(i == 0);
	return this->_buttonHolder->getView();
}

ftui::AView const	*BM::at(int i) const
{
	FTASSERT(i == 0);
	return this->_buttonHolder->getView();
}

int				BM::size(void) const
{
	return 1;
}

ftui::IViewHolder	*BM::holderAt(int i)
{
	FTASSERT(i == 0);
	return this->_buttonHolder;
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
	return {71, 4};
}
ft::Vec2<int>	BMVH::getSize(void) const
{
	return {25, 25};
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
