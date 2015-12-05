// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ASolidView.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:37 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/05 18:02:46 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ASOLIDVIEW_HPP
# define ASOLIDVIEW_HPP

# include "ft/Color.hpp"
# include "ftui/AView.hpp"
# include "ftui/ACanvas.hpp"

namespace ftui
{

/*
** ========================================================================== **
** ASolidView
** -
** Base class for views with a solid background
** -
** Params
** 	backgroundColor		(color)	Background color
** 	borderColor			(color)	Border color
** 	borderWidth			(int)	Border width
*/
class	ASolidView : public AView
{
public:
	virtual ~ASolidView(void);

	virtual void		onDraw(ACanvas &canvas);

	virtual void		setParam(std::string const &p, std::string const &v);

	ft::Color::t		getBackgroundColor(void) const;
	ft::Color::t		getBorderColor(void) const;
	int					getBorderWidth(void) const;

	void				setBackgroundColor(ft::Color::t color);
	void				setBorderColor(ft::Color::t color);
	void				setBorderWidth(int width);

protected:
	ASolidView(Activity &act, std::string const &viewName);

	ACanvas::Params		_bgParams;

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
