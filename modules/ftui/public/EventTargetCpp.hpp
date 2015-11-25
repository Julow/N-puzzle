// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   EventTargetCpp.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/24 13:20:39 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/25 16:10:39 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVENTTARGETCPP_HPP
# define EVENTTARGETCPP_HPP

# include <typeinfo>
# include <tuple>

# include "EventTarget.hpp"

namespace ftui // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T, class ...Args>
class EventTargetCpp : public EventTarget
{
	using CppFun = bool (T::*)(Args...);
	using FtTuple = ft::TupleRef<Args...>;
public:

	/* CONSTRUCTION ***************** */
	EventTargetCpp(AView *v, CppFun f) : EventTarget(v), _f(f) {}
	~EventTargetCpp() {}

	EventTargetCpp() = delete;
	EventTargetCpp(EventTargetCpp const &src) = delete;
	EventTargetCpp(EventTargetCpp &&src) = delete;
	EventTargetCpp		&operator=(EventTargetCpp const &rhs) = delete;
	EventTargetCpp		&operator=(EventTargetCpp &&rhs) = delete;

	/* BEHAVIOUR ******************** */
	bool				isLuaCall(void) const
		{ return false; }
	bool				cppCall(ft::ITupleRef *tup)
		{
			FtTuple		*tup2 = reinterpret_cast<FtTuple*>(tup);
			// FtTuple		*tup2 = dynamic_cast<FtTuple*>(tup);
			// TODO: custom type checking module. Fun params VS Params

			if (tup2 == nullptr)
				throw std::runtime_error(
					ft::f("Activity::fireEvent(): could not match arguments "
						  "with target function params: bool (%::)(%)"
						  , typeid(T).name(), ft::typesToString<Args...>()));
			return delayed_dispatch(*tup2);
		}

private:

	template<std::size_t ...I>
	bool				call_func(FtTuple &tup, std::index_sequence<I...>)
		{
			T *const	v = reinterpret_cast<T*>(this->_v);

			return (v->*this->_f)(std::get<I>(tup.tup)...);
		}

	bool				delayed_dispatch(FtTuple &tup)
		{
			return this->call_func(tup, std::index_sequence_for<Args...>{});
		}

	CppFun				_f;

};


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTUI //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#endif /* ************************************************ EVENTTARGETCPP_HPP */
