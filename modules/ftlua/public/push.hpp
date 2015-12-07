// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:13:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:37:48 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_PUSH_HPP
# define FTLUA_PUSH_HPP

# include <cstdint>
# include <string>
# include <tuple>

# include "liblua/lua.hpp"
# include "ft/Vec.hpp"
# include "ft/Rect.hpp"
# include "ft/utils.hpp"

# include "ftlua/types.hpp"
# include "ftlua/conversions.hpp"
# include "ftlua/stackassert.hpp"
# include "ftlua/utils.hpp"
# include "ftlua/size.hpp"

# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define OK_IFNODEF(PRED) typename std::enable_if<PRED>::type*
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value
# define ISCONST(A) std::is_const<A>::value
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISSAME(A, B) std::is_same<A, B>::value


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// ========================================================================== //
// ========================================================================== //
// PUSH
//
// IMPLICIT CASTS DISABLED ========== //
// Function:		ftlua::push
// Overload:		bool
template <bool LuaErr = false, typename T, OK_IF(ISSAME(T, bool))>
void		push(lua_State *l, T v) {
	lua_pushboolean(l, v);
}

// Function:		ftlua::push
// Overload:		void*
template <bool LuaErr = false, typename T, OK_IF(ISSAME(T, void*))>
void		push(lua_State *l, T v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushlightuserdata(l, v);
}

// LUA SPECIFIC ===================== //
// Function:		ftlua::push
// Overload:		ftlua::nil_t
template <bool LuaErr = false>
void		push(lua_State *l, nil_t) { lua_pushnil(l);
}

// Function:		ftlua::push
// Overload:		ftlua::newtab_t
template <bool LuaErr = false>
void		push(lua_State *l, newtab_t) { lua_createtable(l, 0, 0);
}

// Function:		ftlua::push
// Overload:		ftlua::dup_t
template <bool LuaErr = false>
void		push(lua_State *l, dup_t i)
{
	int const	index = i.i < 0 ? -i.i : i.i;

	FTLUA_STACKASSERT(
		l, index <= lua_gettop(l), LuaErr
		, ft::f("ftlua::push(dup(%)).", i.i)
		, ft::f("Stack index does not exist.")
		);
	lua_pushvalue(l, i.i);
	return ;
}

// Function:		ftlua::push
// Overload:		ftlua::dup_t with panic
template <bool LuaErr = false>
void		push(lua_State *l, dup_t i, std::function<void(std::string)> panic)
{
	int const	index = i.i < 0 ? -i.i : i.i;

	FTLUA_STACKASSERT_PANIC(
		l, index <= lua_gettop(l), panic
		, ft::f("ftlua::push(dup(%)).", i.i)
		, ft::f("Stack index does not exist.")
		);
	lua_pushvalue(l, i.i);
	return ;
}
template <bool LuaErr = false>
void		push(lua_State *l, lua_CFunction v) {
	if (v == NULL) lua_pushnil(l);
	else lua_pushcfunction(l, v);
}

// NUMBERS/STRING =================== //
// Function:		ftlua::push
// Overload:		integer
template <bool LuaErr = false, class T
		  , OK_IF(!ISPTR(T))
		  , OK_IF(!ISSAME(bool, DELCONST(T)))
		  , OK_IF(!std::is_floating_point<T>::value)
		  , OK_IF(ISCONV(T, lua_Integer))
		  >
void		push(lua_State *l, T v)
{
	lua_pushinteger(l, static_cast<lua_Integer>(v));
	return ;
}

// Function:		ftlua::push
// Overload:		floating point
template <bool LuaErr = false, class T
		  , OK_IF(std::is_floating_point<T>::value)
		  , OK_IF(ISCONV(T, lua_Number))
		  >
void		push(lua_State *l, T v)
{
	lua_pushnumber(l, static_cast<lua_Number>(v));
	return ;
}

// Function:		ftlua::push
// Overload:		std::string const&
template <bool LuaErr = false>
void		push(lua_State *l, std::string const &v)
{
	lua_pushstring(l, v.c_str());
	return ;
}


// BOOL/NUMBERS/STRING ===== POINTERS //
// Function:		ftlua::push
// Overload:		integer*
template <bool LuaErr = false, class T
		  , OK_IF(ISPTR(T))
		  , class NOPTR = DELPTR(T)
		  , OK_IF(!ISPTR(NOPTR))
		  , OK_IF(!ISSAME(char, DELCONST(NOPTR)))
		  , OK_IF(!std::is_floating_point<NOPTR>::value)
		  , OK_IF(ISCONV(NOPTR, lua_Integer))
		  >
void		push(lua_State *l, T v)
{
	if (v == nullptr)
		lua_pushnil(l);
	else
		lua_pushinteger(l, static_cast<lua_Integer>(*v));
	return ;
}

// Function:		ftlua::push
// Overload:		floating point*
template <bool LuaErr = false, class T
		  , OK_IF(ISPTR(T))
		  , class NOPTR = DELPTR(T)
		  , OK_IF(!ISPTR(NOPTR))
		  , OK_IF(std::is_floating_point<NOPTR>::value)
		  , OK_IF(ISCONV(NOPTR, lua_Number))
		  >
void		push(lua_State *l, T v)
{
	if (v == nullptr)
		lua_pushnil(l);
	else
		lua_pushinteger(l, static_cast<lua_Integer>(*v));
	return ;
}

// Function:		ftlua::push
// Overload:		std::string *
template <bool LuaErr = false>
void		push(lua_State *l, std::string const *v)
{
	if (v == nullptr)
		lua_pushnil(l);
	else
		lua_pushstring(l, v->c_str());
	return ;
}

// Function:		ftlua::push
// Overload:		char const*
template <bool LuaErr = false>
void		push(lua_State *l, char const *v)
{
	if (v == NULL)
		lua_pushnil(l);
	else
		lua_pushstring(l, v);
	return ;
}

// 'ft::' COMPOUND TYPES ============ //
// Function:		ftlua::push
// Overload:		ft::Vec2<T> const&
template <bool LuaErr = false, typename T>
void		push(lua_State *l, ft::Vec2<T> const &v)
{
	push(l, v.x); push(l, v.y);
	return ;
}

// Function:		ftlua::push
// Overload:		ft::Vec3<T> const&
template <bool LuaErr = false, typename T>
void		push(lua_State *l, ft::Vec3<T> const &v)
{
	push(l, v.x); push(l, v.y); push(l, v.z);
	return ;
}

// Function:		ftlua::push
// Overload:		ft::Vec4<T> const&
template <bool LuaErr = false, typename T>
void		push(lua_State *l, ft::Vec4<T> const &v)
{
	push(l, v.x); push(l, v.y); push(l, v.z); push(l, v.w);
	return ;
}

// Function:		ftlua::push
// Overload:		ft::Rect<T> const&
template <bool LuaErr = false, typename T>
void		push(lua_State *l, ft::Rect<T> const &v)
{
	push(l, v.left); push(l, v.top); push(l, v.right); push(l, v.bottom);
	return ;
}

// CUSTOM::ftlua_push() ============= //
// Function:		ftlua::push
// Overload:		Custom& -> Custom::ftlua_push()
template <bool LuaErr = false, typename T
		  , OK_IF(!ISCONST(T))
		  , OK_IF(ftlua::has_size<T>::value)
		  , OK_IF(ftlua::has_push<T>::value)
		  >
void		push(lua_State *l, T &v)
{
	std::function<void(std::string)>	panic =
		[l, &v](std::string const &str)
		{
			FTLUA_ERR(l, LuaErr, ft::f("ftlua::push(%) failed from:\n%"
									   , ft::valToString(v), str));
		};
	v.ftlua_push(l, panic);
	return ;
}

// Function:		ftlua::push
// Overload:		Custom& -> Custom::ftlua_push() with panic
template <bool LuaErr = false, typename T
		  , OK_IF(!ISCONST(T))
		  , OK_IF(ftlua::has_size<T>::value)
		  , OK_IF(ftlua::has_push<T>::value)
		  >
void		push(lua_State *l, T &v, std::function<void(std::string)> ppanic)
{
	std::function<void(std::string)>	panic =
		[ppanic, &v](std::string const &str)
		{
			ppanic(ft::f("ftlua::push(%) failed from:\n%"
						 , ft::valToString(v), str));
		};
	v.ftlua_push(l, panic);
	return ;
}

// Function:		ftlua::push
// Overload:		Custom&			-> Custom::ftlua_push() const
// Overload:		Custom const&	-> Custom::ftlua_push() const
template <bool LuaErr = false, typename T
		  , OK_IF(ftlua::has_size<T>::value)
		  , OK_IF(ftlua::has_constpush<T>::value)
		  >
void		push(lua_State *l, T const &v)
{
	std::function<void(std::string)>	panic =
		[l, &v](std::string const &str)
		{
			FTLUA_ERR(l, LuaErr, ft::f("ftlua::push(%) failed from:\n%"
									   , ft::valToString(v), str));
		};
	v.ftlua_push(l, panic);
	return ;
}

// Function:		ftlua::push
// Overload:		Custom&			-> Custom::ftlua_push() const with panic
// Overload:		Custom const&	-> Custom::ftlua_push() const with panic
template <bool LuaErr = false, typename T
		  , OK_IF(ftlua::has_size<T>::value)
		  , OK_IF(ftlua::has_constpush<T>::value)
		  >
void		push(lua_State *l, T const &v
				 , std::function<void(std::string)> ppanic)
{
	std::function<void(std::string)>	panic =
		[ppanic, &v](std::string const &str)
		{
			ppanic(ft::f("ftlua::push(%) failed from:\n%"
						 , ft::valToString(v), str));
		};
	v.ftlua_push(l, panic);
	return ;
}

// Function:		ftlua::push
// Overload:		Custom* -> ftlua::nil_t or Custom&
template <bool LuaErr = false, typename T
		  , OK_IF(ISPTR(T))
		  , class NOPTR = DELPTR(T)
		  , OK_IF(ftlua::has_size<NOPTR>::value)
		  , OK_IF(ftlua::has_push<NOPTR>::value
				  || ftlua::has_constpush<NOPTR>::value)
		  >
void		push(lua_State *l, T v)
{
	if (v == nullptr)
		push<LuaErr>(l, nil);
	else
		push<LuaErr>(l, *v);
	return ;
}

// Function:		ftlua::push
// Overload:		Custom* -> ftlua::nil_t or Custom& with panic
template <bool LuaErr = false, typename T
		  , OK_IF(ISPTR(T))
		  , class NOPTR = DELPTR(T)
		  , OK_IF(ftlua::has_size<NOPTR>::value)
		  , OK_IF(ftlua::has_push<NOPTR>::value
				  || ftlua::has_constpush<NOPTR>::value)
		  >
void		push(lua_State *l, T v
				 , std::function<void(std::string)> panic)
{
	if (v == nullptr)
		push<LuaErr>(l, nil);
	else
		push<LuaErr>(l, *v, panic);
	return ;
}


// KeysWrapper<...> ================= //
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
template <size_t I, bool LuaErr
		  , int Relative
		  , typename... ARGS
		  >
void		_dereference(
	lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap)
{
	ftlua::push<LuaErr>(l, std::get<I>(wrap.tup));
	FTLUA_STACKASSERT(
		l, lua_istable(l, -2), LuaErr
		, ft::f("ftlua::push(KeysWrapper<%>) at param %/%."
				, ft::tupleToString(wrap.tup), I + 1, sizeof...(ARGS))
		, ft::f("Stack[-2] should have been a table.")
		);
	lua_gettable(l, -2);
	lua_remove(l, -2);
	return ;
}

template <size_t I, bool LuaErr
		  , int Relative
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I == 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap)
{
	_dereference<I, LuaErr>(l, wrap);
	return ;
}

template <size_t I, bool LuaErr
		  , int Relative
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I != 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap)
{
	_dereference<I, LuaErr>(l, wrap);
	_loopKey<I + 1, LuaErr>(l, wrap);
	return ;
}


template <size_t I, bool LuaErr
		  , int Relative
		  , typename... ARGS
		  // , class Elt = typename std::tuple_element<I, std::tuple<ARGS...> >::type
		  // , OK_IF()
		  >
void		_dereference(
	lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap
	, std::function<void(std::string)> panic)
{
	ftlua::push<LuaErr>(l, std::get<I>(wrap.tup)); //todo pass panic
	FTLUA_STACKASSERT_PANIC(
		l, lua_istable(l, -2), panic
		, ft::f("ftlua::push(KeysWrapper<%>) at param %/%."
				, ft::tupleToString(wrap.tup), I + 1, sizeof...(ARGS))
		, ft::f("Stack[-2] should have been a table.")
		);
	lua_gettable(l, -2);
	lua_remove(l, -2);
	return ;
}

template <size_t I, bool LuaErr
		  , int Relative
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I == 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap
					 , std::function<void(std::string)> panic)
{
	_dereference<I, LuaErr>(l, wrap, panic);
	return ;
}

template <size_t I, bool LuaErr
		  , int Relative
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I != 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap
					 , std::function<void(std::string)> panic)
{
	_dereference<I, LuaErr>(l, wrap, panic);
	_loopKey<I + 1, LuaErr>(l, wrap, panic);
	return ;
}
}; // ~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Function:		ftlua::push
// Overload:		KeyWrapper<...> const&
// TODO: noconst& ?
template <bool LuaErr = false
		  , int Relative
		  , typename ...ARGS>
void		push(lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap)
{
	if (Relative == 0)
		lua_pushglobaltable(l);
	else
	{
		FTLUA_STACKASSERT(
			l, lua_istable(l, Relative), LuaErr
			, ft::f("ftlua::push(KeysWrapper<%, %>)."
					, Relative, ft::tupleToString(wrap.tup))
			, ft::f("Table was expected at KeysWrapper's Relative index.")
			);
		lua_pushvalue(l, Relative);
	}
	internal::_loopKey<0, LuaErr>(l, wrap);
	return ;
}

// Function:		ftlua::push
// Overload:		KeyWrapper<...> const& with panic
// TODO: test panic reference
// TODO: debug panic for KeyWrapper<...>
template <bool LuaErr = false
		  , int Relative
		  , typename ...ARGS>
void		push(lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap
				 , std::function<void(std::string)> panic)
{
	if (Relative == 0)
		lua_pushglobaltable(l);
	else
	{
		FTLUA_STACKASSERT_PANIC(
			l, lua_istable(l, Relative), panic
			, ft::f("ftlua::push(KeysWrapper<%, %>)."
					, Relative, ft::tupleToString(wrap.tup))
			, ft::f("Table was expected at KeysWrapper's Relative index.")
			);
		lua_pushvalue(l, Relative);
	}
	internal::_loopKey<0, LuaErr>(l, wrap, panic);
	return ;
}

// Container<...> =================== //
// Function:		ftlua::push
// Overload:		Container<...>&
template <bool LuaErr = false
		  , class T
		  , OK_IF(ft::is_container<T>::value)
		  >
void		push(lua_State *l, T &cont)
{
	int			i(0);
	int			inc;
	int const	tabI = lua_gettop(l) + 1;
	int const	eltI = tabI + 1;

	push(l, newtab);				// []
	for (auto &elt : cont)
	{
		push(l, elt);				// vn, v1, []
		inc = ftlua::size<typename T::value_type>::value;
		while (inc-- > 0)
		{
			push(l, i);				// 1, vn, v1, []
			push(l, dup(eltI));		// v1, 1, vn, v1, []
			lua_settable(l, tabI);	// vn, v1, []
			lua_remove(l, eltI);	// vn, []
			i++;
		}
	}
	return ;
}

// Function:		ftlua::push
// Overload:		const Container<...>&
template <bool LuaErr = false
		  , class T
		  , OK_IF(ft::is_container<T>::value)
		  >
void		push(lua_State *l, T const &cont)
{
	int			i(0);
	int			inc;
	int const	tabI = lua_gettop(l) + 1;
	int const	eltI = tabI + 1;

	push(l, newtab);				// []
	for (auto const &elt : cont)
	{
		push(l, elt);				// vn, v1, []
		inc = ftlua::size<typename T::value_type>::value;
		while (inc-- > 0)
		{
			push(l, i);				// 1, vn, v1, []
			push(l, dup(eltI));		// v1, 1, vn, v1, []
			lua_settable(l, tabI);	// vn, v1, []
			lua_remove(l, eltI);	// vn, []
			i++;
		}
	}
	return ;
}


// ========================================================================== //
// ========================================================================== //
// MULTI-PUSH
//
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
template <bool LuaErr>
void		_pushLoop(lua_State *)
{
	return ;
}

template <bool LuaErr, typename HEAD, typename ...TAIL>
void		_pushLoop(lua_State *l, HEAD const &h, TAIL const &...t)
{
	push<LuaErr>(l, h);
	_pushLoop<LuaErr>(l, t...);
	return ;
}
}; // ~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Function:		ftlua::multiPush
// Overload:		none
template <bool LuaErr = false, typename ...ARGS>
void		multiPush(lua_State *l, ARGS const & ...args)
{
	internal::_pushLoop<LuaErr>(l, args...);
	return ;
}


// ========================================================================== //
// ========================================================================== //
// TYPE-TRAITS
//

// Class:			ftlua::has_panicpush
// Overload:		none
FT_DEFINE_TYPETRAIT_TEST(
	    has_panicpush
		, class = decltype(ftlua::push(nullptr, *(C*)(0x0)
									   , std::function<void(std::string)>{}))
	);


}; // ~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# undef DELPTR
# undef DELCONST
# undef ISCONV
# undef ISPTR
# undef ISCONST
# undef OK_IF
# undef OK_IFNODEF
# undef ISSAME
#endif
