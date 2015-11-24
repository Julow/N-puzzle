// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HorizontalLayout_ViewHolder.cpp                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 10:11:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 11:05:28 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>

#include "ft/utils.hpp"
#include "ftui/HorizontalLayout.hpp"
#include "ft_xml/XmlParser.hpp"
#include "ftui/Activity.hpp"

namespace ftui
{

HorizontalLayout::ViewHolder::ViewHolder(HorizontalLayout *p, AView *v) :
	_view(v),
	_parent(p),
	_pos(0, 0),
	_size(0, 0),
	_requestedSize(0, 0),
	_horizontalMargin(0, 0),
	_verticalMargin(0, 0),
	_verticalAlign(HorizontalLayout::Align::MIDDLE)
{
}

HorizontalLayout::ViewHolder::~ViewHolder(void)
{
}

ft::Vec2<int>	HorizontalLayout::ViewHolder::getPos(void) const
{
	return (_pos);
}

ft::Vec2<int>	HorizontalLayout::ViewHolder::getSize(void) const
{
	return (_size);
}

ft::Vec2<int>	HorizontalLayout::ViewHolder::getRequestedSize(void) const
{
	return (_requestedSize);
}

void			HorizontalLayout::ViewHolder::setPosX(int x)
{
	_pos.x = x;
}

void			HorizontalLayout::ViewHolder::setPosY(int y)
{
	_pos.y = y;
}

void			HorizontalLayout::ViewHolder::setSize(ft::Vec2<int> size)
{
	if (_size == size)
		return ;
	_size = size;
	_view->onSizeChange();
}

void			HorizontalLayout::ViewHolder::setRequestedSize(ft::Vec2<int> size)
{
	_requestedSize = size;
}

void			HorizontalLayout::ViewHolder::setParam(std::string const &k,
						std::string const &v)
{
	static std::unordered_map<std::string, void (*)(HorizontalLayout::ViewHolder*,
		std::string const &)> const		param_map
	{
		{"marginTop", [](HorizontalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_verticalMargin.x = atoi(v.c_str());
		}},
		{"marginBottom", [](HorizontalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_verticalMargin.y = atoi(v.c_str());
		}},
		{"marginLeft", [](HorizontalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_horizontalMargin.x = atoi(v.c_str());
		}},
		{"marginRight", [](HorizontalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_horizontalMargin.y = atoi(v.c_str());
		}},
		{"verticalAlign", [](HorizontalLayout::ViewHolder *holder,
			std::string const &v)
		{
			if (v == "TOP")
				holder->setVerticalAlign(HorizontalLayout::Align::TOP);
			else if (v == "MIDDLE")
				holder->setVerticalAlign(HorizontalLayout::Align::MIDDLE);
			else if (v == "BOTTOM")
				holder->setVerticalAlign(HorizontalLayout::Align::BOTTOM);
			else
				throw std::domain_error(
					ft::f("HorizontalLayout::ViewHolder::setParam: "
						  "Invalid param at horizontalAlign=\"%\"", v));
		}},
		{"width", [](HorizontalLayout::ViewHolder *holder,
			std::string const &v)
		{
			holder->_requestedSize.x = atoi(v.c_str());
		}},
		{"height", [](HorizontalLayout::ViewHolder *holder,
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

ft::Vec2<int>			HorizontalLayout::ViewHolder::getHorizontalMargin(
	void) const
{ return (_horizontalMargin); }

void					HorizontalLayout::ViewHolder::setHorizontalMargin(
	ft::Vec2<int> margin)
{ _horizontalMargin = margin; }

ft::Vec2<int>			HorizontalLayout::ViewHolder::getVerticalMargin(
	void) const
{ return (_verticalMargin); }

void					HorizontalLayout::ViewHolder::setVerticalMargin(
	ft::Vec2<int> margin)
{ _verticalMargin = margin;}

HorizontalLayout::Align	HorizontalLayout::ViewHolder::getVerticalAlign(
	void) const
{ return (_verticalAlign); }

void					HorizontalLayout::ViewHolder::setVerticalAlign(
	HorizontalLayout::Align align)
{ _verticalAlign = align; }

AView			*HorizontalLayout::ViewHolder::getView(void)
{
	return (this->_view);
}

AView const		*HorizontalLayout::ViewHolder::getView(void) const
{
	return (this->_view);
}

ALayout			*HorizontalLayout::ViewHolder::getParent(void)
{
	return (this->_parent);
}

ALayout const	*HorizontalLayout::ViewHolder::getParent(void) const
{
	return (this->_parent);
}

};
