// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ScrollableLayout.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/26 16:08:13 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/26 17:23:12 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/ScrollableLayout.hpp"

namespace ftui
{

AView			*ScrollableLayout::createView(ftui::Activity &act,
					ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return (new ScrollableLayout(act, id));
	return (new ScrollableLayout(act, *xml));
}

ScrollableLayout::ScrollableLayout(Activity &act, ft::XmlParser const &xml) :
	LinearLayout(act, xml),
	_scroll(0)
{
}

ScrollableLayout::ScrollableLayout(Activity &act, std::string const *id,
		std::string const &viewName) :
	LinearLayout(act, id, viewName),
	_scroll(0)
{
}

ScrollableLayout::~ScrollableLayout(void)
{
}

void				ScrollableLayout::onSizeChange(void)
{
	ft::Vec2<int> const	size = _holder->getSize();
	ft::Vec2<int> const	requestedSize = _holder->getRequestedSize();
	int					maxScroll;
	int					scroll;

	if (_direction == Direction::VERTICAL)
		maxScroll = requestedSize.y - size.y;
	else
		maxScroll = requestedSize.x - size.x;
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

void				ScrollableLayout::onDraw(ACanvas &canvas)
{
	LinearLayout::onDraw(canvas);
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

void				ScrollableLayout::setMaxScroll(int maxScroll)
{
	if (maxScroll == _maxScroll)
		return ;
	if (maxScroll < 0)
		maxScroll = 0;
	_maxScroll = maxScroll;
	if (_scroll > maxScroll)
		setScroll(maxScroll);
	onMaxScrollChange(maxScroll);
}

void				ScrollableLayout::onScrollChange(int scroll)
{
	queryMeasure();
	queryRedraw();
	callLuaCallback(_act.getLuaState(),
		static_cast<uint32_t>(LuaCallback::SCROLL_CHANGE), scroll);
	std::cout << "Scroll " << scroll << std::endl;
}

void				ScrollableLayout::onMaxScrollChange(int max)
{
	callLuaCallback(_act.getLuaState(),
		static_cast<uint32_t>(LuaCallback::MAX_SCROLL_CHANGE), max);
}

bool				ScrollableLayout::onMouseScroll(int x, int y, float delta)
{
	int const			oldScroll = _scroll;

	if (LinearLayout::onMouseScroll(x, y, delta))
		return (true);
	setScroll(_scroll + delta);
	if (oldScroll == _scroll)
		return (false);
	return (true);
}

void				ScrollableLayout::onAttach(void)
{
	hookMouseScroll(true);
	ScrollableLayout::onAttach();
}

void				ScrollableLayout::onDetach(void)
{
	hookMouseScroll(false);
	ScrollableLayout::onDetach();
}

int					ScrollableLayout::getScrollG(lua_State *l)
{
	ScrollableLayout *const	self = ftlua::retrieveSelf<ScrollableLayout>(l, -1);

	return (ftlua::push(l, self->getScroll()));
}

int					ScrollableLayout::setScrollG(lua_State *l)
{
	ScrollableLayout *const	self = ftlua::retrieveSelf<ScrollableLayout>(l, -1);

	self->setScroll(luaL_checkinteger(l, 1));
	lua_pop(l, 1);
	return (0);
}

int					ScrollableLayout::getMaxScrollG(lua_State *l)
{
	ScrollableLayout *const	self = ftlua::retrieveSelf<ScrollableLayout>(l, -1);

	return (ftlua::push(l, self->getMaxScroll()));
}

};
