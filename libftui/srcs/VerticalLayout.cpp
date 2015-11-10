// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VerticalLayout.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/10 14:09:23 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/VerticalLayout.hpp"
#include "ftui/Canvas.hpp"
#include "ftui/XmlParser.hpp"
#include "ft/utils.hpp"

#include <algorithm>
#include <iostream>

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
	_layoutFlags &= ~AView::UPDATE_QUERY;
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
	ft::Vec2<int> const	layoutSize = _holder->getSize();
	int					childPosX;
	ft::Vec2<int>		childSize;

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
	_holder->setRequestedSize(ft::make_vec(maxWidth, offsetTop));
	alignChilds();
	_layoutFlags &= ~AView::MEASURE_QUERY;
}

/*
** onSizeChange
*/
void			VerticalLayout::onSizeChange(void)
{
	AView::onSizeChange();
	alignChilds();
}


/*
** onDraw
*/
static ft::Rect<int>	calc_redraw_clip(
	VerticalLayout::child_container_t &childs)
{
	ft::Rect<int>	clip(0, 0, 0, 0);

	for (VerticalLayout::ViewHolder *vh : childs)
	{
		if (vh->getView()->isRedrawQueried())
		{
			if (clip.getWidth() == 0 || clip.getHeight() == 0)
				clip = ft::make_rect(vh->getPos(), vh->getSize());
			else
				clip.merge(ft::make_rect(vh->getPos(), vh->getSize()));
			ft::f(std::cout, "clip: %\n", clip);
		}
	}
	return clip;
}

//TODO: check, i nuked the previous definition
void			VerticalLayout::onDraw(Canvas &canvas)
{
	float const			oldAlpha = canvas.getAlpha();
	ft::Rect<int> const	oldClip = canvas.getClip();
	auto				redrawChild =
		[=, &canvas](AView *v, ft::Rect<int> const &clip)
	{
		canvas.applyAlpha(v->getAlpha());
		canvas.applyClip(clip);
		v->onDraw(canvas);
		canvas.setClip(oldClip);
		canvas.setAlpha(oldAlpha);
		return ;
	};
	ft::Rect<int>		redrawClip;
	ft::Rect<int>		clip;
	AView				*v;

	// TODO: Canvas::setOrigin
	// canvas.setClip(redrawClip);
	// ASolidView::onDraw(canvas);
	// canvas.setClip(old_clip);
	ft::f(std::cout, "Redraw VerticalLayout:(%) isselfreq(%) ischildreq(%)\n"
		  , (_id ? *_id : "noname")
		  , AView::isRedrawQueried()
		  , (_layoutFlags & AView::REDRAW_QUERY)
		);
	if (AView::isRedrawQueried())
	{
		ASolidView::onDraw(canvas);
		_layoutFlags &= ~AView::REDRAW_QUERY;
		for (ViewHolder *vh : _childs)
			redrawChild(
				vh->getView(), ft::make_rect(vh->getPos(), vh->getSize()));
	}
	else if (_layoutFlags & AView::REDRAW_QUERY)
	{
		redrawClip = calc_redraw_clip(_childs);
		for (ViewHolder *vh : _childs)
		{
			v = vh->getView();
			clip = ft::make_rect(vh->getPos(), vh->getSize());
			ft::f(std::cout, "%  query(%)  collide(%)\n"
				  , (v->getId() ? *v->getId() : "noname")
				  , v->isRedrawQueried()
				  , redrawClip.collides(clip)
				);
			if (v->isRedrawQueried() || redrawClip.collides(clip))
				redrawChild(v, clip);
		}
		_layoutFlags &= ~AView::REDRAW_QUERY;
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
	if (holder == nullptr
		|| (it = std::find(_childs.begin(), _childs.end(), holder))
			== _childs.end())
		throw std::domain_error(ft::f("Invalid pop view"));
	this->_childs.erase(it);
	delete holder;
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
