// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HorizontalLayout.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:13:47 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/24 11:15:00 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/HorizontalLayout.hpp"
#include "ftui/ACanvas.hpp"
#include "ft_xml/XmlParser.hpp"
#include "ft/utils.hpp"

#include <algorithm>

namespace ftui
{

/* ************************************************************************** **
** CONSTRUCTION
*/

AView			*HorizontalLayout::createView(
	ftui::Activity &act, ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return new HorizontalLayout(act, id);
	return new HorizontalLayout(act, *xml);
}

HorizontalLayout::HorizontalLayout(Activity &act, ft::XmlParser const &xml)
	: ALayout(act, xml)
{
}

HorizontalLayout::HorizontalLayout(
	Activity &act, std::string const *id
	, std::string const &viewName /* = "HorizontalLayout" */)
	: ALayout(act, id, viewName)
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
			childSize.y = layoutSize.y - vm.x - vm.y;
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
		h->setSize(childSize);
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
	return (clip);
}

void			HorizontalLayout::onDraw(ACanvas &canvas)
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
	// FTPADB("% GV(%%)", this->tostring()
	// 	   , isRedrawQueried(), AView::isRedrawQueried());
	if (AView::isRedrawQueried())
	{
		ASolidView::onDraw(canvas);
		_layoutFlags &= ~AView::REDRAW_QUERY;
		for (ViewHolder *vh : _childs)
		{
			v = vh->getView();
			if (v->isVisible())
				redrawChild(v, vh->getPos(), vh->getSize());
		}
	}
	else if (_layoutFlags & AView::REDRAW_QUERY)
	{
		redrawClip = calc_redraw_clip(_childs);
		for (ViewHolder *vh : _childs)
		{
			v = vh->getView();
			bounds = ft::make_rect(vh->getPos(), vh->getSize());
			// FTPAD("% GVClip(%%%)",
			// 	  v->tostring()
			// 	  , v->isRedrawQueried()
			// 	  , v->AView::isRedrawQueried()
			// 	  , redrawClip.collides(bounds)
			// 	);
			if (v->isVisible()
				&& (v->isRedrawQueried() || redrawClip.collides(bounds)))
				redrawChild(v, bounds.getPos(), bounds.getSize());
		}
		_layoutFlags &= ~AView::REDRAW_QUERY;
	}
	// FTPADE();
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

};
