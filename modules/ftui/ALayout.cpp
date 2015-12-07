// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ALayout.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 15:46:29 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ALayout.hpp"
#include "ftui/Activity.hpp"
#include "ft_xml/XmlParser.hpp"
#include "ftui/IViewHolder.hpp"
#include "ft/utils.hpp"

#include <algorithm>

using std::string;

namespace ftui
{

ALayout::ALayout(Activity &act, std::string const &viewName) :
	ASolidView(act, viewName)
{
}


ALayout::~ALayout(void)
{
}

void				ALayout::queryUpdate(void)
{
	AView::queryUpdate();
	for (int i = 0; i < size(); i++)
		at(i)->queryUpdate();
}

void				ALayout::queryMeasure(void)
{
	AView::queryMeasure();
	for (int i = 0; i < size(); i++)
		at(i)->queryMeasure();
}

void				ALayout::queryRedraw(void)
{
	AView::queryRedraw();
	for (int i = 0; i < size(); i++)
		at(i)->queryRedraw();
}

void				ALayout::spreadTargetMouseScroll(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_SCROLL_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_SCROLL_TARGET;
		else
		{
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseScrollTargeted())
					return ;
			this->_layoutFlags &= ~AView::MOUSE_SCROLL_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseScroll(state);
	}
	return ;
}

void				ALayout::spreadTargetMouseClick(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_CLICK_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_CLICK_TARGET;
		else
		{
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseClickTargeted())
					return ;
			this->_layoutFlags &= ~AView::MOUSE_CLICK_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseClick(state);
	}
	return ;
}

void				ALayout::spreadTargetMouseMove(bool state)
{
	ALayout			*p;

	// FTPADB("%", (_id ? *_id : "noname"));
	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_MOVE_TARGET)
		!= state)
	{
		// FTPAD("ENTERING");
		if (state)
			this->_layoutFlags |= AView::MOUSE_MOVE_TARGET;
		else
		{
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseMoveTargeted())
				// {
					// FTPADE();
					return ;
				// }
			this->_layoutFlags &= ~AView::MOUSE_MOVE_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseMove(state);
	}
	// FTPADE();
	return ;
}

void				ALayout::spreadTargetMouseCapture(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::MOUSE_CAPTURE_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::MOUSE_CAPTURE_TARGET;
		else
		{
			for (int i = 0; i < size(); i++)
				if (at(i)->isMouseCaptureTargeted())
					return ;
			this->_layoutFlags &= ~AView::MOUSE_CAPTURE_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetMouseCapture(state);
	}
	return ;
}

void				ALayout::spreadTargetKeyboard(bool state)
{
	ALayout			*p;

	if (static_cast<bool>(this->_layoutFlags & AView::KEYBOARD_TARGET)
		!= state)
	{
		if (state)
			this->_layoutFlags |= AView::KEYBOARD_TARGET;
		else
		{
			for (int i = 0; i < size(); i++)
				if (at(i)->isKeyboardTargeted())
					return ;
			this->_layoutFlags &= ~AView::KEYBOARD_TARGET;
		}
		p = this->getParent();
		if (p != nullptr)
			p->spreadTargetKeyboard(state);
	}

	return ;
}

void				ALayout::spreadQueryUpdate(void)
{
	_layoutFlags |= AView::UPDATE_QUERY;
	if (getParent() != nullptr)
		getParent()->spreadQueryUpdate();
}

void				ALayout::spreadQueryMeasure(void)
{
	_layoutFlags |= AView::MEASURE_QUERY;
	if (getParent() != nullptr)
		getParent()->spreadQueryMeasure();
}

void				ALayout::spreadQueryRedraw(void)
{
	_layoutFlags |= AView::REDRAW_QUERY;
	if (getParent() != nullptr)
		getParent()->spreadQueryRedraw();
}


/*
** * AView legacy *********************************************************** **
*/

void				ALayout::inflate(ViewTemplate const &t,
						ParamMap const *parent_map)
{
	AView				*view;

	inflateParams(t.getParams(), parent_map);
	for (ViewTemplate const *child : t.getChilds())
	{
		view = Activity::getFactory(child->getName())(_act);
		addView(view);
		view->inflate(*child, parent_map);
	}
}

void				ALayout::inflate(ft::XmlParser &xml,
						ParamMap const *parent_map)
{
	AView					*v;
	ft::XmlParser::State	state;
	param_map_t				params_save(xml.getParams());
	ParamMap				param_map(params_save, parent_map);

	inflateParams(param_map.params, parent_map);
	while (xml.next(state))
	{
		if (state == ft::XmlParser::State::START)
		{
			v = Activity::getFactory(xml.getMarkupName())(_act);
			this->addView(v);
			v->inflate(xml, &param_map);
		}
		else if (state == ft::XmlParser::State::END)
			return ;
		else
			break ;
	}
	FTASSERT(false, "Should not be reached");
}

bool				ALayout::onMouseScroll(int x, int y, float delta)
{
	AView			*v;
	IViewHolder		*holder;
	ft::Vec2<int>	pos;

	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		holder = v->getViewHolder();
		pos = holder->getPos();
		FTASSERT(v != nullptr);
		if (v->isMouseScrollTargeted() && (ft::make_rect(pos, holder->getSize())
				.contains(ft::make_vec(x, y)) || v->isMouseCaptureTargeted())
			&& v->onMouseScroll(x - pos.x, y - pos.y, delta))
			return (true);
	}
	if (AView::isMouseScrollTargeted())
		return (AView::onMouseScroll(x, y, delta));
	return (false);
}

bool				ALayout::onMouseDown(int x, int y, int button, int mods)
{
	AView			*v;
	IViewHolder		*holder;
	ft::Vec2<int>	pos;

	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		holder = v->getViewHolder();
		pos = holder->getPos();
		FTASSERT(v != nullptr);
		if (v->isMouseClickTargeted() && (ft::make_rect(pos, holder->getSize())
				.contains(ft::make_vec(x, y)) || v->isMouseCaptureTargeted())
			&& v->onMouseDown(x - pos.x, y - pos.y, button, mods))
			return (true);
	}
	if (AView::isMouseClickTargeted())
		return (AView::onMouseDown(x, y, button, mods));
	return (false);
}

bool				ALayout::onMouseUp(int x, int y, int button, int mods)
{
	AView			*v;
	IViewHolder		*holder;
	ft::Vec2<int>	pos;

	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		holder = v->getViewHolder();
		pos = holder->getPos();
		FTASSERT(v != nullptr);
		if (v->isMouseClickTargeted() && (ft::make_rect(pos, holder->getSize())
				.contains(ft::make_vec(x, y)) || v->isMouseCaptureTargeted())
			&& v->onMouseUp(x - pos.x, y - pos.y, button, mods))
			return (true);
	}
	if (AView::isMouseClickTargeted())
		return (AView::onMouseUp(x, y, button, mods));
	return (false);
}

bool				ALayout::onMouseMove(int x, int y)
{
	IViewHolder		*vh;
	AView			*v;

	for (int i = 0; i < size(); i++)
	{
		vh = this->holderAt(i);
		v = vh->getView();
		if (v->isMouseMoveTargeted())
		{
			FTASSERT(vh != nullptr);
			if (ft::Rect<int>{vh->getPos(), vh->getSize()}.contains(
					ft::Vec2<int>{x, y}))
			{
				if (!v->isMouseOver())
					v->setMouseOver(x, y, true);
			}
			else
			{
				if (v->isMouseOver())
					v->setMouseOver(x, y, false);
			}
			if ((v->isMouseOver() || v->isMouseCaptureTargeted())
				&& v->onMouseMove(x - vh->getPos().x, y - vh->getPos().y))
				return (true);
		}
	}
	if (AView::isMouseMoveTargeted())
		return (AView::onMouseMove(x, y));
	return (false);
}

bool				ALayout::onKeyDown(int key_code, int mods)
{
	AView		*v;

	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isKeyboardTargeted() && v->onKeyDown(key_code, mods))
			return (true);
	}
	if (AView::isKeyboardTargeted())
		return (AView::onKeyDown(key_code, mods));
	return (false);
}

bool				ALayout::onKeyUp(int key_code, int mods)
{
	AView		*v;

	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isKeyboardTargeted() && v->onKeyUp(key_code, mods))
			return (true);
	}
	if (AView::isKeyboardTargeted())
		return (AView::onKeyUp(key_code, mods));
	return (false);
}

void				ALayout::onMouseLeave(int x, int y)
{
	AView		*v;

	AView::onMouseLeave(x, y);
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		if (v->isMouseOver())
			v->setMouseOver(x, y, false);
	}
	return ;
}

void				ALayout::onAttach(void)
{
	AView		*v;

	AView::onAttach();
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		FTASSERT(!v->isAttached());
		v->setAttached(true);
	}
	return ;
}
void				ALayout::onDetach(void)
{
	AView		*v;

	AView::onDetach();
	for (int i = 0; i < size(); i++)
	{
		v = at(i);
		FTASSERT(v != nullptr);
		FTASSERT(v->isAttached());
		v->setAttached(false);
	}
	return ;
}


bool				ALayout::isMouseScrollTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_SCROLL_TARGET)
			|| AView::isMouseScrollTargeted());
}

bool				ALayout::isMouseClickTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_CLICK_TARGET)
			|| AView::isMouseClickTargeted());
}

bool				ALayout::isMouseMoveTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_MOVE_TARGET)
			|| AView::isMouseMoveTargeted());
}

bool				ALayout::isMouseCaptureTargeted(void) const
{
	return ((this->_layoutFlags & AView::MOUSE_CAPTURE_TARGET)
			|| AView::isMouseCaptureTargeted());
}

bool				ALayout::isKeyboardTargeted(void) const
{
	return ((this->_layoutFlags & AView::KEYBOARD_TARGET)
			|| AView::isKeyboardTargeted());
}

bool				ALayout::isUpdateQueried(void) const
{
	return ((_layoutFlags & AView::UPDATE_QUERY)
			|| AView::isUpdateQueried());
}

bool				ALayout::isMeasureQueried(void) const
{
	return ((_layoutFlags & AView::MEASURE_QUERY)
			|| AView::isMeasureQueried());
}

bool				ALayout::isRedrawQueried(void) const
{
	return ((_layoutFlags & AView::REDRAW_QUERY)
			|| AView::isRedrawQueried());
}

};
