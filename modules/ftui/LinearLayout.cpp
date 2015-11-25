// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LinearLayout.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/25 13:23:56 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/25 15:31:25 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "LinearLayout.hpp"

namespace ftui
{

AView			*LinearLayout::createView(ftui::Activity &act,
					ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return (new LinearLayout(act, id));
	return (new LinearLayout(act, *xml));
}

LinearLayout::LinearLayout(Activity &act, ft::XmlParser const &xml) :
	ALayout(act, xml)
{
}

LinearLayout::LinearLayout(Activity &act, std::string const *id,
		std::string const &viewName) :
	ALayout(act, id, viewName)
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
			if (childSize.y + margin.left + margin.right > layoutSize.x)
				childSize.y = layoutSize.x - margin.left - margin.right;
			switch (h->getAlign())
			{
			case Align::LEFT:
				childPos.x = margin.left;
				break ;
			case Align::CENTER:
				childPos.x = (layoutSize.x - childSize.y + margin.left
								- margin.right) / 2;
				break ;
			case Align::RIGHT:
				childPos.x = layoutSize.x - childSize.y - margin.right;
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

		requestedSize = h->getView()->getRequestedSize();
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
		_holder->setRequestedSize(ft::make_vec(maxWidth, offset));
	else
		_holder->setRequestedSize(ft::make_vec(offset, maxWidth));
	AView::onMeasure();
	alignChilds();
	_layoutFlags &= ~AView::MEASURE_QUERY;
}

/*
** onSizeChange
*/
void			LinearLayout::onSizeChange(void)
{
	AView::onSizeChange();
	alignChilds();
}

/*
** onDraw
*/
static ft::Rect<int>	calc_redraw_clip(
	LinearLayout::child_container_t &childs)
{
	ft::Rect<int>	clip(0, 0, 0, 0);

	for (LinearLayout::ViewHolder *vh : childs)
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
			if (v->isVisible()
				&& (v->isRedrawQueried() || redrawClip.collides(bounds)))
				redrawChild(v, bounds.getPos(), bounds.getSize());
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

Direction		LinearLayout::getDirection(void) const
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
	static std::unordered_map<std::string, bool (*)(LinearLayout*,
		std::string const &)> const		param_map
	{
		{"direction", [](LinearLayout *holder, std::string const &v)
		{
			if (v == "VERTICAL")
				holder->setDirection(LinearLayout::Direction::VERTICAL);
			else if (v == "HORIZONTAL")
				holder->setDirection(LinearLayout::Direction::HORIZONTAL);
			else
				return (false);
			return (true);
		}}
	};
	auto const		&it = param_map.find(k);

	if (it != param_map.end() && !it->second(this, v))
		throw std::domain_error(ft::f("LinearLayout::setParam: "
			"Invalid param: %=\"%\"", k, v));
	return ;
}

};
