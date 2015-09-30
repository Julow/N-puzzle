// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.tpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 09:01:50 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/30 10:01:00 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "EventBox.hpp"
#include "EventParams.hpp"

namespace ftui
{

template<class T, typename... Args>
void		Activity::storeEvent(std::string const &event, AView *v
							   , void (T::*callback_)(Args...))
{
	IEventBox               *ab;

	ab = new EventBox<T, Args...>(v, callback_);
	this->_eventMap.insert(std::make_pair(event, ab));
	return ;
}

template<typename... Args>
bool		Activity::fireEvent(std::string const &event, Args... args)
{
	auto                	it = this->_eventMap.find(event);
	auto const				ite = this->_eventMap.cend();
	EventParams<Args...>	ar[1];

	ar->tup = std::make_tuple(args...);
	for (; it != ite; it++)
	{
		it->second->call(ar);
	}
	return (true);
}

};
