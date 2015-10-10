// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ASolidView.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:37 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 18:00:26 by jaguillo         ###   ########.fr       //
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

	ASolidView(XmlParser const &xml, Activity &act);

	Canvas::Params		_params;

private:
	ASolidView(void);
	ASolidView(ASolidView const &src);
	ASolidView			&operator=(ASolidView const &rhs);
};

};

#endif
