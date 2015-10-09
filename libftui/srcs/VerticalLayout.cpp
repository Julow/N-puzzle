// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VerticalLayout.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/09 14:56:18 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/VerticalLayout.hpp"
#include "ftui/Canvas.hpp"
#include "ftui/XmlParser.hpp"
#include "ft/utils.hpp"

#include <algorithm>
#include <iostream> //lol

namespace ftui
{

VerticalLayout::VerticalLayout(XmlParser const &xml, Activity &act)
	: ALayout(xml, act)
{
}

VerticalLayout::~VerticalLayout(void)
{
}

void			VerticalLayout::onUpdate(void)
{
	AView::onUpdate();
	for (ViewHolder *h : _childs)
	{
		if (h->getView()->isUpdateQueried())
			h->getView()->onUpdate();
	}
	std::cout << "VerticalLayout onUpdate " << (void*)this << std::endl; //lol
}

void            VerticalLayout::inflate(XmlParser &xml, Activity &a)
{
	ALayout::inflate(xml, a);
	return ;
}

/*
** Align childs horizontally and lock their size
*/
void			VerticalLayout::alignChilds(void)
{
	ft::Vec2<int>	layoutSize = _holder->getSize();
	int				childPosX;
	ft::Vec2<int>	childSize;

	for (ViewHolder *h : _childs)
	{
		childPosX = h->getPos().x;
		childSize = h->getRequestedSize();
		if (childSize.x > layoutSize.x)
			childSize.x = layoutSize.x;
		switch (h->getHorizontalAlign())
		{
		case Align::LEFT:
			childPosX = 0;
			break ;
		case Align::CENTER:
			childPosX = (layoutSize.x - childSize.x) / 2;
			break ;
		case Align::RIGHT:
			childPosX = layoutSize.x - childSize.x;
			break ;
		}
		h->setPosX(childPosX);
		h->setSize(childSize);
	}
}

/*
** onMeasure
** -
** Place childs vertically
*/
void			VerticalLayout::onMeasure(void)
{
	ft::Vec2<int>	requestedSize;
	int				offsetTop = 0;
	int				maxWidth = 0;

	AView::onMeasure();
	for (ViewHolder *h : _childs)
	{
		h->getView()->onMeasure();
		requestedSize = h->getRequestedSize();
		if (requestedSize.x > maxWidth)
			maxWidth = requestedSize.x;
		offsetTop += h->getVerticalMargin().x;
		h->setPosY(offsetTop);
		offsetTop += h->getVerticalMargin().y;
		offsetTop += requestedSize.y;
	}
	_holder->setRequestedSize(ft::Vec2<int>(maxWidth, offsetTop));
	alignChilds();
}

/*
** onSizeChange
*/
void			VerticalLayout::onSizeChange(void)
{
	AView::onSizeChange();
	alignChilds();
}

void			VerticalLayout::onDraw(Canvas &canvas)
{
	float const			old_alpha = canvas.getAlpha();
	ft::Rect<int> const	old_clip = canvas.getClip();

	AView::onDraw(canvas);
	for (ViewHolder *h : _childs)
	{
		if (h->getView()->isRedrawQueried())
		{
			canvas.applyAlpha(h->getView()->getAlpha());
			canvas.applyClip(ft::Rect<int>(h->getPos(), h->getSize()));
			h->getView()->onDraw(canvas);
			canvas.setClip(old_clip);
			canvas.setAlpha(old_alpha);
		}
	}
}

/*
** Add a view
** If the view already has a parent, throw
*/
void			VerticalLayout::addView(AView *view)
{
	ViewHolder		*holder;
	
	if (view->getViewHolder() != NULL)
		throw std::invalid_argument(ft::f("View (#%) already has a parent",
		view->getViewHolder()->getParent()));
	holder = new ViewHolder(this, view);
	view->setViewHolder(holder);
	_childs.push_back(holder);
	view->queryUpdate();
	view->queryMeasure();
	view->queryRedraw();
}

AView			*VerticalLayout::popView(AView *view)
{
	ViewHolder					*holder;
	child_container_t::iterator	it;

	holder = dynamic_cast<ViewHolder*>(view->getViewHolder());
	if (holder == nullptr)
		; // TODO THROW
	it = std::find(this->_childs.begin(), this->_childs.end(), holder);
	if (it == this->_childs.end())
		; // TODO THROW
	this->_childs.erase(it);
	delete (holder);
	view->setViewHolder(nullptr);
	return (view);
}

AView			*VerticalLayout::at(int i)
{
	return (_childs[i]->getView());
}

AView const		*VerticalLayout::at(int i) const
{
	return (_childs[i]->getView());
}

int				VerticalLayout::size(void) const
{
	return (_childs.size());
}

IViewHolder		*VerticalLayout::holderAt(int i)
{
	return (_childs[i]);
}

/*
** Static
*/
AView			*VerticalLayout::createView(XmlParser const &xml, Activity &act)
{
	return (new VerticalLayout(xml, act));
}

};
