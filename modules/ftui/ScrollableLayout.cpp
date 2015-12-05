// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ScrollableLayout.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/26 16:08:13 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/05 17:33:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ScrollableLayout.hpp"

namespace ftui
{

AView			*ScrollableLayout::createView(ftui::Activity &act)
{
	return (new ScrollableLayout(act));
}

ScrollableLayout::ScrollableLayout(Activity &act, std::string const &viewName) :
	LinearLayout(act, viewName),
	_scroll(0)
{
}

ScrollableLayout::~ScrollableLayout(void)
{
}

void				ScrollableLayout::onSizeChange(ft::Vec2<int> size)
{
	int					maxScroll;
	int					scroll;

	LinearLayout::onSizeChange(size);
	if (_direction == Direction::VERTICAL)
		maxScroll = _fullSize.y - size.y;
	else
		maxScroll = _fullSize.x - size.x;
	FTASSERT(maxScroll >= 0);
	scroll = _scroll;
	if (maxScroll != _maxScroll)
	{
		_maxScroll = maxScroll;
		if (scroll > maxScroll)
			scroll = maxScroll;
		onMaxScrollChange(maxScroll);
	}
	setScroll(scroll);
}

void				ScrollableLayout::onMeasure(void)
{
	LinearLayout::onMeasure();
}

void				ScrollableLayout::onDraw(ACanvas &canvas)
{
	ft::Vec2<int> const	oldOrigin = canvas.getOrigin();

	canvas.applyOrigin(ft::make_vec(0, -_scroll));
	LinearLayout::onDraw(canvas);
	canvas.setOrigin(oldOrigin);
}

int					ScrollableLayout::getScroll(void) const
{
	return (_scroll);
}

void				ScrollableLayout::setScroll(int scroll)
{
	if (scroll < 0)
		scroll = 0;
	if (scroll > _maxScroll)
		scroll = _maxScroll;
	if (scroll == _scroll)
		return ;
	_scroll = scroll;
	onScrollChange(scroll);
}

int					ScrollableLayout::getMaxScroll(void) const
{
	return (_maxScroll);
}

void				ScrollableLayout::onScrollChange(int scroll)
{
	queryRedraw();
	callLuaCallback(_act.getLuaState(),
		static_cast<uint32_t>(LuaCallback::SCROLL_CHANGE), scroll);
}

void				ScrollableLayout::onMaxScrollChange(int max)
{
	callLuaCallback(_act.getLuaState(),
		static_cast<uint32_t>(LuaCallback::MAX_SCROLL_CHANGE), max);
}

bool				ScrollableLayout::onMouseScroll(int x, int y, float delta)
{
	int const			oldScroll = _scroll;

	if (LinearLayout::onMouseScroll(x, y + _scroll, delta))
		return (true);
	setScroll(_scroll + delta);
	if (oldScroll == _scroll)
		return (false);
	return (true);
}

bool				ScrollableLayout::onMouseDown(int x, int y, int button, int mods)
{
	return (LinearLayout::onMouseDown(x, y + _scroll, button, mods));
}

bool				ScrollableLayout::onMouseUp(int x, int y, int button, int mods)
{
	return (LinearLayout::onMouseUp(x, y + _scroll, button, mods));
}

bool				ScrollableLayout::onMouseMove(int x, int y)
{
	return (LinearLayout::onMouseMove(x, y + _scroll));
}

void				ScrollableLayout::onMouseLeave(int x, int y)
{
	LinearLayout::onMouseLeave(x, y + _scroll);
}

void				ScrollableLayout::onAttach(void)
{
	hookMouseScroll(true);
	LinearLayout::onAttach();
}

void				ScrollableLayout::onDetach(void)
{
	hookMouseScroll(false);
	LinearLayout::onDetach();
}

int					ScrollableLayout::getScrollG(lua_State *l)
{
	ScrollableLayout *const	self = ftlua::pop<ScrollableLayout*>(l, -1);
	// ScrollableLayout *const	self = ftlua::retrieveSelf<ScrollableLayout>(l, -1);

	ftlua::push(l, self->getScroll());
	return 1;
}

int					ScrollableLayout::setScrollG(lua_State *l)
{
	ScrollableLayout *const	self = ftlua::pop<ScrollableLayout*>(l, -1);
	// ScrollableLayout *const	self = ftlua::retrieveSelf<ScrollableLayout>(l, -1);

	self->setScroll(luaL_checkinteger(l, 1));
	lua_pop(l, 1);
	return (0);
}

int					ScrollableLayout::getMaxScrollG(lua_State *l)
{
	ScrollableLayout *const	self = ftlua::pop<ScrollableLayout*>(l, -1);
	// ScrollableLayout *const	self = ftlua::retrieveSelf<ScrollableLayout>(l, -1);

	ftlua::push(l, self->getMaxScroll());
	return 1;
}

};
