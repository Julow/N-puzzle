/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 09:01:50 by ngoguey           #+#    #+#             */
//   Updated: 2015/11/23 19:50:21 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */


namespace ftui
{

/*
** ************************************************************************** **
** Render-time -> instance.*Event       (more in Activity.cpp)
*/

// template<typename... Args>
// void		Activity::registerEvent(std::string const &event, AView *v)
// {
// 	IEventBox               *ab;

// 	ab = new DefaultEventBox<Args...>(v);
// 	this->_eventMap.insert(std::make_pair(event, ab));
// 	return ;
// }

// template<class T, typename... Args>
// void		Activity::registerEvent(std::string const &event, AView *v
// 									  , bool (T::*callback_)(Args...))
// {
// 	IEventBox               *ab;

// 	ab = new EventBox<T, Args...>(v, callback_);
// 	this->_eventMap.insert(std::make_pair(event, ab));
// 	return ;
// }

template<typename... Args>
bool		Activity::fireEvent(std::string const &, Args... )
// bool		Activity::fireEvent(std::string const &event, Args... args)
{
	// auto			it = this->_eventMap.find(event);
	// auto const		ite = this->_eventMap.cend();
	// int				err;

	// for (; it != ite; it++)
	// {
	// 	if (it->second->isLuaCall())
	// 	{
	// 		ftlua::multiPush(_l, it->second->getView(), event);		// "", []
	// 		if (!lua_istable(_l, -2))
	// 			throw std::runtime_error("TODO");
	// 		lua_gettable(_l, -2);									// f, []
	// 		if (lua_isnil(_l, -1))
	// 		{
	// 			lua_pop(_l, 1);										// []
	// 			err = ftlua::pcallMethod(
	// 				_l, 0, ftlua::make_keys("onEvent"), event, args...);
	// 		}
	// 		else
	// 		{
	// 			err = ftlua::pcall(_l, 0, 0, ftlua::dup(-2), args...);
	// 			lua_pop(_l, 1);
	// 		}
	// 		if (err != LUA_OK)
	// 			throw std::runtime_error("TODO2");
	// 	}
	// 	else
	// 	{

	// 	}
	// }
	// return (true); //test
}

};
