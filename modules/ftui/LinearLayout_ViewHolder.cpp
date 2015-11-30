// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LinearLayout_ViewHolder.cpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 10:11:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/30 16:32:54 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>

#include "ftui/LinearLayout.hpp"
#include "ft/utils.hpp"

namespace ftui
{

LinearLayout::ViewHolder::ViewHolder(LinearLayout *p, AView *v) :
	_view(v),
	_parent(p),
	_pos(0, 0),
	_size(0, 0),
	_requestedSize(0, 0),
	_margin(0, 0, 0, 0),
	_align(LinearLayout::Align::LEFT),
	_flags(0)
{
}

LinearLayout::ViewHolder::~ViewHolder(void)
{
}

ft::Vec2<int>	LinearLayout::ViewHolder::getPos(void) const
{
	return (_pos);
}

ft::Vec2<int>	LinearLayout::ViewHolder::getSize(void) const
{
	return (_size);
}

ft::Vec2<int>	LinearLayout::ViewHolder::getRequestedSize(void) const
{
	return (_requestedSize);
}

void			LinearLayout::ViewHolder::setPosX(int x)
{
	_pos.x = x;
}

void			LinearLayout::ViewHolder::setPosY(int y)
{
	_pos.y = y;
}

void			LinearLayout::ViewHolder::setPos(ft::Vec2<int> pos)
{
	_pos = pos;
}

void			LinearLayout::ViewHolder::setSize(ft::Vec2<int> size)
{
	if (_size == size)
		return ;
	_size = size;
	_view->onSizeChange(size);
}

uint32_t		LinearLayout::ViewHolder::getFlags(void) const
{
	return (_flags);
}

void			LinearLayout::ViewHolder::setRequestedSize(ft::Vec2<int> size)
{
	if (!(_flags & FIXED_WIDTH))
		_requestedSize.x = size.x;
	if (!(_flags & FIXED_HEIGHT))
		_requestedSize.y = size.y;
}

void			LinearLayout::ViewHolder::setParam(std::string const &k,
						std::string const &v)
{
	static std::unordered_map<std::string, bool (*)(LinearLayout::ViewHolder*,
		std::string const &)> const		param_map
	{
		{"marginTop", [](LinearLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_margin.top = atoi(v.c_str());
			return (true);
		}},
		{"marginBottom", [](LinearLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_margin.bottom = atoi(v.c_str());
			return (true);
		}},
		{"marginLeft", [](LinearLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_margin.left = atoi(v.c_str());
			return (true);
		}},
		{"marginRight", [](LinearLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_margin.right = atoi(v.c_str());
			return (true);
		}},
		{"align", [](LinearLayout::ViewHolder *holder, std::string const &v)
		{
			if (v == "LEFT" || v == "TOP")
				holder->setAlign(LinearLayout::Align::LEFT);
			else if (v == "CENTER")
				holder->setAlign(LinearLayout::Align::CENTER);
			else if (v == "RIGHT" || v == "BOTTOM")
				holder->setAlign(LinearLayout::Align::RIGHT);
			else
				return (false);
			return (true);
		}},
		{"width", [](LinearLayout::ViewHolder *holder, std::string const &v)
		{
			holder->_flags |= FIXED_WIDTH;
			holder->_requestedSize.x = atoi(v.c_str());
			return (true);
		}},
		{"height", [](LinearLayout::ViewHolder *holder, std::string const &v)
		{
			holder->_flags |= FIXED_HEIGHT;
			holder->_requestedSize.y = atoi(v.c_str());
			return (true);
		}},
	};
	auto const		&it = param_map.find(k);

	if (it != param_map.end() && !it->second(this, v))
		throw std::domain_error(ft::f("LinearLayout::ViewHolder::setParam: "
			"Invalid param: %=\"%\"", k, v));
	return ;
}

ft::Rect<int> const		&LinearLayout::ViewHolder::getMargin(void) const
{
	return (_margin);
}

void					LinearLayout::ViewHolder::setMargin(
							ft::Rect<int> const &margin)
{
	_margin = margin;
}

LinearLayout::Align		LinearLayout::ViewHolder::getAlign(void) const
{
	return (_align);
}

void					LinearLayout::ViewHolder::setAlign(
							LinearLayout::Align align)
{
	_align = align;
}

AView					*LinearLayout::ViewHolder::getView(void)
{
	return (this->_view);
}

AView const				*LinearLayout::ViewHolder::getView(void) const
{
	return (this->_view);
}

ALayout					*LinearLayout::ViewHolder::getParent(void)
{
	return (this->_parent);
}

ALayout const			*LinearLayout::ViewHolder::getParent(void) const
{
	return (this->_parent);
}

};
