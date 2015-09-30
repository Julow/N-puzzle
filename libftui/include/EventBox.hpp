// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventBox.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 09:44:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/30 09:57:58 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVENTBOX_HPP
# define EVENTBOX_HPP

# include "IEventBox.hpp"

template<class T, typename... ARGS>
class ftui::EventBox : public IEventBox
{
private:
	typedef void					(T::*fun_t)(ARGS...);
	typedef std::tuple<ARGS...>		tuple_t;

	T					*_v;
	fun_t				_f;

public:

	EventBox(AView *v, fun_t f) : _v(static_cast<T*>(v)) , _f(f) {}
	virtual ~EventBox(){};

	void				call(IEventParams *a_)
		{
			EventParams<ARGS...>	 *a;

			a = reinterpret_cast<EventParams<ARGS...>*>(a_);
			delayed_dispatch(a->tup);
			return ;
		}

private:
	template<std::size_t ...I>
	void				call_func(tuple_t params, std::index_sequence<I...>)
		{
			((this->_v)->*(this->_f))(std::get<I>(params)...);
			return ;
		}
	void				delayed_dispatch(tuple_t params)
		{
			call_func(params, std::index_sequence_for<ARGS...>{});
			return ;
		}

	EventBox() = delete;
	EventBox(EventBox const &) = delete;
	EventBox					&operator=(EventBox const &) = delete;
};

#endif // ****************************************************** EVENTBOX_HPP //
