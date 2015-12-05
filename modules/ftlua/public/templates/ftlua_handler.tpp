// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_handler.tpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/09 09:10:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 10:22:13 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <type_traits>
#include <typeinfo>

#include "ft/Vec.hpp"
#include "ft/utils.hpp"
#include "ft/assert.hpp"

#include "ftlua/push.hpp"
#include "ftlua/size.hpp"


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// * STEP 2 HELPERS ********************************************************* //
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

BASICPOPSTACK(std::string, luaL_checkstring)
BASICPOPSTACK(int, luaL_checkinteger)
BASICPOPSTACK(unsigned int, luaL_checkinteger)
// BASICPOPSTACK(uint32_t, luaL_checkinteger)
BASICPOPSTACK(bool, luaL_checkinteger)
BASICPOPSTACK(float, luaL_checknumber)
BASICPOPSTACK(double, luaL_checknumber)

#undef BASICPOPSTACK

// * STEP 5 *** Push return value on stack ********************************** //
template <class T>
void	stackPush(lua_State *l, T &val)
{
	ftlua::push<true>(l, val);
	return ;
}

template <class T>
void	stackPush(lua_State *l, T const &val)
{
	ftlua::push<true>(l, val);
	return ;
}

// * STEP 4 *** Call the function ******************************************* //
// * Function *** //
template <int NumOut, typename Ret, typename... Params>
void	helperCall(lua_State *l, Ret (*f)(Params...), Params ...p)
{
	int const	npushed = NumOut; // tmp

	stackPush(l, f(p...));
	FTLUA_STACKASSERT(
		l, npushed == NumOut, true
		, ft::f("ftlua::handle(% (*)(%))."
				, typeid(Ret).name()
				, ft::variadicToString(p...))
		, ft::f("Pushed % out of %", npushed, NumOut)
		);
	return ;
}
template <int NumOut, typename... Params>
void	helperCall(lua_State *, void (*f)(Params...), Params ...p)
{
	static_assert(NumOut == 0, "Wrong number of arguments for return value");

	f(p...);
	return ;
}

// * MemFun ***** //
template <int NumOut, typename Ret, class C, typename... Params>
void	helperCall(lua_State *l, C *i, Ret (C::*f)(Params...), Params ...p)
{
	int const	npushed = NumOut; // tmp

	stackPush(l, (i->*f)(p...));
	FTLUA_STACKASSERT(
		l, npushed == NumOut, true
		, ft::f("ftlua::handle(% (%::*)(%))."
				, typeid(Ret).name()
				, typeid(C).name()
				, ft::variadicToString(p...))
		, ft::f("Pushed % out of %", npushed, NumOut)
		);
	return ;
}
template <int NumOut, class C, typename... Params>
void	helperCall(lua_State *, C *i, void (C::*f)(Params...), Params ...p)
{
	static_assert(NumOut == 0, "Wrong number of arguments for return value");

	(i->*f)(p...);
	return ;
}

// * STEP 3 *** Restore the function pointer and check NumIn **************** //
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

	HeadCleanAll	p{popStack<HeadCleanAll>(l, NumIn)};

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

	HeadCleanAll	p{popStack<HeadCleanAll>(l, NumIn)};

	helperLoop<NumIn - decay<HeadCleanAll>(), NumOut>(
		l, i, reinterpret_cast<Ret (C::*)(ArgsLeft...)>(f)
		, std::forward<Retreived>(r)...
		, std::forward<HeadCleanAll>(p)
		);
	return ;
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// * STEP 1 *** Call the helperLoop ***************************************** //
// * Function *** //
template <int NumIn, int NumOut, typename Ret, typename... Args>
int		handle(lua_State *l, Ret (*f)(Args...))
{
	internal::helperLoop<NumIn, NumOut>(l, f);
	return (NumOut);
}

// * MemFun ***** //
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, C *i, Ret (C::*f)(Args...))
{
	internal::helperLoop<NumIn, NumOut>(l, i, f);
	return (NumOut);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, C const *i, Ret (C::*f)(Args...) const)
{
	using FClean = Ret (C::*)(Args...);
	using CClean = C*;

	internal::helperLoop<NumIn, NumOut>(
		l, const_cast<CClean>(i), reinterpret_cast<FClean>(f));
	// TODO: sorry world this is a const_cast :( TODO: fix_later
	return (NumOut);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, Ret (C::*f)(Args...))
{
	internal::helperLoop<NumIn - 1, NumOut>(
		l, retrieveSelf<C>(l, -NumIn), f);
	return (NumOut);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, Ret (C::*f)(Args...) const)
{
	using F = Ret (C::*)(Args...);
	using FClean = typename std::remove_cv<F>::type;

	return (handle<NumIn, NumOut>(l, reinterpret_cast<FClean>(f)));
}




template <typename T> //TODO: get rid of this
T		*retrieveSelf(lua_State *l, int index, bool pop)
{
	void		*i;

	if (!lua_istable(l, index))
		luaL_error(l, "Lua stack: bad argument at index %d", index);
	lua_pushinteger(l, 0);
	if (index < 0)
	{
		if (lua_gettable(l, index - 1) != LUA_TLIGHTUSERDATA)
			luaL_error(l, "Missing luserdata at self[0] in table");
	}
	else
	{
		if (lua_gettable(l, index) != LUA_TLIGHTUSERDATA)
			luaL_error(l, "Missing luserdata at self[0] in table");
	}
	i = lua_touserdata(l, -1);
	lua_pop(l, 1);
	if (pop)
		lua_remove(l, index);
	return (reinterpret_cast<T*>(i));
}

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
