// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IEventBox.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 09:49:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/13 09:32:27 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IEVENTBOX_HPP
# define IEVENTBOX_HPP

# include "ftui/libftui.hpp"

namespace ftui
{

class IEventBox
{
public:
	virtual ~IEventBox(void) {}

	virtual bool			call(std::string const &ev, IEventParams *a_) = 0;
	virtual AView const		*getView(void) const = 0;
};

};

#endif
