// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TextView.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/12 08:49:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/16 20:13:38 by ngoguey          ###   ########.fr       //
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
	TextView(Activity &a, ft::XmlParser const &xml);
	virtual ~TextView(void);

	virtual void		onMeasure(void);
	virtual void		onDraw(Canvas &canvas);

	std::string const	&getText(void) const;
	void				setText(std::string const &text);

	Canvas::font_t		getFont(void) const;
	void				setFont(Canvas::font_t font);

	ft::Color::t		getTextColor(void) const;
	void				setTextColor(ft::Color::t color);

	int32_t				getTextSize(void) const;
	void				setTextSize(int32_t size);

	virtual void		setParam(std::string const &k, std::string const &v);

protected:

	std::string			_text;
	Canvas::Params		_textParams;

private:
	TextView(void);
	TextView(TextView const &src);
	TextView			&operator=(TextView const &rhs);

/*
** Static
*/
public:
	static AView            *createView(ftui::Activity &act
										, ft::XmlParser const *xml = nullptr
										, std::string const *id = nullptr);

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
