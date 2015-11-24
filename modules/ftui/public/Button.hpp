// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Button.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/09 14:26:40 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 11:15:03 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BUTTON_HPP
# define BUTTON_HPP

# include "ftui/AView.hpp"
# include "ftui/ACanvas.hpp"

//# include <string>
# include <iostream>
//# include <stdexcept>
# include <chrono>

namespace ftui
{

class Button : public AView
{
public:

	enum class	LuaCallback : uint32_t
	{
		CLICK = static_cast<uint32_t>(AView::LuaCallback::__LAST),
		DOUBLE_CLICK,
		__LAST
	};

	// CONSTRUCTION ***************** //
	static AView		*createView(
		ftui::Activity &act, ft::XmlParser const *xml, std::string const *id);

	Button(Activity &act, ft::XmlParser const &xml);
	Button(Activity &act, std::string const *id
			, std::string const &viewName = "Button");
	virtual ~Button();

	Button() = delete;
	Button(Button const &src) = delete;
	Button				&operator=(Button const &rhs) = delete;

	// virtual void setParam(std::string const &k, std::string const &v); //TODO: this

	// DRAW ************************* //
	virtual void		onDraw(ACanvas &canvas);

	// MOUSE EVENTS ***************** //
	virtual bool		onMouseDown(int x, int y, int button, int mods);
	virtual bool		onMouseUp(int x, int y, int button, int mods);

	virtual void		onMouseEnter(int x, int y);
	virtual void		onMouseLeave(int x, int y);

	virtual void		onClick(int mods);
	virtual void		onDoubleClick(int mods);

	// INTERACTIONS ***************** //
	virtual void		onAttach(void);
	virtual void		onDetach(void);

	virtual void		setState(bool status);
	virtual bool		getState(void);

	ACanvas::Params const	&getNormalParams(void) const;
	void					setNormalParams(ACanvas::Params const &p);

	ACanvas::Params const	&getDisabledParams(void) const;
	void					setDisabledParams(ACanvas::Params const &p);

	ACanvas::Params const	&getPushedParams(void) const;
	void					setPushedParams(ACanvas::Params const &p);

	ACanvas::Params const	&getHighlightParams(void) const;
	void					setHighlightParams(ACanvas::Params const &p);

protected:
	bool				_state;
	ACanvas::Params		_normal;
	ACanvas::Params		_disabled;
	ACanvas::Params		_pushed;
	ACanvas::Params		_highlight;

private:
	using time_point = std::chrono::system_clock::time_point;
	using time_diff = std::chrono::duration<int, std::milli>;
	static const time_point	_zero;
	static const time_diff	_maxDelta;
	time_point			_lastClick;

};
};
//std::ostream					&operator<<(std::ostream &o, Button const &rhs);

#endif // ******************************************************** BUTTON_HPP //
