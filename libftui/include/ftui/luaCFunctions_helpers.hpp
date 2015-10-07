// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   luaCFunctions_helpers.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:23:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/06 12:42:52 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef LUACFUNCTIONS_HELPERS_HPP
# define LUACFUNCTIONS_HELPERS_HPP

#include "ftui/libftui.hpp"

# include <iostream>
# include <functional>

# include "ft/Vec.hpp"
# include "ft/utils.hpp"

namespace ftui
{


inline void        luaFT_stackdump(lua_State *L)
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
		[=, &i](){std::cout << "   tab" << "\n";},
		[=, &i](){std::cout << "  func: " << (void*)lua_tocfunction(L, i) << "\n";},
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

template <typename T>
constexpr inline int	decay(){ return 1; }

template <>
constexpr inline int	decay<ft::Vec2<int>>(){ return 2; }

template <typename T>
inline T			retreiveParam(lua_State *, int)
{
	static_assert(!std::is_same<T, T>::value
				  , "This type is not handled by LOLhelper function.");
	return T();
}

template <>
inline double		retreiveParam<double>(lua_State *l, int numIn)
{
	double			v(luaL_checknumber(l, -numIn));

	lua_remove(l, -numIn);
	return v;
}

template <>
inline std::string		retreiveParam<std::string>(lua_State *l, int numIn)
{
	std::string		v(luaL_checklstring(l, -numIn, NULL));

	lua_remove(l, -numIn);
	return v;
}

template <>
inline int				retreiveParam<int>(lua_State *l, int numIn)
{
	int				v(luaL_checkinteger(l, -numIn));

	lua_remove(l, -numIn);
	return v;
}

template <>
inline ft::Vec2<int>	retreiveParam<ft::Vec2<int>>(lua_State *l, int numIn)
{
	ft::Vec2<int>	v(luaL_checkinteger(l, -numIn)
					  , luaL_checkinteger(l, -numIn + 1));

	lua_remove(l, -numIn + 1);
	lua_remove(l, -numIn + 1);
	return v;
}



template <int NumIn, int NumOut
		  , typename Ret, typename... Retreived>
void		helperLoop(lua_State *, Ret (*f)(), Retreived const &&...r)
{
	std::cout << "Calling now!!!\n";
	reinterpret_cast<Ret (*)(Retreived...)>(f)(r...);
	return ;
}

template <int NumIn, int NumOut
		  , typename Ret, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(lua_State *l, Ret (*f)(Head, ArgsLeft...), Retreived&&...r)
{
	luaFT_stackdump(l);
	Head		p{retreiveParam<Head>(l, NumIn)};
	ft::f(std::cout, "got '%' at index %\n", p, -NumIn);

	helperLoop<NumIn - decay<Head>(), NumOut>(
		l, reinterpret_cast<Ret (*)(ArgsLeft...)>(f)
		, std::forward<Retreived>(r)...
		, std::forward<Head>(p)
		);
	return ;
}

// * Fun ******** //
template <int NumIn, int NumOut, typename Ret, typename... Args>
int			helperFun(lua_State *l, Ret (*f)(Args...))
{
	std::cout << "helperFun entry\n";
	helperLoop<NumIn, NumOut>(l, f);
	return (0);
}

// * MemFun ***** //


};

#endif
