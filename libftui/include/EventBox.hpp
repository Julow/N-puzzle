// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventBox.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 09:44:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/30 11:47:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVENTBOX_HPP
# define EVENTBOX_HPP

# include "IEventBox.hpp"

template<class T, typename... ARGS>
class ftui::EventBox : public IEventBox
{
private:
	typedef bool					(T::*fun_t)(ARGS...);
	typedef std::tuple<ARGS...>		tuple_t;

	T					*_v;
	fun_t				_f;

public:

	EventBox(AView *v, fun_t f) : _v(reinterpret_cast<T*>(v)) , _f(f) {}
	virtual ~EventBox(){};

	bool				call(std::string const &, IEventParams *a_)
		{
			EventParams<ARGS...>	 *a;

			a = reinterpret_cast<EventParams<ARGS...>*>(a_);
			return delayed_dispatch(a->tup);
		}

private:
	template<std::size_t ...I>
	bool				call_func(tuple_t params, std::index_sequence<I...>)
		{
			return ((this->_v)->*(this->_f))(std::get<I>(params)...);
		}
	bool				delayed_dispatch(tuple_t params)
		{
			return call_func(params, std::index_sequence_for<ARGS...>{});
		}

	EventBox() = delete;
	EventBox(EventBox const &) = delete;
	EventBox					&operator=(EventBox const &) = delete;
};

#endif // ****************************************************** EVENTBOX_HPP //
