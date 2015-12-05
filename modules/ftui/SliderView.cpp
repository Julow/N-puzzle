// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SliderView.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:27:49 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/05 18:03:53 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"
#include "ftui/ASolidView.hpp"
#include "ftui/SliderView.hpp"
#include "ftui/Activity.hpp"


namespace ftui
{

ftui::AView			*SliderView::createView(ftui::Activity &act)
{
	return (new SliderView(act));
}

SliderView::SliderView(ftui::Activity &act, std::string const &viewName) :
	ftui::ASolidView(act, viewName),
	_bounds(0.f, 1.f),
	_value(0.f),
	_steps(-1),
	_barParams({0x0, 0xDD0EE1EC, 1, 0}),
	_flags(0)
{
}

SliderView::~SliderView(void)
{
}

float				SliderView::getValue(void) const
{
	return (_value);
}

void				SliderView::setValue(float val)
{
	if (val < _bounds.x)
		val = _bounds.x;
	else if (val > _bounds.y)
		val = _bounds.y;
	if (_steps > 0)
		val = std::round((val - _bounds.x) / ((_bounds.y - _bounds.x) / _steps))
			* ((_bounds.y - _bounds.x) / _steps) + _bounds.x;
	if (val != _value)
	{
		_value = val;
		if (!(_flags & FLAG_IN_CALLBACK))
		{
			_flags |= FLAG_IN_CALLBACK;
			onValueChange(val);
			_flags &= ~FLAG_IN_CALLBACK;
		}
	}
}

int					SliderView::getSteps(void) const
{
	return (_steps);
}

void				SliderView::setSteps(int step)
{
	_steps = step;
	setValue(_value);
}

int					SliderView::getStepValue(void) const
{
	return (std::round((_value - _bounds.x)
		/ ((_bounds.y - _bounds.x) / _steps)));
}

void				SliderView::setStepValue(int step)
{
	setValue(step * (_bounds.y - _bounds.x) / _steps + _bounds.x);
}

ft::Vec2<float>		SliderView::getBounds(void) const
{
	return (_bounds);
}

void				SliderView::setBounds(ft::Vec2<float> bounds)
{
	_bounds = bounds;
	if (_value < bounds.x)
		_value = bounds.x;
	else if (_value > bounds.y)
		_value = bounds.y;
}

ftui::ACanvas::Params	&SliderView::getBarParams(void)
{
	return (_barParams);
}

ftui::ACanvas::Params const	&SliderView::getBarParams(void) const
{
	return (_barParams);
}

void				SliderView::setDisabled(bool b)
{
	if (b)
	{
		hookMouseClick(false);
		hookMouseScroll(false);
		hookMouseMove(false);
		hookMouseCapture(false);
		_flags |= FLAG_DISABLED;
	}
	else
	{
		hookMouseClick(true);
		hookMouseScroll(true);
		_flags &= ~FLAG_DISABLED;
	}
}

bool				SliderView::isDisabled(void) const
{
	return (static_cast<bool>(_flags & FLAG_DISABLED));
}

void				SliderView::onValueChange(float val)
{
	queryRedraw();
	callLuaCallback(_act.getLuaState(),
		static_cast<uint32_t>(LuaCallback::VALUE_CHANGE), val);
}

void				SliderView::onAttach(void)
{
	if (!(_flags & FLAG_DISABLED))
	{
		hookMouseClick(true);
		hookMouseScroll(true);
	}
	AView::onAttach();
}

void				SliderView::onDetach(void)
{
	if (!(_flags & FLAG_DISABLED))
	{
		hookMouseClick(false);
		hookMouseScroll(false);
	}
	AView::onDetach();
}

void				SliderView::onDraw(ftui::ACanvas &canvas)
{
	ft::Rect<float>			rect(canvas.getClip());

	ASolidView::onDraw(canvas);
	rect.setWidth(rect.getWidth() * (_value - _bounds.x)
		/ (_bounds.y - _bounds.x));
	if (ft::Color::a(_bgParams.strokeColor) > 0 && _bgParams.lineWidth > 0)
		rect.expand(-_bgParams.lineWidth);
	canvas.drawRect(rect, _barParams);
}

bool				SliderView::onMouseDown(int x, int y, int button, int mods)
{
	if (ftui::ASolidView::onMouseDown(x, y, button, mods))
		return (true);
	if (_flags & FLAG_DISABLED)
		return (false);
	setValueWidth(x);
	hookMouseMove(true);
	hookMouseCapture(true);
	return (true);
}

bool				SliderView::onMouseUp(int x, int y, int button, int mods)
{
	if (ftui::ASolidView::onMouseUp(x, y, button, mods))
		return (true);
	if (_flags & FLAG_DISABLED)
		return (false);
	hookMouseMove(false);
	hookMouseCapture(false);
	return (true);
}

bool				SliderView::onMouseMove(int x, int y)
{
	if (ftui::ASolidView::onMouseMove(x, y))
		return (true);
	setValueWidth(x);
	return (true);
}

bool				SliderView::onMouseScroll(int x, int y, float delta)
{
	if (ftui::ASolidView::onMouseScroll(x, y, delta))
		return (true);
	if (_flags & FLAG_DISABLED)
		return (false);
	setValue(_value + delta);
	return (true);
}

void				SliderView::setParam(std::string const &k, std::string const &v)
{
	static std::unordered_map<std::string, void (*)(SliderView*,
		std::string const &)> const		param_map
	{
		{"value", [](SliderView *view, std::string const &p)
		{
			view->setValue(std::atof(p.c_str()));
		}},
		{"steps", [](SliderView *view, std::string const &p)
		{
			view->setSteps(std::atoi(p.c_str()));
		}},
		{"minValue", [](SliderView *view, std::string const &p)
		{
			view->setBounds(ft::make_vec(
				static_cast<float>(std::atof(p.c_str())),
				view->getBounds().y));
		}},
		{"maxValue", [](SliderView *view, std::string const &p)
		{
			view->setBounds(ft::make_vec(view->getBounds().x,
				static_cast<float>(std::atof(p.c_str()))));
		}},
		{"barColor", [](SliderView *view, std::string const &p)
		{
			view->getBarParams().fillColor = std::stoul(p, NULL, 16);
		}},
		{"barBorderColor", [](SliderView *view, std::string const &p)
		{
			view->getBarParams().strokeColor = std::stoul(p, NULL, 16);
		}},
		{"barBorderWidth", [](SliderView *view, std::string const &p)
		{
			view->getBarParams().lineWidth = std::stoul(p, NULL, 16);
		}},
		{"disabled", [](SliderView *view, std::string const &p)
		{
			view->setDisabled(p == "true");
		}},
	};
	auto const		&it = param_map.find(k);

	if (it != param_map.end())
		it->second(this, v);
	else
		ASolidView::setParam(k, v);
}

void				SliderView::setValueWidth(int x)
{
	float const			width = static_cast<float>(_holder->getSize().x);
	float const			pos = static_cast<float>(x);

	setValue(pos * (_bounds.y - _bounds.x) / width + _bounds.x);
}

int					SliderView::getValueG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);

	// ftlua::push(l, self->getValue());
	// return 1;
	return ftlua::handle<1, 1>(l, &SliderView::getValue);
}

int					SliderView::setValueG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);

	// self->setValue(luaL_checknumber(l, 1));
	// lua_pop(l, 1);
	// return (0);
	return ftlua::handle<2, 0>(l, &SliderView::setValue);
}

int					SliderView::getStepValueG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);

	// ftlua::push(l, self->getStepValue());
	// return 1;
	return ftlua::handle<1, 1>(l, &SliderView::getStepValue);
}

int					SliderView::setStepValueG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);

	// self->setStepValue(luaL_checkinteger(l, 1));
	// lua_pop(l, 1);
	// return (0);
	return ftlua::handle<2, 0>(l, &SliderView::setStepValue);
}

int					SliderView::getBoundsG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);

	// ftlua::push(l, self->getBounds());
	// return 2;
	return ftlua::handle<1, 2>(l, &SliderView::getBounds);
}

int					SliderView::setBoundsG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);
	// ft::Vec2<float>		bounds;

	// bounds.x = luaL_checknumber(l, 1);
	// bounds.y = luaL_checknumber(l, 2);
	// lua_pop(l, 2);
	// self->setBounds(bounds);
	// return (0);
	return ftlua::handle<3, 0>(l, &SliderView::setBounds);
}

int					SliderView::getStepsG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);

	// ftlua::push(l, self->getSteps());
	// return 1;
	return ftlua::handle<1, 1>(l, &SliderView::getSteps);
}

int					SliderView::setStepsG(lua_State *l)
{
	// SliderView *const	self = ftlua::pop<SliderView*>(l, 1);
	// // SliderView *const	self = ftlua::retrieveSelf<SliderView>(l, 1);

	// self->setSteps(luaL_checkinteger(l, 1));
	// lua_pop(l, 1);
	// return (0);
	return ftlua::handle<2, 0>(l, &SliderView::setSteps);
}

};
