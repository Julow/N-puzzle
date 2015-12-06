// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 07:39:43 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/06 13:09:03 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_HPP
# define FTLUA_HPP

# include <string>

# include "liblua/lua.hpp"

# include "ftlua/types.hpp"
# include "ftlua/push.hpp"
# include "ftlua/pop.hpp"
# include "ftlua/utils.hpp"
# include "ftlua/call.hpp"
# include "ftlua/set.hpp"
# include "ftlua/light.hpp"
# include "ftlua/stackassert.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


/*
** ========================================================================== **
** Handler
*/

/*
**	'handle' functions handle the lua stack inside a lua_CFunction.
** ************************************************************************** **
** 'handle<i,o>(l, f)'		Calls 'f'
** * e.g. ******* **
** // double			std::sqrt(double);
** int					sqrt_lua(lua_State *l)
** { return ftui::handle<1, 1>(l, &std::sqrt); }
** ************************************************************************** **
** ************************************************************************** **
** 'handle<i,o>(l, c, c::f)'	Calls 'c'->*'c::f'
** * e.g. ******* **
** // void				Game::reloadGame(void);
** int					reload_game(lua_State *l)
** { return ftui::handle<0, 0>(l, Game::instance(), &Game::reloadGame); }
** ************************************************************************** **
** ************************************************************************** **
** 'handle<i,o>(l, c::f)'	Expects a self table as first lua argument
**								Looks for 'c' in 'self[0]', calls 'c'->*'c::f'
**								'self' table counts as 1 argument in 'NumIn'
** * e.g. ******* **
** // ft::Vec3<float>	MyView::getColor(void) const;
** int					get_myview_color(lua_State *l)
** { return ftui::handle<1, 3>(l, &MyView::getColor); }
** ************************************************************************** **
*/
template <int NumIn, int NumOut, typename Ret, typename... Args>
int			handle(lua_State *l, Ret (*f)(Args...));

template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int			handle(lua_State *l, C *i, Ret (C::*f)(Args...));

template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int			handle(lua_State *l, Ret (C::*f)(Args...));
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int			handle(lua_State *l, Ret (C::*f)(Args...) const);

}; // ~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# include "ftlua/templates/ftlua_handler.tpp"

#endif
