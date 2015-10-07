// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   luaCFunctions_helpers.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:23:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/07 18:55:17 by juloo            ###   ########.fr       //
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

// * STEP 2 HELPERS ********************************************************* //
template <typename T>
constexpr inline int	decay(){ return 1; }

template <>
constexpr inline int	decay<ft::Vec2<int>>(){ return 2; }

template <typename T>
inline T				popStack(lua_State *, int)
{
	static_assert(!std::is_same<T, T>::value
				  , "This type is not handled by LOLhelper function.");
	return T();
}

template <>
inline double			popStack<double>(lua_State *l, int numIn)
{
	double				v(luaL_checknumber(l, -numIn));

	lua_remove(l, -numIn);
	return v;
}

template <>
inline std::string		popStack<std::string>(lua_State *l, int numIn)
{
	std::string			v(luaL_checklstring(l, -numIn, NULL));

	lua_remove(l, -numIn);
	return v;
}

template <>
inline int				popStack<int>(lua_State *l, int numIn)
{
	int					v(luaL_checkinteger(l, -numIn));

	lua_remove(l, -numIn);
	return v;
}

template <>
inline ft::Vec2<int>	popStack<ft::Vec2<int>>(lua_State *l, int numIn)
{
	ft::Vec2<int>		v(
		luaL_checkinteger(l, -numIn), luaL_checkinteger(l, -numIn + 1));

	lua_remove(l, -numIn + 1);
	lua_remove(l, -numIn + 1);
	return v;
}

// * STEP 4 HELPERS ********************************************************* //
template <int NumOut, typename Ret>
void					pushStack(lua_State *, Ret&&)
{
	static_assert(!std::is_same<Ret, Ret>::value
				  , "This return type is not supported by LOLhelper function "
				  " or Wrong number of arguments for return value");
	return ;
}

template <> inline void		pushStack<1, double>(lua_State *l, double&& r)
{ lua_pushnumber(l, r); }
template <> inline void		pushStack<1, int>(lua_State *l, int&& r)
{ lua_pushinteger(l, r); }
template <> inline void		pushStack<1, std::string>(lua_State *l, std::string&& r)
{ lua_pushstring(l, r.c_str()); }
template <> inline void		pushStack<2, ft::Vec2<int> >(
	lua_State *l, ft::Vec2<int>&& r)
{
	lua_pushinteger(l, r.x);//TODO right order ?
	lua_pushinteger(l, r.y);
	return ;
}

// * STEP 4 *** Call the function ******************************************* //
template <int NumOut, typename Ret, typename... Params>
void		helperCall(lua_State *l, Ret (*f)(Params...), Params ...p)
{
	pushStack<NumOut>(l, f(p...));
	luaFT_stackdump(l);
	return ;
}

template <int NumOut, typename... Params>
void		helperCall(lua_State *l, void (*f)(Params...), Params ...p)
{
	static_assert(NumOut == 0, "Wrong number of arguments for return value");
	f(p...);
	luaFT_stackdump(l);
	return ;
}

// * STEP 3 *** Clean the function pointer and check NumIn ****************** //
template <int NumIn, int NumOut
		  , typename Ret, typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(), Retreived const &&...r)
{
	static_assert(NumIn == 0, "Wrong number of arguments provided");
	std::cout << "Calling now!!!\n";
	helperCall<NumOut>(l, reinterpret_cast<Ret (*)(Retreived...)>(f), r...);
	return ;
}

// * STEP 2 *** Loop through arguments to retreive them from the lua Stack ** //
template <int NumIn, int NumOut
		  , typename Ret, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(Head, ArgsLeft...), Retreived&&...r)
{
	luaFT_stackdump(l);
	Head		p{popStack<Head>(l, NumIn)};
	ft::f(std::cout, "got '%' at index %\n", p, -NumIn);

	helperLoop<NumIn - decay<Head>(), NumOut>(
		l, reinterpret_cast<Ret (*)(ArgsLeft...)>(f)
		, std::forward<Retreived>(r)...
		, std::forward<Head>(p)
		);
	return ;
}

// * STEP 1 *** Call the helperLoop ***************************************** //
// * Function *** //
template <int NumIn, int NumOut, typename Ret, typename... Args>
int			helperFun(lua_State *l, Ret (*f)(Args...))
{
	std::cout << "helperFun entry\n";
	helperLoop<NumIn, NumOut>(l, f);
	return (NumOut);
}

// * MemFun ***** //


};

#endif
