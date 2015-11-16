// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HorizontalLayout.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/11 18:52:44 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/HorizontalLayout.hpp"
#include "ftui/Canvas.hpp"
#include "ft_xml/XmlParser.hpp"
#include "ft/utils.hpp"

#include <algorithm>
#include <iostream>

namespace ftui
{

HorizontalLayout::HorizontalLayout(ft::XmlParser const &xml, Activity &act)
	: ALayout(xml, act)
{
}

HorizontalLayout::~HorizontalLayout(void)
{
}

void			HorizontalLayout::onUpdate(void)
{
	AView::onUpdate();
	for (ViewHolder *h : _childs)
	{
		if (h->getView()->isUpdateQueried())
			h->getView()->onUpdate();
	}
	_layoutFlags &= ~AView::UPDATE_QUERY;
}

void            HorizontalLayout::inflate(ft::XmlParser &xml, Activity &a)
{
	ALayout::inflate(xml, a);
	return ;
}

/*
** Align childs vertically and lock their size
*/
void			HorizontalLayout::alignChilds(void)
{
	ft::Vec2<int> const	layoutSize = _holder->getSize();
	int					childPosY;
	ft::Vec2<int>		childSize;
	ft::Vec2<int>		vm;

	for (ViewHolder *h : _childs)
	{
		childPosY = h->getPos().y;
		childSize = h->getRequestedSize();
		vm = h->getVerticalMargin();
		if (childSize.y + vm.x + vm.y > layoutSize.y)
			childSize.y = layoutSize.y;//TODO: why?, de tt facon ca depasse
		switch (h->getVerticalAlign())
		{
		case Align::TOP:
			childPosY = vm.x;
			break ;
		case Align::MIDDLE:
			childPosY = (layoutSize.y - childSize.y + vm.x - vm.y) / 2;
			break ;
		case Align::BOTTOM:
			childPosY = layoutSize.y - childSize.y - vm.y;
			break ;
		}
		h->setPosY(childPosY);
		h->setSize(childSize);//TODO: faut-il verifier que la taille a bien change?
	}
}
/*
** onMeasure
** -
** Place childs horizontally
*/
void			HorizontalLayout::onMeasure(void)
{
	ft::Vec2<int>	requestedSize;
	ft::Vec2<int>	hm;
	ft::Vec2<int>	vm;
	int				height;
	int				offsetLeft = 0;
	int				maxHeight = 0;

	AView::onMeasure();
	for (ViewHolder *h : _childs)
	{
		h->getView()->onMeasure();
		requestedSize = h->getRequestedSize();
		vm = h->getVerticalMargin();
		height = requestedSize.y + vm.x + vm.y;
		if (height > maxHeight)
			maxHeight = height;
		hm = h->getHorizontalMargin();
		offsetLeft += hm.x;
		h->setPosX(offsetLeft);
		offsetLeft += hm.y;
		offsetLeft += requestedSize.x;
	}
	_holder->setRequestedSize(ft::make_vec(offsetLeft, maxHeight));
	alignChilds();
	_layoutFlags &= ~AView::MEASURE_QUERY;
}

/*
** onSizeChange
*/
void			HorizontalLayout::onSizeChange(void)
{
	AView::onSizeChange();
	alignChilds();
}


/*
** onDraw
*/
static ft::Rect<int>	calc_redraw_clip(
	HorizontalLayout::child_container_t &childs)
{
	ft::Rect<int>	clip(0, 0, 0, 0);
	ft::Rect<int>	tmp;

	for (HorizontalLayout::ViewHolder *vh : childs)
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

//TODO: check, i nuked the previous definition
void			HorizontalLayout::onDraw(Canvas &canvas)
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
	FTPADB("% GV(%%)", this->tostring()
		   , isRedrawQueried(), AView::isRedrawQueried());
	if (AView::isRedrawQueried())
	{
		ASolidView::onDraw(canvas);
		_layoutFlags &= ~AView::REDRAW_QUERY;
		for (ViewHolder *vh : _childs)
		{
			redrawChild(
				vh->getView(), ft::make_rect(vh->getPos(), vh->getSize()));
		}
	}
	else if (_layoutFlags & AView::REDRAW_QUERY)
	{
		redrawClip = calc_redraw_clip(_childs);
		for (ViewHolder *vh : _childs)
		{
			v = vh->getView();
			clip = ft::make_rect(vh->getPos(), vh->getSize());
			FTPAD("% GVClip(%%%)",
				  v->tostring()
				  , v->isRedrawQueried()
				  , v->AView::isRedrawQueried()
				  , redrawClip.collides(clip)
				);
			if (v->isRedrawQueried() || redrawClip.collides(clip))
				redrawChild(v, clip);
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
void			HorizontalLayout::addView(AView *view)
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

AView			*HorizontalLayout::popView(AView *view)
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

AView			*HorizontalLayout::at(int i)
{
	return (_childs[i]->getView());
}

AView const		*HorizontalLayout::at(int i) const
{
	return (_childs[i]->getView());
}

int				HorizontalLayout::size(void) const
{
	return (_childs.size());
}

IViewHolder		*HorizontalLayout::holderAt(int i)
{
	return (_childs[i]);
}

/*
** Static
*/
AView			*HorizontalLayout::createView(ft::XmlParser const &xml, Activity &act)
{
	return (new HorizontalLayout(xml, act));
}

};
