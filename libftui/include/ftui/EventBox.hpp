/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventBox.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 09:44:31 by ngoguey           #+#    #+#             */
//   Updated: 2015/10/05 17:40:08 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTBOX_HPP
# define EVENTBOX_HPP

# include "ftui/IEventBox.hpp"
# include "ft/assert.hpp"

template<class T, typename... Args>
class ftui::EventBox : public IEventBox
{
private:
	typedef bool					(T::*fun_t)(Args...);
	typedef std::tuple<Args...>		tuple_t;

	T					*_v;
	fun_t				_f;

public:

	EventBox(AView *v, fun_t f) : _v(reinterpret_cast<T*>(v)) , _f(f) {}
	virtual ~EventBox(){};

	bool				call(std::string const &str, IEventParams *a_)
		{
			EventParams<Args...>	 *a;

 			FTASSERT(dynamic_cast<EventParams<Args...>*>(a_) != nullptr
					 , "Wrong parameters type to " + str + " call");
			a = reinterpret_cast<EventParams<Args...>*>(a_);
			return delayed_dispatch(a->tup);
		}
	AView const			*getView(void) const
		{
			return (this->_v);
		}

private:
	template<std::size_t ...I>
	bool				call_func(tuple_t params, std::index_sequence<I...>)
		{
			return ((this->_v)->*(this->_f))(std::get<I>(params)...);
		}
	bool				delayed_dispatch(tuple_t params)
		{
			return call_func(params, std::index_sequence_for<Args...>{});
		}

	EventBox() = delete;
	EventBox(EventBox const &) = delete;
	EventBox					&operator=(EventBox const &) = delete;
};

#endif // ****************************************************** EVENTBOX_HPP //
