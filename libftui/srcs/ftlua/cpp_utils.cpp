// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cpp_utils.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 07:59:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/13 09:11:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftlua/ftlua.hpp"

#include <iostream>
#include <functional>

namespace ftlua
{

void		stackdump(lua_State *L) //TODO move luaFT_stackdump
{
	int const               top = lua_gettop(L);
	int                     i;
	std::function<void()>   funcs[] =
	{
		[=, &i](){std::cout << "  none" << "\n";},
		[=, &i](){std::cout << "   nil" << "\n";},
		[=, &i](){std::cout << "  bool: " << lua_toboolean(L, i) << "\n";},
		[=, &i](){std::cout << " lusrd" << "\n";},
		[=, &i](){std::cout << "   nbr: " << lua_tonumber(L, i) <<  "\n";},
		[=, &i](){std::cout << "   str: " << lua_tostring(L, i) << "\n";},
		[=, &i](){std::cout << "   tab: "<<(void*)lua_topointer(L, i) << "\n";},
		[=, &i](){std::cout << "  func: "<<(void*)lua_tocfunction(L, i) << "\n";},
		[=, &i](){std::cout << "  usrd" << "\n";},
		[=, &i](){std::cout << "thread" << "\n";},
	};
	std::cout << "Stack dump: " << top << " Elements" << std::endl;
	for (i = 1; i <= top; i++)
	{
		std::cout << "[" << i << "]";
		funcs[lua_type(L, i) + 1]();
	}
	return ;
}

};
