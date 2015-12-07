// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ftlua_handler.tpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/09 09:10:41 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:35:01 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <type_traits>
#include <typeinfo>

#include "ft/Vec.hpp"

#include "ftlua/push.hpp"
#include "ftlua/pop.hpp"
#include "ftlua/size.hpp"

# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELREF(T) typename std::remove_reference<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define OK_IFNODEF(PRED) typename std::enable_if<PRED>::type*
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value
# define ISCONST(A) std::is_const<A>::value
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISSAME(A, B) std::is_same<A, B>::value


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// * STEP 5 *** Push return value on stack ********************************** //
// template <class T>
template <class Fun, class T, OK_IF(!has_panicpush<T>::value)>
void	stackPush(lua_State *l, T &val)
{
	ftlua::push<true>(l, val);
	return ;
}

template <class Fun, class T, OK_IF(!has_panicpush<T>::value)>
void	stackPush(lua_State *l, T const &val)
{
	ftlua::push<true>(l, val);
	return ;
}

template <class Fun, class T, OK_IF(has_panicpush<T>::value)>
void	stackPush(lua_State *l, T &v)
{
	std::function<void(std::string)>    panic =
		[l, &v](std::string const &str) {
		FTLUA_ERR(l, true, ft::f("from\nftlua::handle(%) failed from:\n%"
								 , ft::funTypeToString<Fun>(), str));
	};
	ftlua::push<true>(l, v, panic);
	return ;
}

template <class Fun, class T, OK_IF(has_panicpush<T>::value)>
void	stackPush(lua_State *l, T const &v)
{
	std::function<void(std::string)>	panic =
		[l, &v](std::string const &str) {
		FTLUA_ERR(l, true, ft::f("from:\nftlua::handle(%) failed from:\n%"
								 , ft::funTypeToString<Fun>(), str));
	};
	ftlua::push<true>(l, v, panic);
	return ;
}

// * STEP 4 *** Call the function ******************************************* //
// * Function *** //
template <typename Ret, typename... Params>
void	helperCall(lua_State *l, Ret (*f)(Params...), Params &&...p)
{
	stackPush<Ret(*)(Params...)>(l, f(p...));
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
	stackPush<Ret(C::*)(Params...)>(l, (i->*f)(p...));
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
template <int NextIndex
		  , typename Ret, typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(), Retreived &&...r)
{
	static_assert(NextIndex == 0, "Debug, can't be triggered");

	helperCall(l, reinterpret_cast<Ret (*)(Retreived...)>(f)
			   , std::forward<Retreived>(r)...);
	return ;
}

// * MemFun ***** //
template <int NextIndex
		  , typename Ret, class C, typename... Retreived>
void		helperLoop(
	lua_State *l, C *i, Ret (C::*f)(), Retreived &&...r)
{
	static_assert(NextIndex == 0, "Debug, can't be triggered");

	helperCall(l, i
			   , reinterpret_cast<Ret (C::*)(Retreived...)>(f)
			   , std::forward<Retreived>(r)...);
	return ;
}

// * STEP 2 *** Loop through arguments to retreive them from the lua Stack ** //
// * Function *** //
template <int NextIndex
		  , typename Ret, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(
	lua_State *l, Ret (*f)(Head, ArgsLeft...), Retreived&&...r)
{
	using HeadClean = DELCONST(DELREF(Head));

	std::function<void(std::string)>	panic =
		[=](std::string const &str)
		{
			using Fun = Ret (*)(Retreived..., Head, ArgsLeft...);

			FTLUA_ERR(l, true, ft::f("from:\nftlua::handle(%) failed from:\n%"
									 , ft::funTypeToString<Fun>(), str));
		};
	HeadClean	v{ftlua::pop<HeadClean>(l, NextIndex, panic)};

	helperLoop
		<NextIndex + static_cast<int>(ftlua::size<HeadClean>::value)>
		(l, reinterpret_cast<Ret (*)(ArgsLeft...)>(f)
		 , std::forward<Retreived>(r)..., std::forward<HeadClean>(v));
	return ;
}

// * MemFun ***** //
template <int NextIndex
		  , typename Ret, class C, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helperLoop(
	lua_State *l, C *inst, Ret (C::*f)(Head, ArgsLeft...), Retreived&&...r)
{
	using HeadClean = DELCONST(DELREF(Head));

	std::function<void(std::string)>	panic =
		[=](std::string const &str)
		{
			using Fun = Ret (C::*)(Retreived..., Head, ArgsLeft...);

			FTLUA_ERR(l, true, ft::f("from:\nftlua::handle(%) failed from:\n%"
									 , ft::funTypeToString<Fun>(), str));
		};
	HeadClean	v{ftlua::pop<HeadClean>(l, NextIndex, panic)};

	helperLoop
		<NextIndex + static_cast<int>(ftlua::size<HeadClean>::value)>
		(l, inst, reinterpret_cast<Ret (C::*)(ArgsLeft...)>(f)
		 , std::forward<Retreived>(r)..., std::forward<HeadClean>(v));
	return ;
}


}; // ~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// * STEP 1 *** Call the helperLoop ***************************************** //
// * Function *** //
template <int NumIn, int NumOut, typename Ret, typename... Args>
int		handle(lua_State *l, Ret (*f)(Args...))
{
	static_assert(NumIn == ftlua::multiSize<Args...>()
				  , "Wrong number of poped arguments.");
	static_assert(NumOut == ftlua::size<Ret>::value
				  , "Wrong number of pushed arguments.");

	internal::helperLoop<-NumIn>(l, f);
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

	internal::helperLoop<-NumIn>(l, i, f);
	return (NumOut);
}

template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, Ret (C::*f)(Args...))
// TODO: split for popable/not popable
{
	static_assert(NumIn == ftlua::multiSize<C, Args...>()
				  , "Wrong number of poped arguments.");
	static_assert(NumOut == ftlua::size<Ret>::value
				  , "Wrong number of pushed arguments.");

	C		*inst = ftlua::pop<C*, true>(l, -NumIn);

	internal::helperLoop
		<-NumIn + static_cast<int>(ftlua::size<C>::value)>
		(l, inst, f);
	return (NumOut);
}

template <int NumIn, int NumOut, typename Ret, class C, typename... Args>
int		handle(lua_State *l, Ret (C::*f)(Args...) const)
// TODO: improve this function
{
	using F = Ret (C::*)(Args...);
	using FClean = typename std::remove_cv<F>::type;

	return (handle<NumIn, NumOut>(l, reinterpret_cast<FClean>(f)));
}

}; // ~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# undef DELPTR
# undef DELREF
# undef DELCONST
# undef ISCONV
# undef ISPTR
# undef ISCONST
# undef OK_IF
# undef OK_IFNODEF
# undef ISSAME
