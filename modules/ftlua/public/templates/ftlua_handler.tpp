// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_handler.tpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/09 09:10:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 14:54:47 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <type_traits>
#include <typeinfo>

#include "ft/Vec.hpp"
#include "ft/utils.hpp"
#include "ft/assert.hpp"

#include "ftlua/push.hpp"
#include "ftlua/pop.hpp"
#include "ftlua/size.hpp"


# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define OK_IFNODEF(PRED) typename std::enable_if<PRED>::type*
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value
# define ISCONST(A) std::is_const<A>::value
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISSAME(A, B) std::is_same<A, B>::value

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
// template <class T>
template <class T, OK_IF(!has_panicpush<T>::value)>
void	stackPush(lua_State *l, T &val)
{
	ftlua::push<true>(l, val);
	return ;
}

// template <class T>
template <class T, OK_IF(!has_panicpush<T>::value)>
void	stackPush(lua_State *l, T const &val)
{
	ftlua::push<true>(l, val);
	return ;
}

template <class T, OK_IF(has_panicpush<T>::value)>
void	stackPush(lua_State *l, T &v)
{
	std::function<void(std::string)>    panic =
		[l, &v](std::string const &str) {
		FTLUA_ERR(l, true, ft::f("ftlua::handle(%) failed from:\n%"
								   , ft::valToString(v), str));
	};
	ftlua::push<true>(l, v, panic);
	return ;
}

template <class T, OK_IF(has_panicpush<T>::value)>
void	stackPush(lua_State *l, T const &v)
{
	std::function<void(std::string)>	panic =
		[l, &v](std::string const &str) {
		FTLUA_ERR(l, true, ft::f("ftlua::handle(%) failed from:\n%"
								   , ft::valToString(v), str));
	};
	// ftlua::push<true>(l, v);
	ftlua::push<true>(l, v, panic);
	return ;
}

// * STEP 4 *** Call the function ******************************************* //
// * Function *** //
template <typename Ret, typename... Params>
void	helperCall(lua_State *l, Ret (*f)(Params...), Params &&...p)
{
	stackPush(l, f(p...));
	return ;
}
template <typename... Params>
void	helperCall(lua_State *, void (*f)(Params...), Params &&...p)
{
	f(p...);
	return ;
}

// * MemFun ***** //
template <typename Ret, class C, typename... Params>
void	helperCall(lua_State *l, C *i, Ret (C::*f)(Params...), Params &&...p)
{
	stackPush(l, (i->*f)(p...));
	return ;
}
template <class C, typename... Params>
void	helperCall(lua_State *, C *i, void (C::*f)(Params...), Params &&...p)
{
	(i->*f)(p...);
	return ;
}

// * STEP 3 *** Restore the function pointer and check NumIn **************** //
// * Function *** //
template <int NumIn
		  , typename Ret, typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(), Retreived &&...r)
{
	helperCall(l, reinterpret_cast<Ret (*)(Retreived...)>(f)
			   , std::forward<Retreived>(r)...);
	return ;
}

// * MemFun ***** //
template <int NumIn
		  , typename Ret, class C, typename... Retreived>
void		helperLoop(
	lua_State *l, C *i, Ret (C::*f)(), Retreived &&...r)
{
	helperCall(l, i
			   , reinterpret_cast<Ret (C::*)(Retreived...)>(f)
			   , std::forward<Retreived>(r)...);
	return ;
}

// * STEP 2 *** Loop through arguments to retreive them from the lua Stack ** //
// * Function *** //
template <int NumIn
		  , typename Ret, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(Head, ArgsLeft...), Retreived&&...r)
{
	using HeadCleanRef = typename std::remove_reference<Head>::type;
	using HeadCleanAll = typename std::remove_cv<HeadCleanRef>::type;

	HeadCleanAll	p{popStack<HeadCleanAll>(l, NumIn)};

	helperLoop<NumIn - decay<HeadCleanAll>()>(
		l, reinterpret_cast<Ret (*)(ArgsLeft...)>(f)
		, std::forward<Retreived>(r)...
		, std::forward<HeadCleanAll>(p)
		);
	return ;
}

// * MemFun ***** //
template <int NumIn
		  , typename Ret, class C, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(
	lua_State *l, C *i, Ret (C::*f)(Head, ArgsLeft...), Retreived&&...r)
{
	using HeadCleanRef = typename std::remove_reference<Head>::type;
	using HeadCleanAll = typename std::remove_cv<HeadCleanRef>::type;

	HeadCleanAll	p{popStack<HeadCleanAll>(l, NumIn)};

	helperLoop<NumIn - decay<HeadCleanAll>()>(
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
	static_assert(NumIn == ftlua::multiSize<Args...>()
				  , "Wrong number of poped arguments.");
	static_assert(NumOut == ftlua::size<Ret>::value
				  , "Wrong number of pushed arguments.");
	internal::helperLoop<NumIn>(l, f);
	return (NumOut);
}

// * MemFun ***** //
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, C *i, Ret (C::*f)(Args...))
{
	static_assert(NumIn == ftlua::multiSize<C, Args...>()
				  , "Wrong number of poped arguments.");
	static_assert(NumOut == ftlua::size<Ret>::value
				  , "Wrong number of pushed arguments.");
	internal::helperLoop<NumIn>(l, i, f);
	return (NumOut);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, C const *i, Ret (C::*f)(Args...) const)
{
	static_assert(NumIn == ftlua::multiSize<C, Args...>()
				  , "Wrong number of poped arguments.");
	static_assert(NumOut == ftlua::size<Ret>::value
				  , "Wrong number of pushed arguments.");
	using FClean = Ret (C::*)(Args...);
	using CClean = C*;

	internal::helperLoop<NumIn>(
		l, const_cast<CClean>(i), reinterpret_cast<FClean>(f));
	// TODO: sorry world this is a const_cast :( TODO: fix_later
	return (NumOut);
}
template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, Ret (C::*f)(Args...))
{
	static_assert(NumIn == ftlua::multiSize<C, Args...>()
				  , "Wrong number of poped arguments.");
	static_assert(NumOut == ftlua::size<Ret>::value
				  , "Wrong number of pushed arguments.");
	internal::helperLoop<NumIn - 1>(
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

# undef DELPTR
# undef DELCONST
# undef ISCONV
# undef ISPTR
# undef ISCONST
# undef OK_IF
# undef OK_IFNODEF
# undef ISSAME
