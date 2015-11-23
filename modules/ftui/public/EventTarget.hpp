// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventTarget.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 18:21:16 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/23 18:21:34 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVENTTARGET_HPP
# define EVENTTARGET_HPP

// # include <iostream>
// # include <>

// # include ""

namespace ftui // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

class EventTarget
{
public:

	/* CONSTRUCTION ***************** */
	EventTarget();
	// virtual ~EventTarget();
	~EventTarget();

	// EventTarget() = delete;
	EventTarget(EventTarget const &src) = delete;
	EventTarget(EventTarget &&src) = delete;
	EventTarget				&operator=(EventTarget const &rhs) = delete;
	EventTarget				&operator=(EventTarget &&rhs) = delete;

protected:
private:
};

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTUI //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif /* *************************************************** EVENTTARGET_HPP */
