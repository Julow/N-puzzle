// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_extend.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:20:10 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/21 09:06:07 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTUI_FTLUA_EXTEND_HPP
# define FTUI_FTLUA_EXTEND_HPP

# include "ftlua/ftlua.hpp"

# include "ftui/libftui.hpp"


namespace ftlua
{

template <bool USELUAERR = false>
int			push(lua_State *l, ftui::AView *const &v)
{
	ftlua::push<USELUAERR>(
		l, ftlua::make_keys(reinterpret_cast<void* const&>(v)));
	return 1;
}

template <bool USELUAERR = false>
int			push(lua_State *l, ftui::Canvas *const &v)
{
	ftlua::push<USELUAERR>(
		l, ftlua::make_keys(reinterpret_cast<void* const&>(v)));
	return 1;
}

};

#endif /* ********************************************* FTUI_FTLUA_EXTEND_HPP */
