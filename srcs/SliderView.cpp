// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SliderView.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:27:49 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/23 17:49:20 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "SliderView.hpp"

ftui::AView			*SliderView::createView(ftui::Activity &act,
						ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return (new SliderView(act, id));
	return (new SliderView(act, *xml));
}

SliderView::SliderView(ftui::Activity &act, std::string const *id,
		std::string const &viewName) :
	ftui::ASolidView(act, id, viewName),
	_bounds(0.f, 1.f),
	_value(0.f),
	_inCallback(false)
{
}

SliderView::SliderView(ftui::Activity &act, ft::XmlParser const &xml) :
	ftui::ASolidView(act, xml),
	_bounds(0.f, 1.f),
	_value(0.f),
	_inCallback(false)
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
	if (val != _value && !_inCallback)
	{
		_inCallback = true;
		onValueChange(val);
		_inCallback = false;
	}
	_value = val;
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

void				SliderView::onValueChange(float val)
{
	queryRedraw();
	callLuaCallback(_act.getLuaState(),
		static_cast<uint32_t>(LuaCallback::VALUE_CHANGE), val);
}

void				SliderView::onAttach(void)
{
	hookMouseClick(true);
	hookMouseScroll(true);
	AView::onAttach();
}

void				SliderView::onDetach(void)
{
	hookMouseClick(false);
	hookMouseScroll(false);
	AView::onDetach();
}

void				SliderView::onDraw(ftui::Canvas &canvas)
{
	ft::Rect<float>			rect(canvas.getClip());

	ASolidView::onDraw(canvas);
	rect.setWidth(rect.getWidth() * _value / (_bounds.y - _bounds.x));
	if (ft::Color::a(_bgParams.strokeColor) > 0 && _bgParams.lineWidth > 0)
		rect.expand(-_bgParams.lineWidth);
	canvas.drawRect(rect, ftui::Canvas::Params{0xFFFF0000, 0xFFFFFF00, 1, 0});
}

bool				SliderView::onMouseDown(int x, int y, int button, int mods)
{
	if (ftui::ASolidView::onMouseDown(x, y, button, mods))
		return (true);
	setValueWidth(x);
	hookMouseMove(true);
	hookMouseCapture(true);
	return (true);
}

bool				SliderView::onMouseUp(int x, int y, int button, int mods)
{
	if (ftui::ASolidView::onMouseUp(x, y, button, mods))
		return (true);
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
	setValue(_value + delta);
	return (true);
}

void				SliderView::setValueWidth(int x)
{
	float const			width = static_cast<float>(_holder->getSize().x);
	float const			pos = static_cast<float>(x);

	setValue(pos * (_bounds.y - _bounds.x) / width + _bounds.x);
}
