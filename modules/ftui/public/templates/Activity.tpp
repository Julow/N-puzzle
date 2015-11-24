/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 09:01:50 by ngoguey           #+#    #+#             */
//   Updated: 2015/11/24 19:25:10 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "ftui/EventTarget.hpp"
#include "ftui/EventTargetCpp.hpp"

#include "ftui/AView.hpp"

namespace ftui
{

/*
** ************************************************************************** **
** Render-time -> instance.*Event       (more in Activity.cpp)
*/

template<class T, typename... Args>
void		Activity::registerEvent(std::string const &event, T *v
									, bool (T::*f)(Args...))
{
	this->_eventMap.insert(std::make_pair(
							   event, new EventTargetCpp<T, Args...>(v, f)));
	return ;
}

template<typename... Args>
bool		Activity::fireEvent(std::string const &event, Args... args)
{
	auto			it = this->_eventMap.find(event);
	auto const		ite = this->_eventMap.cend();
	int				err;
	bool			ret(false);

	for (; it != ite; it++)
	{
		if (it->second->isLuaCall())
		{
			ftlua::multiPush(_l, it->second->getView(), event);	// "", []
			FTLUA_STACKASSERT(
				_l, lua_istable(_l, -2), false
				, ft::f("Activity::fireEvent(event=%, %)"
						, event, ft::variadicToString(args...))
				, ft::f("Could not retreive _G[%]",
						reinterpret_cast<void*>(it->second->getView())));
			lua_gettable(_l, -2);								// f, []
			if (lua_isnil(_l, -1))
			{
				lua_pop(_l, 1);									// []
				lua_pushliteral(_l, "onEvent");					// "", []
				lua_gettable(_l, -2);							// f, []
			}
			FTLUA_STACKASSERT(
				_l, lua_isfunction(_l, -1), false
				, ft::f("Activity::fireEvent(event=%, %)"
						, event, ft::variadicToString(args...))
				, ft::f("Could not find a suitable function in table"));
			err = ftlua::pcall(_l, 0, 0, ftlua::dup(-2), args...);
			if (err != LUA_OK)
				throw std::runtime_error(
					ft::f("% error ffs", ftlua::stacktostring(_l)));
			lua_pop(_l, 1);
		}
		else
		{
			ret |= it->second->cppCall(
// (ft::ITupleRef[]){ft::make_tupleref(args...)}
// This line fucks the pointer, TODO: talk about it
				(ft::TupleRef<Args...>[]){ft::make_tupleref(args...)}
				);
		}
	}
	return ret; //test
}

};
