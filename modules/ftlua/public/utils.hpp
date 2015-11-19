// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 14:08:42 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 14:09:29 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_UTILS_HPP
# define FTLUA_UTILS_HPP

# include <string>

# include "liblua/lua.hpp"

namespace ftlua
{

void	pushUtils(lua_State *l);
void	stackdump(lua_State *l);
void	registerLuaCFunTable(
	    lua_State *l
		, std::string const &tabName
		, std::string const &funName
		, lua_CFunction f);

};

#endif
