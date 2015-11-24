// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventTarget.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/24 13:08:54 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 19:46:29 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVENTTARGET_HPP
# define EVENTTARGET_HPP

# include "ft/TupleRef.hpp"
# include "libftui.hpp"

namespace ftui // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


class EventTarget
{
public:

	/* CONSTRUCTION ***************** */
	EventTarget(AView *v);
	virtual ~EventTarget();

	EventTarget() = delete;
	EventTarget(EventTarget const &src) = delete;
	EventTarget(EventTarget &&src) = delete;
	EventTarget				&operator=(EventTarget const &rhs) = delete;
	EventTarget				&operator=(EventTarget &&rhs) = delete;


	/* BEHAVIOUR ******************** */
	AView					*getView(void);
	virtual bool			isLuaCall(void) const;
	virtual bool			cppCall(ft::ITupleRef *tup);

	template <Args...>
	bool					isCompatible();

protected:
	AView					*_v;

};


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTUI //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif /* *************************************************** EVENTTARGET_HPP */
