// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TextView.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/12 08:49:40 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/12 16:11:34 by jaguillo         ###   ########.fr       //
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
	TextView(XmlParser const &xml, Activity &a);
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

	static AView		*createView(XmlParser const &xml, Activity &a);

protected:

	std::string			_text;
	Canvas::Params		_textParams;

private:
	TextView(void);
	TextView(TextView const &src);
	TextView			&operator=(TextView const &rhs);
};

};

#endif
