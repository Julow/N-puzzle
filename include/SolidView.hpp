// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/08 11:45:37 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/08 13:06:04 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLIDVIEW_HPP
# define SOLIDVIEW_HPP

# include "ftui/AView.hpp"
# include "ftui/Canvas.hpp"

namespace ftui
{

class	SolidView : public AView
{
public:
	SolidView(XmlParser const &xml, Activity &act);
	virtual ~SolidView(void);

	virtual void		onDraw(Canvas &canvas);

	virtual void		setParam(std::string const &p, std::string const &v);

protected:

	Canvas::color_t		_color;

private:
	SolidView(void);
	SolidView(SolidView const &src);
	SolidView			&operator=(SolidView const &rhs);

/*
** Static
*/
public:
	static AView		*create_view(XmlParser const &xml, Activity &act);
};

};

#endif
