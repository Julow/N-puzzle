// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventTarget.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/24 13:17:39 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 14:31:09 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/EventTarget.hpp"

namespace ftui // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


EventTarget::EventTarget(AView *v) : _v(v) {}
EventTarget::~EventTarget() {}

AView		*EventTarget::getView(void)
{
	return this->_v;
}

bool		EventTarget::isLuaCall(void) const
{
	return true;
}

bool		EventTarget::cppCall(ft::ITupleRef *)
{
	FTASSERT(false, "Should not be reached");
	return false;
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTUI //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
