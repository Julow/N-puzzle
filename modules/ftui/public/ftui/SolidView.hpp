// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:50:52 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/16 20:16:55 by ngoguey          ###   ########.fr       //
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
	SolidView(Activity &act, ft::XmlParser const &xml);
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
	static AView		*createView(ftui::Activity &act
									, ft::XmlParser const *xml = nullptr
									, std::string const *id = nullptr);

};

};

#endif
