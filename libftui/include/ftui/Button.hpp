// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Button.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/09 14:26:40 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/10 18:34:26 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BUTTON_HPP
# define BUTTON_HPP

# include "ftui/AView.hpp"
# include "ftui/Canvas.hpp"

//# include <string>
# include <iostream>
//# include <stdexcept>

namespace ftui
{

class Button : public AView
{
public:

	enum class  LuaCallback : uint32_t
	{
		CLICK = static_cast<uint32_t>(AView::LuaCallback::__LAST),
		__LAST
	};

	// CONSTRUCTION ***************** //
	static AView		*createView(XmlParser const &xml, Activity &a);

	Button() = delete;
	Button(XmlParser const &xml, Activity &a);
	Button(Button const &src) = delete;
	Button				&operator=(Button const &rhs) = delete;
	virtual ~Button();

	virtual void                inflate(XmlParser &xml, Activity &act);

	// virtual void		 setParam(std::string const &k, std::string const &v);


	// MOUSE EVENTS ***************** //
	virtual bool		onMouseDown(int x, int y, int button, int mods);
	virtual bool		onMouseUp(int x, int y, int button, int mods);

	virtual void		onMouseEnter(int x, int y);
	virtual void		onMouseLeave(int x, int y);

	virtual void		onClick(int button, int mods);
	virtual void		onDraw(Canvas &canvas);

protected:
	Canvas::Params		_normal;
	Canvas::Params		_disabled;
	Canvas::Params		_pushed;
	Canvas::Params		_highlight;

private:
};
};
//std::ostream					&operator<<(std::ostream &o, Button const &rhs);

#endif // ******************************************************** BUTTON_HPP //
