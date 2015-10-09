// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   luaCFunctions_helpers.tpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/09 09:10:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/09 16:08:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include <iostream>
# include <functional> //TODO move luaFT_stackdump

# include "ft/Vec.hpp"
# include "ft/utils.hpp"

namespace ftui
{

inline void        luaFT_stackdump(lua_State *L) //TODO move luaFT_stackdump
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

/*
** ************************************************************************** //
** * luaCFunHelper ********************************************************** //
** ************************************************************************** //
*/
// * STEP 2 HELPERS ********************************************************* //
namespace internal
{
template <typename T>
constexpr inline int	decay(void){ return 1; }

template <>
constexpr inline int	decay<ft::Vec2<int>>(void){ return 2; }

template <typename T>
inline T				popStack(lua_State *, int)
{
	static_assert(!std::is_same<T, T>::value
				  , "This type is not handled by LOLhelper function.");
	return T();
}

template <>
inline std::string		popStack<std::string>(lua_State *l, int numIn)
{
	std::string			v(luaL_checklstring(l, -numIn, NULL));

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

#define BASICPOPSTACK(TYPE, FUNCTION)							\
template <>														\
inline TYPE				popStack<TYPE>(lua_State *l, int numIn)	\
{																\
	TYPE				v(FUNCTION(l, -numIn));					\
																\
	lua_remove(l, -numIn);										\
	return v;													\
}

BASICPOPSTACK(int, luaL_checkinteger)
BASICPOPSTACK(bool, luaL_checkinteger)
BASICPOPSTACK(float, luaL_checknumber)
BASICPOPSTACK(double, luaL_checknumber)

#undef BASICPOPSTACK

// * STEP 4 HELPERS ********************************************************* //
template <int NumOut, typename Ret,
	typename std::enable_if<!std::is_pointer<Ret>::value>::type* = nullptr>
void					pushStack(lua_State *, Ret&&)
{
	static_assert(!std::is_same<Ret, Ret>::value
				  , "This return type is not supported by LOLhelper function "
				  " or Wrong number of arguments for return value");
	return ;
}

template <int NumOut, typename Ret,
	typename std::enable_if<std::is_pointer<Ret>::value>::type* = nullptr>
void					pushStack(lua_State *, Ret&& r)
{
	static_assert(NumOut == 1, "Wrong number of arguments for return value");
	void *const	ptr = reinterpret_cast<void*>(r);

	std::cout << "faire des trucs sur la stack lua\n";
	(void)ptr;
	//TODO untested + finir
	// static_assert(!std::is_same<Ret, Ret>::value, "truc c'est bon");
	return ;
}

template <> inline void	pushStack<1, std::string>(lua_State *l, std::string&& r)
{ lua_pushstring(l, r.c_str()); }
template <> inline void	pushStack<2, ft::Vec2<int> >(
	lua_State *l, ft::Vec2<int>&& r)
{
	lua_pushinteger(l, r.x);//TODO right order ?
	lua_pushinteger(l, r.y);
	return ;
}

#define BASICPUSHSTACK(TYPE, FUNCTION)								\
template <>															\
inline void				pushStack<1, TYPE>(lua_State *l, TYPE &&r)	\
{																	\
	FUNCTION(l, r);													\
	return ;														\
}

BASICPUSHSTACK(int, lua_pushinteger)
BASICPUSHSTACK(bool, lua_pushinteger)
BASICPUSHSTACK(float, lua_pushnumber)
BASICPUSHSTACK(double, lua_pushnumber)

#undef BASICPUSHSTACK

// * STEP 4 *** Call the function ******************************************* //
// * Function *** //
template <int NumOut, typename Ret, typename... Params>
void	helperCall(lua_State *l, Ret (*f)(Params...), Params ...p)
{
	pushStack<NumOut>(l, f(p...));
	luaFT_stackdump(l);
	return ;
}
template <int NumOut, typename... Params>
void	helperCall(lua_State *l, void (*f)(Params...), Params ...p)
{
	static_assert(NumOut == 0, "Wrong number of arguments for return value");
	f(p...);
	luaFT_stackdump(l);
	return ;
}

// * MemFun ***** //
template <int NumOut, typename Ret, class C, typename... Params>
void	helperCall(lua_State *l, C *i, Ret (C::*f)(Params...), Params ...p)
{
	pushStack<NumOut>(l, (i->*f)(p...));
	luaFT_stackdump(l);
	return ;
}
template <int NumOut, class C, typename... Params>
void	helperCall(lua_State *l, C *i, void (C::*f)(Params...), Params ...p)
{
	static_assert(NumOut == 0, "Wrong number of arguments for return value");
	(i->*f)(p...);
	luaFT_stackdump(l);
	return ;
}

// * STEP 3 *** Clean the function pointer and check NumIn ****************** //
// * Function *** //
template <int NumIn, int NumOut
		  , typename Ret, typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(), Retreived const &&...r)
{
	static_assert(NumIn == 0, "Wrong number of arguments provided");
	helperCall<NumOut>(l, reinterpret_cast<Ret (*)(Retreived...)>(f), r...);
	return ;
}

// * MemFun ***** //
template <int NumIn, int NumOut
		  , typename Ret, class C, typename... Retreived>
void		helperLoop(
	lua_State *l, C *i, Ret (C::*f)(), Retreived const &&...r)
{
	static_assert(NumIn == 0, "Wrong number of arguments provided");
	helperCall<NumOut>(l, i
		, reinterpret_cast<Ret (C::*)(Retreived...)>(f), r...);
	return ;
}

// * STEP 2 *** Loop through arguments to retreive them from the lua Stack ** //
// * Function *** //
template <int NumIn, int NumOut
		  , typename Ret, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(Head, ArgsLeft...), Retreived&&...r)
{
	using HeadCleanRef = typename std::remove_reference<Head>::type;
	using HeadCleanAll = typename std::remove_cv<HeadCleanRef>::type;
	luaFT_stackdump(l);
	HeadCleanAll	p{popStack<HeadCleanAll>(l, NumIn)};
	ft::f(std::cout, "got '%' at index %\n", p, -NumIn);

	helperLoop<NumIn - decay<HeadCleanAll>(), NumOut>(
		l, reinterpret_cast<Ret (*)(ArgsLeft...)>(f)
		, std::forward<Retreived>(r)...
		, std::forward<HeadCleanAll>(p)
		);
	return ;
}

// * MemFun ***** //
template <int NumIn, int NumOut
		  , typename Ret, class C, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(
	lua_State *l, C *i, Ret (C::*f)(Head, ArgsLeft...), Retreived&&...r)
{
	using HeadCleanRef = typename std::remove_reference<Head>::type;
	using HeadCleanAll = typename std::remove_cv<HeadCleanRef>::type;
	luaFT_stackdump(l);
	HeadCleanAll	p{popStack<HeadCleanAll>(l, NumIn)};
	ft::f(std::cout, "got '%' at index %\n", p, -NumIn);

	helperLoop<NumIn - decay<HeadCleanAll>(), NumOut>(
		l, i, reinterpret_cast<Ret (C::*)(ArgsLeft...)>(f)
		, std::forward<Retreived>(r)...
		, std::forward<HeadCleanAll>(p)
		);
	return ;
}
};// end internal //

// * STEP 1 *** Call the helperLoop ***************************************** //
// * Function *** //
template <int NumIn, int NumOut, typename Ret, typename... Args>
int		luaCFunHelper(lua_State *l, Ret (*f)(Args...))
{
	internal::helperLoop<NumIn, NumOut>(l, f);
	return (NumOut);
}

// * MemFun ***** //
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, C *i, Ret (C::*f)(Args...))
{
	internal::helperLoop<NumIn, NumOut>(l, i, f);
	return (NumOut);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, C const *i, Ret (C::*f)(Args...) const)
{
	using F = Ret (C::*)(Args...);
	using FClean = typename std::remove_cv<F>::type;
	using CClean = typename std::remove_cv<C>::type;
	internal::helperLoop<NumIn, NumOut>(
		l, reinterpret_cast<CClean>(i), reinterpret_cast<FClean>(f));
	return (NumOut);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, Ret (C::*f)(Args...))
{
	internal::helperLoop<NumIn - 1, NumOut>(
		l, luaCFunRetreiveSelf<C>(l, -NumIn), f);
	return (NumOut - 1);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		luaCFunHelper(lua_State *l, Ret (C::*f)(Args...) const)
{
	using F = Ret (C::*)(Args...);
	using FClean = typename std::remove_cv<F>::type;
	return (luaCFunHelper<NumIn, NumOut>(l, reinterpret_cast<FClean>(f)));
}

/*
** ************************************************************************** //
** * luaCFunRetreiveSelf **************************************************** //
** ************************************************************************** //
*/

template <typename T>
inline T	*luaCFunRetreiveSelf(lua_State *l, int index)
{
	void		*i;

	if (!lua_istable(l, index))
		throw std::runtime_error(ft::f("Lua stack: bad argument at index %",
			index));
	lua_pushinteger(l, 0);
	if (lua_gettable(l, index - 1) != LUA_TLIGHTUSERDATA)
		throw std::runtime_error(ft::f("Lua stack: Corrupted table at index %",
			index));
	i = lua_touserdata(l, -1);
	lua_pop(l, 1);
	lua_remove(l, index);
	return (reinterpret_cast<T*>(i));
}
};
