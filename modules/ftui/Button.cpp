// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Button.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/09 14:32:22 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/17 15:02:38 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Button.hpp"
#include "ftui/Activity.hpp"
#include "ftui/IViewHolder.hpp"

namespace ftui
{

using namespace std::chrono_literals;

Button::time_point const	Button::_zero =
	std::chrono::system_clock::from_time_t(0);
Button::time_diff const	Button::_maxDelta =
	300ms;

/* ************************************************************************** **
** CONSTRUCTION
*/

AView		*Button::createView(
	ftui::Activity &act, ft::XmlParser const *xml, std::string const *id)
{
	FTASSERT((xml == nullptr) != (id == nullptr));
	if (xml == nullptr)
		return new Button(act, id);
	return new Button(act, *xml);
}

Button::Button(Activity &act, ft::XmlParser const &xml)
	: AView(act, xml)
	, _state(true)
	, _normal{		0xFF00AA00, 0xFFFF0000, 5, 0}
	, _disabled{	0, 0, 0, 0}
	, _pushed{		0xFF00AA00, 0xFFAA0000, 2, 0}
	, _highlight{	0, 0x40FFFF00, 5, 0}
	, _lastClick(_zero)
{
	return ;
}

Button::Button(Activity &act, std::string const *id
			   , std::string const &viewName /* = "Button" */)
	: AView(act, id, viewName)
	, _state(true)
	, _normal{		0xFF00AA00, 0xFFFF0000, 5, 0}
	, _disabled{	0, 0, 0, 0}
	, _pushed{		0xFF00AA00, 0xFFAA0000, 2, 0}
	, _highlight{	0, 0x40FFFF00, 5, 0}
	, _lastClick(_zero)
{
	return ;
}

Button::~Button()
{
	return ;
}

void		Button::inflate(Activity &act, ft::XmlParser &xml)
{
	AView::inflate(act, xml);
	return ;
}

void		Button::onAttach(void)
{
	this->hookMouseMove(true);
	this->hookMouseClick(true);
	return ;
}

void		Button::onDetach(void)
{
	this->hookMouseMove(false);
	this->hookMouseClick(false);
	return ;
}

/* ************************************************************************** **
** DRAW
*/

void		Button::onDraw(Canvas &canvas)
{
	IViewHolder		*vh = this->getViewHolder();

	FTASSERT(vh != nullptr);
	// canvas.clearClip();
	if (this->isMouseCaptureTargeted())
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_pushed);
	else if (_state == true)
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_normal);
	else
		canvas.drawRect(ft::make_rect(ft::make_vec(0, 0), _holder->getSize()),
						_disabled);
	if (this->isMouseOver())
	{
		auto tmp = ft::make_vec(_highlight.lineWidth, _highlight.lineWidth);
		canvas.drawRect(ft::make_rect<float>(tmp, _holder->getSize() - tmp * 2.)
						, _highlight);
		// canvas.drawRect({
		// 		{5.f, 5.f}
		// 		, ft::Vec2<float>(vh->getSize().x - 10, vh->getSize().y - 10)}
		// 	, _highlight); //TODO: pas beau
	}
	AView::onDraw(canvas);
	return ;
}

/* ************************************************************************** **
** MOUSE EVENTS
*/

bool        Button::onMouseDown(int x, int y, int button, int mods)
{
	if (button == 0)
	{
		this->hookMouseCapture(true);
		this->queryRedraw();
	}
	return AView::onMouseDown(x, y, button, mods) || true;
}

bool        Button::onMouseUp(int x, int y, int button, int mods)
{
	if (this->isMouseCaptureTargeted())
	{
		if (button == 0 && this->isMouseOver())
		{
			if (_lastClick != _zero
				&& std::chrono::system_clock::now() - _lastClick < _maxDelta)
			{
				// 1. Validate button double click
				_lastClick = _zero;
				this->onDoubleClick(mods);
			}
			else
			{
				// 2. Validate button click
				_lastClick = std::chrono::system_clock::now();
				this->onClick(mods);
			}
			this->queryRedraw();
			this->hookMouseCapture(false);
			return AView::onMouseUp(x, y, button, mods) || true;
		}
		// 3. Abort button click
		this->queryRedraw();
		this->hookMouseCapture(false);
	}
	// 4. Was not clicking
	return AView::onMouseUp(x, y, button, mods);
}

void        Button::onMouseEnter(int x, int y)
{
	this->queryRedraw();
	AView::onMouseEnter(x, y);
	return ;
}

void        Button::onMouseLeave(int x, int y)
{
	this->queryRedraw();
	AView::onMouseLeave(x, y);
	return ;
}


void        Button::onClick(int mods)
{
	this->callLuaCallback(
		_act.getLuaState()
		, static_cast<uint32_t>(LuaCallback::CLICK), mods, 0);
	//TODO: does not compile without the trailing '0'
	return ;
}

void        Button::onDoubleClick(int mods)
{
	this->callLuaCallback(
		_act.getLuaState()
		, static_cast<uint32_t>(LuaCallback::DOUBLE_CLICK), mods, 0);
	//TODO: does not compile without the trailing '0'
	return ;
}

/* ************************************************************************** **
** INTERACTIONS
*/

void		Button::setState(bool state)
{
	if (state != _state)
	{
		_state = state;
		this->queryRedraw();
	}
	return ;
}

bool		Button::getState(void)
{
	return _state;
}

Canvas::Params const	&Button::getNormalParams(void) const
{ return this->_normal ; }

void					Button::setNormalParams(Canvas::Params const &p)
{ this->_normal = p; }


Canvas::Params const	&Button::getDisabledParams(void) const
{ return this->_disabled ; }

void					Button::setDisabledParams(Canvas::Params const &p)
{ this->_disabled = p; }


Canvas::Params const	&Button::getPushedParams(void) const
{ return this->_pushed ; }

void					Button::setPushedParams(Canvas::Params const &p)
{ this->_pushed = p; }


Canvas::Params const	&Button::getHighlightParams(void) const
{ return this->_highlight ; }

void					Button::setHighlightParams(Canvas::Params const &p)
{ this->_highlight = p; }

};
