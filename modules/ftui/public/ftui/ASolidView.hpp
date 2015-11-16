// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ASolidView.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:37 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/16 13:13:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ASOLIDVIEW_HPP
# define ASOLIDVIEW_HPP

# include "ft/Color.hpp"
# include "ftui/AView.hpp"
# include "ftui/Canvas.hpp"

namespace ftui
{

/*
** ASolidView
** -
** Base class for views with a solid background
*/
class	ASolidView : public AView
{
public:
	virtual ~ASolidView(void);

	virtual void		onDraw(Canvas &canvas);

	virtual void		setParam(std::string const &p, std::string const &v);

	ft::Color::t		getBackgroundColor(void) const;
	ft::Color::t		getBorderColor(void) const;
	int					getBorderWidth(void) const;

	void				setBackgroundColor(ft::Color::t color);
	void				setBorderColor(ft::Color::t color);
	void				setBorderWidth(int width);

protected:

	ASolidView(ft::XmlParser const &xml, Activity &act);
	ASolidView(Activity &act, std::string const *id, std::string const &viewName);

	Canvas::Params		_bgParams;

private:
	ASolidView(void);
	ASolidView(ASolidView const &src);
	ASolidView			&operator=(ASolidView const &rhs);

/*
** Static
*/
public:
	static int			getBackgroundColorG(lua_State *l);
	static int			getBorderColorG(lua_State *l);
	static int			getBorderWidthG(lua_State *l);

	static int			setBackgroundColorG(lua_State *l);
	static int			setBorderColorG(lua_State *l);
	static int			setBorderWidthG(lua_State *l);
};

};

#endif
