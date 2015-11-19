// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_extend.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:20:10 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 12:59:36 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_EXTEND_HPP
# define FTLUA_EXTEND_HPP

# include "ftlua/ftlua.hpp"

# include "AView.hpp"

namespace ftlua
{

template <bool USELUAERR = false>
int			push(lua_State *l, AView *const &v)
{
	// push(reinterpret_cast<void*const&>(v));
	return 1;
}

};

#endif /* ************************************************** FTLUA_EXTEND_HPP */
