/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout_ViewHolder.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/25 10:11:27 by ngoguey           #+#    #+#             */
/*   Updated: 2015/10/02 10:25:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui/VerticalLayout.hpp"
#include "ftui/XmlParser.hpp"

#include "ftui/Activity.hpp"

namespace ftui
{

VerticalLayout::ViewHolder::ViewHolder(VerticalLayout *p, AView *v)
	: _view(v), _parent(p)
{
}

VerticalLayout::ViewHolder::~ViewHolder(void)
{
}

Vec2<int>		VerticalLayout::ViewHolder::getPos(void) const
{
	return (_pos);
}

Vec2<int>		VerticalLayout::ViewHolder::getSize(void) const
{
	return (_size);
}

Vec2<int>		VerticalLayout::ViewHolder::getRequestedSize(void) const
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

void			VerticalLayout::ViewHolder::setSize(Vec2<int> size)
{
	if (_size == size)
		return ;
	_size = size;
	_view->onSizeChange();
}

void			VerticalLayout::ViewHolder::setRequestedSize(Vec2<int> size)
{
	_requestedSize = size;
}

Vec2<int>		VerticalLayout::ViewHolder::getVerticalMargin(void) const
{
	return (_verticalMargin);
}

VerticalLayout::Align	VerticalLayout::ViewHolder::getHorizontalAlign(void) const
{
	return (_horizontalAlign);
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
