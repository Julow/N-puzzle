/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 09:01:50 by ngoguey           #+#    #+#             */
//   Updated: 2015/12/06 10:14:06 by ngoguey          ###   ########.fr       //
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
bool		Activity::fireEventInternal(std::string const &event, Args... args)
{
	auto			itpair = this->_eventMap.equal_range(event);
	auto			it = itpair.first;
	auto const		ite = itpair.second;
	int				err;
	bool			ret(false);
	bool			pushName;

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
				pushName = true;
			}
			else
				pushName = false;
			FTLUA_STACKASSERT(
				_l, lua_isfunction(_l, -1), false
				, ft::f("Activity::fireEvent(event=%, %)"
						, event, ft::variadicToString(args...))
				, ft::f("Could not find a suitable function in table"));
			if (pushName)
				err = ftlua::pcall(_l, 0, 0, ftlua::dup(-2), event, args...);
			else
				err = ftlua::pcall(_l, 0, 0, ftlua::dup(-2), args...);
			if (err != LUA_OK)
				throw std::runtime_error(
					ft::f("Activity::fireEvent(event=%, %) failed from:\n%"
						  , event, ft::variadicToString(args...), luaL_checkstring(_l, -1)));
			lua_pop(_l, 1);
		}
		else
		{
			ret |= it->second->cppCall(
				(ft::TupleRef<Args...>[]){ft::make_tupleref(args...)});
		}
	}
	return ret;
}

template<typename... Args>
bool		Activity::fireEvent(std::string const &event, Args... args)
{
	this->cleanEventMap();
	return this->fireEventInternal(event, args...);
}

};
