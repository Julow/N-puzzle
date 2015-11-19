// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 07:39:43 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 17:10:18 by ngoguey          ###   ########.fr       //
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

namespace ftlua
{

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
int			handle(lua_State *l, C const *i, Ret (C::*f)(Args...) const);

template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int			handle(lua_State *l, Ret (C::*f)(Args...));
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int			handle(lua_State *l, Ret (C::*f)(Args...) const);

/*
** ========================================================================== **
** Caller
*/

/*
** Call the function 'name' in the table currently on the top of the stack
** -
** A table or the global table have to be on the top of the stack
*/
template<typename ...ARGS>
void		call(lua_State *l, std::string const &name, ARGS ...args);

/*
** Call a lua function that is already on the top of the lua stack
** -
** n_args is the count of argument already pushed on the stack or 0
*/
template<size_t N, typename ...ARGS>
void		call(lua_State *l, ARGS ...args);


/*
** 'retrieveSelf'				1. Looks for a table at index.		(may throw)
**								2. Looks for a userdata at tab[0]	(may throw)
**								3. Pops it from the stack
**								4. Returns it
*/

template <typename T>
T					*retrieveSelf(lua_State *l, int index, bool pop = true);

};

# include "ftlua/templates/ftlua_handler.tpp"
# include "ftlua/templates/ftlua_caller.tpp"

#endif
