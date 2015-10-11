// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   luaCFunctions_helpers.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:23:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 17:57:35 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LUACFUNCTIONS_HELPERS_HPP
# define LUACFUNCTIONS_HELPERS_HPP

# include "lua/lua.hpp"

namespace ftui
{

/*
**	'luaCFunHelper' functions handle the lua stack inside a lua_CFunction.
** ************************************************************************** **
** 'luaCFunHelper<i,o>(l, f)'		Calls 'f'
** * e.g. ******* **
** // double			std::sqrt(double);
** int					sqrt_lua(lua_State *l)
** { return ftui::luaCFunHelper<1, 1>(l, &std::sqrt); }
** ************************************************************************** **
** ************************************************************************** **
** 'luaCFunHelper<i,o>(l, c, c::f)'	Calls 'c'->*'c::f'
** * e.g. ******* **
** // void				Game::reloadGame(void);
** int					reload_game(lua_State *l)
** { return ftui::luaCFunHelper<0, 0>(l, Game::instance(), &Game::reloadGame); }
** ************************************************************************** **
** ************************************************************************** **
** 'luaCFunHelper<i,o>(l, c::f)'	Expects a self table as first lua argument
**								Looks for 'c' in 'self[0]', calls 'c'->*'c::f'
**								'self' table counts as 1 argument in 'NumIn'
** * e.g. ******* **
** // ft::Vec3<float>	MyView::getColor(void) const;
** int					get_myview_color(lua_State *l)
** { return ftui::luaCFunHelper<1, 3>(l, &MyView::getColor); }
** ************************************************************************** **
*/

template <int NumIn, int NumOut, typename Ret, typename... Args>
int		luaCFunHelper(lua_State *l, Ret (*f)(Args...));

template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, C *i, Ret (C::*f)(Args...));
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, C const *i, Ret (C::*f)(Args...) const);

template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, Ret (C::*f)(Args...));
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, Ret (C::*f)(Args...) const);

/*
** 'luaCFunRetreiveSelf'		1. Looks for a table at index.		(may throw)
**								2. Looks for a userdata at tab[0]	(may throw)
**								3. Pops it from the stack
**								4. Returns it
*/

template <typename T>
T		*luaCFunRetreiveSelf(lua_State *l, int index);


};

# include "ftui/templates/luaCFunctions_helpers.tpp"

#endif
