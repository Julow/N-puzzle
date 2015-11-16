// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VerticalLayout.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/16 15:16:51 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/VerticalLayout.hpp"
#include "ftui/Canvas.hpp"
#include "ft_xml/XmlParser.hpp"
#include "ft/utils.hpp"

#include <algorithm>
#include <iostream>

namespace ftui
{

VerticalLayout::VerticalLayout(ft::XmlParser const &xml, Activity &act)
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

void            VerticalLayout::inflate(ft::XmlParser &xml, Activity &a)
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
	ft::Vec2<int>		hm;

	for (ViewHolder *h : _childs)
	{
		childPosX = h->getPos().x;
		childSize = h->getRequestedSize();
		hm = h->getHorizontalMargin();
		if (childSize.x + hm.x + hm.y > layoutSize.x)
			childSize.x = layoutSize.x - hm.x - hm.y;
		switch (h->getHorizontalAlign())
		{
		case Align::LEFT:
			childPosX = hm.x;
			break ;
		case Align::CENTER:
			childPosX = (layoutSize.x - childSize.x + hm.x - hm.y) / 2;
			break ;
		case Align::RIGHT:
			childPosX = layoutSize.x - childSize.x - hm.y;
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
	ft::Vec2<int>	vm;
	ft::Vec2<int>	hm;
	int				width;
	int				offsetTop = 0;
	int				maxWidth = 0;

	AView::onMeasure();
	for (ViewHolder *h : _childs)
	{
		h->getView()->onMeasure();
		requestedSize = h->getRequestedSize();
		hm = h->getHorizontalMargin();
		width = requestedSize.x + hm.x + hm.y;
		if (width > maxWidth)
			maxWidth = width;
		vm = h->getVerticalMargin();
		offsetTop += vm.x;
		h->setPosY(offsetTop);
		offsetTop += vm.y;
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
		}
		// ft::f(std::cout, "clip: %  (%)\n", clip, ft::make_rect(vh->getPos(), vh->getSize()));
	}
	return clip;
}

void			VerticalLayout::onDraw(Canvas &canvas)
{
	float const			oldAlpha = canvas.getAlpha();
	ft::Vec2<int> const	oldOrigin = canvas.getOrigin();
	auto				redrawChild =
		[=, &canvas](AView *v, ft::Vec2<int> pos, ft::Vec2<int> size)
	{
		canvas.applyAlpha(v->getAlpha());
		canvas.applyOrigin(pos);
		canvas.setClip(size);
		v->onDraw(canvas);
		canvas.setOrigin(oldOrigin);
		canvas.setAlpha(oldAlpha);
		return ;
	};
	ft::Rect<int>		redrawClip;
	ft::Rect<int>		bounds;
	AView				*v;

	// canvas.setClip(redrawClip);
	// ASolidView::onDraw(canvas);
	// canvas.setClip(old_clip);
	FTPADB("% GV(%%)", this->tostring()
		   , isRedrawQueried(), AView::isRedrawQueried());
	if (AView::isRedrawQueried())
	{
		ASolidView::onDraw(canvas);
		_layoutFlags &= ~AView::REDRAW_QUERY;
		for (ViewHolder *vh : _childs)
		{
			redrawChild(vh->getView(), vh->getPos(), vh->getSize());
		}
	}
	else if (_layoutFlags & AView::REDRAW_QUERY)
	{
		redrawClip = calc_redraw_clip(_childs);
		for (ViewHolder *vh : _childs)
		{
			v = vh->getView();
			bounds = ft::make_rect(vh->getPos(), vh->getSize());
            FTPAD("% GVClip(%%%)",
				  v->tostring()
				  , v->isRedrawQueried()
				  , v->AView::isRedrawQueried()
				  , redrawClip.collides(bounds)
				);
			if (v->isRedrawQueried() || redrawClip.collides(bounds))
				redrawChild(v, bounds.getPos(), bounds.getSize());
		}
		_layoutFlags &= ~AView::REDRAW_QUERY;
	}
	FTPADE();
	return ;
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
AView			*VerticalLayout::createView(ft::XmlParser const &xml, Activity &act)
{
	return (new VerticalLayout(xml, act));
}

};
