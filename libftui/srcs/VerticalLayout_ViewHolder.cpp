// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VerticalLayout_ViewHolder.cpp                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 10:11:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/09 14:56:40 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>

#include "ft/utils.hpp"
#include "ftui/VerticalLayout.hpp"
#include "ftui/XmlParser.hpp"
#include "ftui/Activity.hpp"

namespace ftui
{

VerticalLayout::ViewHolder::ViewHolder(VerticalLayout *p, AView *v) :
	_view(v),
	_parent(p),
	_pos(0, 0),
	_size(0, 0),
	_requestedSize(0, 0),
	_verticalMargin(0, 0),
	_horizontalAlign(VerticalLayout::Align::LEFT)
{
}

VerticalLayout::ViewHolder::~ViewHolder(void)
{
}

ft::Vec2<int>	VerticalLayout::ViewHolder::getPos(void) const
{
	return (_pos);
}

ft::Vec2<int>	VerticalLayout::ViewHolder::getSize(void) const
{
	return (_size);
}

ft::Vec2<int>	VerticalLayout::ViewHolder::getRequestedSize(void) const
{
	return (_requestedSize);
}

void			VerticalLayout::ViewHolder::setPosX(int x)
{
	_pos.x = x;
}

void			VerticalLayout::ViewHolder::setPosY(int y)
{
	_pos.y = y;
}

void			VerticalLayout::ViewHolder::setSize(ft::Vec2<int> size)
{
	if (_size == size)
		return ;
	_size = size;
	_view->onSizeChange();
}

void			VerticalLayout::ViewHolder::setRequestedSize(ft::Vec2<int> size)
{
	_requestedSize = size;
}

void			VerticalLayout::ViewHolder::setParam(std::string const &k,
						std::string const &v)
{
	static std::unordered_map<std::string, void (*)(VerticalLayout::ViewHolder*,
		std::string const &)> const		param_map
	{
		{"marginTop", [](VerticalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_verticalMargin.x = atoi(v.c_str());
		}},
		{"marginBottom", [](VerticalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_verticalMargin.y = atoi(v.c_str());
		}},
		{"verticalAlign", [](VerticalLayout::ViewHolder *holder,
			std::string const &v)
		{
			if (v == "LEFT")
				holder->setHorizontalAlign(VerticalLayout::Align::LEFT);
			else if (v == "CENTER")
				holder->setHorizontalAlign(VerticalLayout::Align::CENTER);
			else if (v == "RIGHT")
				holder->setHorizontalAlign(VerticalLayout::Align::RIGHT);
			else
				throw std::domain_error(ft::f("Invalid param: "
					"verticalAlign=\"%\"", v));
		}},
		{"width", [](VerticalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_requestedSize.x = atoi(v.c_str());
		}},
		{"height", [](VerticalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_requestedSize.y = atoi(v.c_str());
		}},
	};
	auto const	&it = param_map.find(k);
	if (it != param_map.end())
		it->second(this, v);
	return ;
}

ft::Vec2<int>	VerticalLayout::ViewHolder::getVerticalMargin(void) const
{
	return (_verticalMargin);
}

void			VerticalLayout::ViewHolder::setVerticalMargin(ft::Vec2<int> margin)
{
	_verticalMargin = margin;
}

VerticalLayout::Align VerticalLayout::ViewHolder::getHorizontalAlign(void) const
{
	return (_horizontalAlign);
}

void		 VerticalLayout::ViewHolder::setHorizontalAlign(VerticalLayout::Align align)
{
	_horizontalAlign = align;
}

AView			*VerticalLayout::ViewHolder::getView(void)
{
	return (this->_view);
}

AView const		*VerticalLayout::ViewHolder::getView(void) const
{
	return (this->_view);
}

ALayout			*VerticalLayout::ViewHolder::getParent(void)
{
	return (this->_parent);
}

ALayout const	*VerticalLayout::ViewHolder::getParent(void) const
{
	return (this->_parent);
}

};
