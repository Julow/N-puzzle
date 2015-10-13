// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventBox.tpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 09:19:14 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/13 09:40:51 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "ft/assert.hpp"

namespace ftui
{

template<class T, typename... Args>
EventBox<T, Args...>::EventBox(AView *v, EventBox<T, Args...>::fun_t f) :
	_v(reinterpret_cast<T*>(v)),
	_f(f)
{
}

template<class T, typename... Args>
EventBox<T, Args...>::~EventBox(void)
{
}

template<class T, typename... Args>
bool		EventBox<T, Args...>::call(std::string const &str, IEventParams *a_)
{
	EventParams<Args...>	*a;

		FTASSERT(dynamic_cast<EventParams<Args...>*>(a_) != nullptr,
			"Wrong parameters type to " + str + " call");
	a = reinterpret_cast<EventParams<Args...>*>(a_);
	return delayed_dispatch(a->tup);
}

template<class T, typename... Args>
AView const	*EventBox<T, Args...>::getView(void) const
{
	return (this->_v);
}

template<class T, typename... Args>
template<std::size_t ...I>
bool		EventBox<T, Args...>::call_func(EventBox::tuple_t params,
				std::index_sequence<I...>)
{
	return (((this->_v)->*(this->_f))(std::get<I>(params)...));
}

template<class T, typename... Args>
bool		EventBox<T, Args...>::delayed_dispatch(EventBox::tuple_t params)
{
	return (call_func(params, std::index_sequence_for<Args...>{}));
}

};
