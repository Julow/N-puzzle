// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TextView.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/12 08:49:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/24 11:15:03 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TEXTVIEW_HPP
# define TEXTVIEW_HPP

# include "ftui/ASolidView.hpp"

namespace ftui
{

/*
** TODO: \n
*/
class	TextView : public ASolidView
{
public:

	// CONSTRUCTION ***************** //
	static AView		*createView(
		ftui::Activity &act, ft::XmlParser const *xml, std::string const *id);

	TextView(Activity &a, ft::XmlParser const &xml);
	TextView(Activity &act, std::string const *id
			 , std::string const &viewName = "TextView");
	virtual ~TextView(void);

	TextView(void) = delete;
	TextView(TextView const &src) = delete;
	TextView			&operator=(TextView const &rhs) = delete;


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
