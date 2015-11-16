// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:50:52 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 18:00:05 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLIDVIEW_HPP
# define SOLIDVIEW_HPP

# include "ftui/ASolidView.hpp"

namespace ftui
{

/*
** Simplest implementation of ASolidView
*/
class	SolidView : public ASolidView
{
public:
	SolidView(ft::XmlParser const &xml, Activity &act);
	virtual ~SolidView(void);

protected:

private:
	SolidView(void);
	SolidView(SolidView const &src);
	SolidView			&operator=(SolidView const &rhs);
/*
** Static
*/
public:
	static AView		*createView(ft::XmlParser const &xml, Activity &act);
};

};

#endif
