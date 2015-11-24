/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 09:01:50 by ngoguey           #+#    #+#             */
//   Updated: 2015/11/24 16:33:10 by ngoguey          ###   ########.fr       //
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

	for (; it != ite; it++)
	{
		if (it->second->isLuaCall())
		{
			ftlua::multiPush(_l, it->second->getView(), event);		// "", []
			FTLUA_STACKASSERT(
				_l, lua_istable(_l, -2), false
				, ft::f("Activity::fireEvent(%, %)"
						, event, ft::variadicToString(args...))
				, ft::f("Could not retreive _G[%]",
						reinterpret_cast<void*>(it->second->getView())));
			lua_gettable(_l, -2);									// f, []
			if (lua_isnil(_l, -1))
			{
				lua_pop(_l, 1);										// []
				err = ftlua::pcallMethod(
					_l, 0, ftlua::make_keys("onEvent"), event, args...);
			}
			else
			{
				err = ftlua::pcall(_l, 0, 0, ftlua::dup(-2), args...);
				lua_pop(_l, 1);
			}
			if (err != LUA_OK)
				throw std::runtime_error("TODO2");
		}
		else
		{
			it->second->cppCall(
				(ft::ITupleRef[]){ft::make_tupleref(args...)}
				);
		}
	}
	// FTPADE();
	return (true); //test
}

};
