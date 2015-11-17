// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:50:52 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/17 14:45:27 by ngoguey          ###   ########.fr       //
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

	static AView		*createView(
		ftui::Activity &act, ft::XmlParser const *xml, std::string const *id);

	SolidView(Activity &act, ft::XmlParser const &xml);
	SolidView(Activity &act, std::string const *id
	 , std::string const &viewName = "SolidView");
	virtual ~SolidView(void);

	SolidView(void) = delete;
	SolidView(SolidView const &src) = delete;
	SolidView			&operator=(SolidView const &rhs) = delete;

};

};

#endif
