// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventBox.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/30 09:44:31 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/13 09:34:59 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVENTBOX_HPP
# define EVENTBOX_HPP

# include "ftui/IEventBox.hpp"

namespace ftui
{

template<class T, typename... Args>
class EventBox : public IEventBox
{
public:
	typedef bool					(T::*fun_t)(Args...);
	typedef std::tuple<Args...>		tuple_t;

	EventBox(AView *v, fun_t f);
	virtual ~EventBox(void);

	bool				call(std::string const &str, IEventParams *a_);

	AView const			*getView(void) const;

protected:
	T					*_v;
	fun_t				_f;

	template<std::size_t ...I>
	bool				call_func(tuple_t params, std::index_sequence<I...>);

	bool				delayed_dispatch(tuple_t params);

private:
	EventBox(void) = delete;
	EventBox(EventBox const &) = delete;
	EventBox			&operator=(EventBox const &) = delete;
};

};

# include "ftui/templates/EventBox.tpp"

#endif
