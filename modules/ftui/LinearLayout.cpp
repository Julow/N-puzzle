// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LinearLayout.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/25 13:23:56 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/05 17:55:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/LinearLayout.hpp"

namespace ftui
{

AView			*LinearLayout::createView(ftui::Activity &act)
{
	return (new LinearLayout(act));
}

LinearLayout::LinearLayout(Activity &act, std::string const &viewName) :
	ALayout(act, viewName),
	_childs(),
	_direction(Direction::VERTICAL),
	_fullSize(0)
{
}

LinearLayout::~LinearLayout(void)
{
}

void			LinearLayout::onUpdate(void)
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
** alignChilds
** -
** Align childs and lock their size
*/
void			LinearLayout::alignChilds(void)
{
	ft::Vec2<int> const	layoutSize = _holder->getSize();
	ft::Vec2<int>		childPos;
	ft::Vec2<int>		childSize;

	for (ViewHolder *h : _childs)
	{
		ft::Rect<int> const	&margin = h->getMargin();

		childPos = h->getPos();
		childSize = h->getRequestedSize();
		if (_direction == Direction::VERTICAL)
		{
			if (childSize.x + margin.left + margin.right > layoutSize.x)
				childSize.x = layoutSize.x - margin.left - margin.right;
			switch (h->getAlign())
			{
			case Align::LEFT:
				childPos.x = margin.left;
				break ;
			case Align::CENTER:
				childPos.x = (layoutSize.x - childSize.x + margin.left
								- margin.right) / 2;
				break ;
			case Align::RIGHT:
				childPos.x = layoutSize.x - childSize.x - margin.right;
				break ;
			}
		}
		else
		{
			if (childSize.y + margin.top + margin.bottom > layoutSize.y)
				childSize.y = layoutSize.y - margin.top - margin.bottom;
			switch (h->getAlign())
			{
			case Align::TOP:
				childPos.y = margin.top;
				break ;
			case Align::CENTER:
				childPos.y = (layoutSize.y - childSize.y + margin.top
								- margin.bottom) / 2;
				break ;
			case Align::BOTTOM:
				childPos.y = layoutSize.y - childSize.y - margin.bottom;
				break ;
			}
		}
		h->setPos(childPos);
		h->setSize(childSize);
	}
}

/*
** onMeasure
** -
** Place childs respecting their requested size and their margin
** and resize the layout
*/
void			LinearLayout::onMeasure(void)
{
	ft::Vec2<int>	requestedSize;
	int				tmp;
	int				offset;
	int				maxWidth;

	offset = 0;
	maxWidth = 0;
	for (ViewHolder *h : _childs)
	{
		h->getView()->onMeasure();

		ft::Rect<int> const	&margin = h->getMargin();

		requestedSize = h->getRequestedSize();
		if (_direction == Direction::VERTICAL)
		{
			tmp = requestedSize.x + margin.left + margin.right;
			if (tmp > maxWidth)
				maxWidth = tmp;
			offset += margin.top;
			h->setPosY(offset);
			offset += margin.bottom;
			offset += requestedSize.y;
		}
		else
		{
			tmp = requestedSize.y + margin.top + margin.bottom;
			if (tmp > maxWidth)
				maxWidth = tmp;
			offset += margin.left;
			h->setPosX(offset);
			offset += margin.right;
			offset += requestedSize.x;
		}
	}
	if (_direction == Direction::VERTICAL)
		_fullSize = ft::make_vec(maxWidth, offset);
	else
		_fullSize = ft::make_vec(offset, maxWidth);
	_holder->setRequestedSize(_fullSize);
	AView::onMeasure();
	alignChilds();
	_layoutFlags &= ~AView::MEASURE_QUERY;
}

/*
** onSizeChange
*/
void			LinearLayout::onSizeChange(ft::Vec2<int> size)
{
	AView::onSizeChange(size);
	alignChilds();
}

/*
** onDraw
*/
ft::Rect<int>	LinearLayout::getRedrawClip(void) const
{
	ft::Rect<int>	clip(0, 0, 0, 0);

	for (LinearLayout::ViewHolder *vh : _childs)
	{
		if (vh->getView()->isRedrawQueried())
		{
			if (clip.getWidth() == 0 || clip.getHeight() == 0)
				clip = ft::make_rect(vh->getPos(), vh->getSize());
			else
				clip.merge(ft::make_rect(vh->getPos(), vh->getSize()));
		}
	}
	return clip;
}

void			LinearLayout::onDraw(ACanvas &canvas)
{
	float const			oldAlpha = canvas.getAlpha();
	ft::Vec2<int> const	oldOrigin = canvas.getOrigin();
	ft::Rect<int> const	layoutRect = canvas.getClip();
	auto				redrawChild =
		[=, &canvas](AView *v, ft::Rect<int> const &bounds)
	{
		ft::Rect<int>		clip;

		if (!bounds.collides(layoutRect, clip))
			return ;
		clip -= bounds.getPos();
		canvas.applyAlpha(v->getAlpha());
		canvas.applyOrigin(bounds.getPos());
		canvas.setClip(clip);
		v->onDraw(canvas);
		canvas.setOrigin(oldOrigin);
		canvas.setAlpha(oldAlpha);
		return ;
	};
	ft::Rect<int>		redrawClip;
	ft::Rect<int>		bounds;
	AView				*v;

	if (AView::isRedrawQueried())
	{
		ASolidView::onDraw(canvas);
		_layoutFlags &= ~AView::REDRAW_QUERY;
		for (ViewHolder *vh : _childs)
		{
			v = vh->getView();
			bounds = vh->getPos() ^ vh->getSize();
			if (v->isVisible())
				redrawChild(v, bounds);
		}
	}
	else if (_layoutFlags & AView::REDRAW_QUERY)
	{
		redrawClip = getRedrawClip();
		for (ViewHolder *vh : _childs)
		{
			v = vh->getView();
			bounds = vh->getPos() ^ vh->getSize();
			if (v->isVisible()
				&& (v->isRedrawQueried() || redrawClip.collides(bounds)))
				redrawChild(v, bounds);
		}
		_layoutFlags &= ~AView::REDRAW_QUERY;
	}
	return ;
}

/*
** Add a view
** If the view already has a parent, throw
*/
void			LinearLayout::addView(AView *view)
{
	ViewHolder		*holder;

	if (view->getViewHolder() != NULL)
		throw std::invalid_argument(
			ft::f("LinearLayout::addView: View (#%) already has a parent",
				  view->getViewHolder()->getParent()));
	holder = new ViewHolder(this, view);
	view->setViewHolder(holder);
	_childs.push_back(holder);
	view->queryUpdate();
	view->queryMeasure();
	view->queryRedraw();
}

AView			*LinearLayout::popView(AView *view)
{
	ViewHolder					*holder;
	child_container_t::iterator	it;

	holder = dynamic_cast<ViewHolder*>(view->getViewHolder());
	if (holder == nullptr
		|| (it = std::find(_childs.begin(), _childs.end(), holder))
			== _childs.end())
		throw std::domain_error(ft::f("HorizontalLayout::popView: Invalid"));
	this->_childs.erase(it);
	delete holder;
	view->setViewHolder(nullptr);
	return (view);
}

AView			*LinearLayout::at(int i)
{
	return (_childs[i]->getView());
}

AView const		*LinearLayout::at(int i) const
{
	return (_childs[i]->getView());
}

int				LinearLayout::size(void) const
{
	return (_childs.size());
}

IViewHolder		*LinearLayout::holderAt(int i)
{
	return (_childs[i]);
}

LinearLayout::Direction	LinearLayout::getDirection(void) const
{
	return (_direction);
}

void			LinearLayout::setDirection(Direction o)
{
	_direction = o;
}

void			LinearLayout::setParam(std::string const &k,
					std::string const &v)
{
	static std::unordered_map<std::string, Direction> const direction_map
	{
		{"vertical", Direction::VERTICAL},
		{"horizontal", Direction::HORIZONTAL},
	};
	static std::unordered_map<std::string, bool (*)(LinearLayout*,
		std::string const &)> const		param_map
	{
		{"direction", [](LinearLayout *layout, std::string const &v)
		{
			auto const		&it = direction_map.find(v);

			if (it == direction_map.cend())
				return (false);
			layout->setDirection(it->second);
			return (true);
		}},
	};
	auto const		&it = param_map.find(k);

	if (it != param_map.cend())
	{
		if (!it->second(this, v))
			throw std::domain_error(ft::f("LinearLayout::setParam: "
				"Invalid param: %=\"%\"", k, v));
	}
	else
		ALayout::setParam(k, v);
}

int				LinearLayout::getDirectionG(lua_State *l)
{
	LinearLayout *const	self = ftlua::pop<LinearLayout*>(l, 1);
	// LinearLayout *const	self = ftlua::retrieveSelf<LinearLayout>(l, 1);

	ftlua::push(l, static_cast<int>(self->getDirection()));
	return 1;
}

int				LinearLayout::setDirectionG(lua_State *l)
{
	LinearLayout *const	self = ftlua::pop<LinearLayout*>(l, 1);
	// LinearLayout *const	self = ftlua::retrieveSelf<LinearLayout>(l, 1);

	self->setDirection(static_cast<Direction>(luaL_checkinteger(l, 1)));
	lua_pop(l, 1);
	return (0);
}

};
