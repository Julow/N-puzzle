// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolidView.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/10 17:50:52 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 19:00:01 by jaguillo         ###   ########.fr       //
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
	static AView		*createView(ftui::Activity &act);

	SolidView(Activity &act, std::string const &viewName = "SolidView");
	virtual ~SolidView(void);

private:
	SolidView(void) = delete;
	SolidView(SolidView const &src) = delete;
	SolidView			&operator=(SolidView const &rhs) = delete;
};

};

#endif
