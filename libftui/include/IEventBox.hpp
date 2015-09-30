// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IEventBox.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 09:49:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/30 10:02:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IEVENTBOX_HPP
# define IEVENTBOX_HPP

# include "libftui.h"

class ftui::IEventBox
{
public:
	IEventBox(){}
	virtual ~IEventBox(){}

	virtual bool			call(IEventParams *a_) = 0;
	
private:
	IEventBox(IEventBox const &src) = delete;
	IEventBox				&operator=(IEventBox const &rhs) = delete;

};

#endif // ***************************************************** IEVENTBOX_HPP //