// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TextView.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/12 08:49:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 18:59:34 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TEXTVIEW_HPP
# define TEXTVIEW_HPP

# include "ftui/ASolidView.hpp"

namespace ftui
{

/*
** ========================================================================== **
** TextView
** -
** Params:
** 	text			(str)	Text to be render
** 	textFont		(str)	Font
** 	textColor		(color)
** 	textSize		(int)
** -
** TODO: \n
*/
class	TextView : public ASolidView
{
public:
	static AView		*createView(ftui::Activity &act);

	TextView(Activity &act, std::string const &viewName = "TextView");
	virtual ~TextView(void);

	virtual void		onMeasure(void);
	virtual void		onDraw(ACanvas &canvas);

	std::string const	&getText(void) const;
	void				setText(std::string const &text);

	ACanvas::font_t		getFont(void) const;
	void				setFont(ACanvas::font_t font);

	ft::Color::t		getTextColor(void) const;
	void				setTextColor(ft::Color::t color);

	int32_t				getTextSize(void) const;
	void				setTextSize(int32_t size);

	virtual void		setParam(std::string const &k, std::string const &v);

protected:
	std::string			_text;
	ACanvas::Params		_textParams;

private:
	TextView(void) = delete;
	TextView(TextView const &src) = delete;
	TextView			&operator=(TextView const &rhs) = delete;

/*
** Static
*/
public:
	static int			getTextG(lua_State *l);
	static int			setTextG(lua_State *l);
	static int			getFontG(lua_State *l);
	static int			setFontG(lua_State *l);
	static int			getTextColorG(lua_State *l);
	static int			setTextColorG(lua_State *l);
	static int			getTextSizeG(lua_State *l);
	static int			setTextSizeG(lua_State *l);
	static int			setParamG(lua_State *l);
};

};

#endif
