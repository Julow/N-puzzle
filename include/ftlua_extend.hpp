// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_extend.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/11 16:30:35 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 16:30:55 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_EXTEND_HPP
# define FTLUA_EXTEND_HPP

#include "ftlua/ftlua.hpp"
#include "Grid.hpp"

namespace ftlua
{

int			pushgrid(lua_State *l, Grid const &gr);

};

#endif // ************************************************** FTLUA_EXTEND_HPP //
