// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Button.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/09 14:32:22 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/08 12:24:12 by ngoguey          ###   ########.fr       //
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

AView		*Button::createView(ftui::Activity &act)
{
	return (new Button(act));
}

Button::Button(Activity &act, std::string const &viewName /* = "Button" */)
	: AView(act, viewName)
	, _state(true)
	, _highlightLocked(false)
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

void		Button::onAttach(void)
{
	this->hookMouseMove(true);
	this->hookMouseClick(true);
	AView::onAttach();
	return ;
}

void		Button::onDetach(void)
{
	this->hookMouseMove(false);
	this->hookMouseClick(false);
	AView::onDetach();
	return ;
}

/* ************************************************************************** **
** DRAW
*/

void		Button::onDraw(ACanvas &canvas)
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
	if (this->_highlightLocked || this->isMouseOver())
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
		, static_cast<uint32_t>(LuaCallback::CLICK), mods);
	return ;
}

void        Button::onDoubleClick(int mods)
{
	this->callLuaCallback(
		_act.getLuaState()
		, static_cast<uint32_t>(LuaCallback::DOUBLE_CLICK), mods);
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

int			Button::lockHighlightG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &Button::lockHighlight);
}
void				Button::lockHighlight(bool status)
{
	if (this->_highlightLocked != status)
	{
		this->_highlightLocked = status;
		this->queryRedraw();
	}
}

ACanvas::Params			Button::retrieveParams(lua_State *l) /*static*/
{
	ACanvas::Params		p{0, 0, 0, 0};
	int const			top = lua_gettop(l);

	if (top == 1)
		p.fillColor = luaL_checkinteger(l, 1);
	else if (top == 3)
	{
		p.fillColor = luaL_checkinteger(l, 1);
		p.strokeColor = luaL_checkinteger(l, 2);
		p.lineWidth = luaL_checkinteger(l, 3);
	}
	else
		luaL_error(l, "Bad arguments count");
	return p;
}


ACanvas::Params const	&Button::getNormalParams(void) const
{ return this->_normal ; }

void					Button::setNormalParams(ACanvas::Params const &p)
{ this->_normal = p; }

int						Button::setNormalParamsG(lua_State *l)
{
	Button	*v = ftlua::pop<Button*>(l, 1);
	// Button	*v = ftlua::retrieveSelf<Button>(l, 1);

	v->setNormalParams(Button::retrieveParams(l));
	return 0;
}


ACanvas::Params const	&Button::getDisabledParams(void) const
{ return this->_disabled ; }

void					Button::setDisabledParams(ACanvas::Params const &p)
{ this->_disabled = p; }
int						Button::setDisabledParamsG(lua_State *l)
{
	Button	*v = ftlua::pop<Button*>(l, 1);
	// Button	*v = ftlua::retrieveSelf<Button>(l, 1);

	v->setDisabledParams(Button::retrieveParams(l));
	return 0;
}


ACanvas::Params const	&Button::getPushedParams(void) const
{ return this->_pushed ; }

void					Button::setPushedParams(ACanvas::Params const &p)
{ this->_pushed = p; }
int						Button::setPushedParamsG(lua_State *l)
{
	Button	*v = ftlua::pop<Button*>(l, 1);
	// Button	*v = ftlua::retrieveSelf<Button>(l, 1);

	v->setPushedParams(Button::retrieveParams(l));
	return 0;
}


ACanvas::Params const	&Button::getHighlightParams(void) const
{ return this->_highlight ; }

void					Button::setHighlightParams(ACanvas::Params const &p)
{ this->_highlight = p; }
int						Button::setHighlightParamsG(lua_State *l)
{
	Button	*v = ftlua::pop<Button*>(l, 1);
	// Button	*v = ftlua::retrieveSelf<Button>(l, 1);

	v->setHighlightParams(Button::retrieveParams(l));
	return 0;
}

void                Button::setParam(
	std::string const &k, std::string const &v)
{
	using lambda = void (*)(Button*,std::string const&);
	using map = std::unordered_map<std::string, lambda>;

	static map      param_map
	{
		{"highlightLocked", [](Button *v, std::string const &str) {
				v->lockHighlight(str == "true");
		}},
		{"normalFillColor", [](Button *v, std::string const &str) {
				auto old = v->getNormalParams();
				old.fillColor = std::stoul(str, NULL, 16);
				v->setNormalParams(old);
		}},
		{"highlightFillColor", [](Button *v, std::string const &str) {
				auto old = v->getHighlightParams();
				old.fillColor = std::stoul(str, NULL, 16);
				v->setHighlightParams(old);
		}},
		{"normalStrokeColor", [](Button *v, std::string const &str) {
				auto old = v->getNormalParams();
				old.strokeColor = std::stoul(str, NULL, 16);
				v->setNormalParams(old);
		}},
		{"normalBorderWidth", [](Button *v, std::string const &str) {
				auto old = v->getNormalParams();
				old.lineWidth = std::stoi(str, NULL);
				v->setNormalParams(old);
		}},
		{"pushedFillColor", [](Button *v, std::string const &str) {
				auto old = v->getPushedParams();
				old.fillColor = std::stoul(str, NULL, 16);
				v->setPushedParams(old);
		}},
		{"pushedStrokeColor", [](Button *v, std::string const &str) {
				auto old = v->getPushedParams();
				old.strokeColor = std::stoul(str, NULL, 16);
				v->setPushedParams(old);
		}},
		{"pushedBorderWidth", [](Button *v, std::string const &str) {
				auto old = v->getPushedParams();
				old.lineWidth = std::stoi(str, NULL);
				v->setPushedParams(old);
		}},
	};
	auto const      &it = param_map.find(k);

	if (it != param_map.end())
		it->second(this, v);
	else
		AView::setParam(k, v);
}

};
