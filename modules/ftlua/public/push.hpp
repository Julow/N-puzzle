// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:13:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/02 19:57:04 by ngoguey          ###   ########.fr       //
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
# include "ft/assert.hpp" //debug

# include "ftlua/types.hpp"
# include "ftlua/conversions.hpp"
# include "ftlua/stackassert.hpp"
# include "ftlua/utils.hpp"


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define OK_IFNODEF(PRED) typename std::enable_if<PRED>::type*
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value
# define ISCONST(A) std::is_const<A>::value
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISSAME(A, B) std::is_same<A, B>::value

// Some prototypes ========================================================== //

// TODO: Split hpp/cpp (ps: NO DEFAULT PARAMETERS IN PROTOTYPE)

// ========================================================================== //
// ========================================================================== //
// STRAIGHTFORWARD PUSH-OVERLOADS
//

// IMPLICIT CASTS DISABLED ========== //
template <bool LuaErr = false, typename T, OK_IF(ISSAME(T, bool))>
	int			push(lua_State *l, T const &v)
{ lua_pushboolean(l, v); return 1; }
// ftlua::push<void*>	No const accepted here, const_cast yourself before call.
template <bool LuaErr = false, typename T, OK_IF(ISSAME(T, void*))>
int			push(lua_State *l, T const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushlightuserdata(l, v); return 1; }


// LUA SPECIFIC ===================== //
template <bool LuaErr = false>
int			push(lua_State *l, nil_t const &)
{ lua_pushnil(l); return 1; }
template <bool LuaErr = false>
int			push(lua_State *l, newtab_t const &)
{ lua_createtable(l, 0, 0); return 1; }
template <bool LuaErr = false>
int			push(lua_State *l, dup_t const &i)
{
	int const	index = i.i < 0 ? -i.i : i.i;

	FTLUA_STACKASSERT(
		l, index <= lua_gettop(l), LuaErr
		, ft::f("ftlua::push(dup(%)).", i.i)
		, ft::f("Stack index does not exist.")
		);
	lua_pushvalue(l, i.i);
	return 1;
}
template <bool LuaErr = false>
int			push(lua_State *l, lua_CFunction const &v) {
	if (v == NULL) lua_pushnil(l);
	else lua_pushcfunction(l, v); return 1; }


// NUMBERS/STRING =================== //
template <bool LuaErr = false, class T
		  , OK_IF(!ISPTR(T))
		  , OK_IF(!ISSAME(bool, DELCONST(T)))
		  , OK_IF(!std::is_floating_point<T>::value)
		  , OK_IF(ISCONV(T, lua_Integer))
		  >
int			push(lua_State *l, T const &v)
{
	lua_pushinteger(l, static_cast<lua_Integer>(v));
	return 1;
}

template <bool LuaErr = false, class T
		  , OK_IF(std::is_floating_point<T>::value)
		  , OK_IF(ISCONV(T, lua_Number))
		  >
int			push(lua_State *l, T const &v)
{
	lua_pushnumber(l, static_cast<lua_Number>(v));
	return 1;
}

template <bool LuaErr = false>
int			push(lua_State *l, std::string const &v)
{
	lua_pushstring(l, v.c_str());
	return 1;
}


// BOOL/NUMBERS/STRING/ ==== POINTERS //
template <bool LuaErr = false, class T
			, OK_IF(ISPTR(T))
			, class NOPTR = DELPTR(T)
			, OK_IF(!ISPTR(NOPTR))
			, OK_IF(!ISSAME(char, DELCONST(NOPTR)))
			, OK_IF(!std::is_floating_point<NOPTR>::value)
			, OK_IF(ISCONV(NOPTR, lua_Integer))
			>
int			push(lua_State *l, T v)
{
	if (v == nullptr)
		lua_pushnil(l);
	else
		lua_pushinteger(l, static_cast<lua_Integer>(*v));
	return 1;
}

template <bool LuaErr = false, class T
			, OK_IF(ISPTR(T))
			, class NOPTR = DELPTR(T)
			, OK_IF(!ISPTR(NOPTR))
			, OK_IF(std::is_floating_point<NOPTR>::value)
			, OK_IF(ISCONV(NOPTR, lua_Number))
			>
int			push(lua_State *l, T v)
{
	if (v == nullptr)
		lua_pushnil(l);
	else
		lua_pushinteger(l, static_cast<lua_Integer>(*v));
	return 1;
}

template <bool LuaErr = false>
int			push(lua_State *l, std::string const *const &v)
{
	if (v == nullptr)
		lua_pushnil(l);
	else
		lua_pushstring(l, v->c_str());
	return 1;
}

template <bool LuaErr = false>
int			push(lua_State *l, char const *v)
{
	FTASSERT(false);
	if (v == NULL)
		lua_pushnil(l);
	else
		lua_pushstring(l, v);
	return 1;
}

// 'ft::' COMPOUND TYPES ============ //
template <bool LuaErr = false, typename T>
int	push(lua_State *l, ft::Vec2<T> const &v)
{
	push(l, v.x); push(l, v.y);
	return 2;
}
template <bool LuaErr = false, typename T>
int	push(lua_State *l, ft::Vec3<T> const &v)
{
	push(l, v.x); push(l, v.y); push(l, v.z);
	return 3;
}
template <bool LuaErr = false, typename T>
int	push(lua_State *l, ft::Vec4<T> const &v)
{
	push(l, v.x); push(l, v.y); push(l, v.z); push(l, v.w);
	return 4;
}
template <bool LuaErr = false, typename T>
int	push(lua_State *l, ft::Rect<T> const &v)
{
	push(l, v.left); push(l, v.top); push(l, v.right); push(l, v.bottom);
	return 4;
}


// ========================================================================== //
// ========================================================================== //
// CUSTOM::ftlua_push() PUSH-OVERLOADS
//


// (T -> T::ftlua_push())
template <bool LuaErr = false, typename T
			// , OK_IF(ft::is_complete<T>::value) // TODO: in_complete works?
			, OK_IF(!ISCONST(T))
			, OK_IF(ftlua::has_size<T>::value)
			, OK_IF(ftlua::has_push<T>::value)
			>
int			push(lua_State *l, T &v)
{
	bool const	err = v.ftlua_push(l);

	FTASSERT(err == true); //TODO FTLUA_STACKASSERT
	return T::ftlua_size::value;
}

// (T -> T::ftlua_push() const) OR (T const -> T::ftlua_push() const)
template <bool LuaErr = false, typename T
			, OK_IF(ftlua::has_size<T>::value)
			, OK_IF(ftlua::has_constpush<T>::value)
			>
int			push(lua_State *l, T const &v)
{
	bool const	err = v.ftlua_push(l);

	FTASSERT(err == true); //TODO FTLUA_STACKASSERT
	return T::ftlua_size::value;
}

// Pointers tmp function
template <bool LuaErr = false, typename T
			, OK_IF(ISPTR(T))
			, class NOPTR = DELPTR(T)
			, OK_IF(ftlua::has_size<NOPTR>::value)
			, OK_IF(ftlua::has_push<NOPTR>::value
					|| ftlua::has_constpush<NOPTR>::value)
			>
int			push(lua_State *l, T v)
{
	if (v == nullptr)
		return push<LuaErr>(l, nil);
	else
		return push<LuaErr>(l, *v);
}


// ========================================================================== //
// ========================================================================== //
// KeysWrapper<...> PUSH-OVERLOADS
//
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


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


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <bool LuaErr = false
			, int Relative
			, typename ...ARGS>
int			push(lua_State *l, KeysWrapper<Relative, ARGS...> const &wrap)
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
	return 1;
}


// ========================================================================== //
// ========================================================================== //
// CONTAINERS<...> PUSH-OVERLOADS
//


template <bool LuaErr = false
			, class T
			, OK_IF(ft::is_container<T>::value)
			>
int			push(lua_State *l, T &cont)
{
	int			i(0);
	int			inc;
	int const	tabI = lua_gettop(l) + 1;
	int const	eltI = tabI + 1;

	push(l, newtab);				// []
	for (auto &elt : cont)
	{
		inc = push(l, elt);			// vn, v1, []
		while (inc-- > 0)
		{
			push(l, i);				// 1, vn, v1, []
			push(l, dup(eltI));		// v1, 1, vn, v1, []
			lua_settable(l, tabI);	// vn, v1, []
			lua_remove(l, eltI);	// vn, []
			i++;
		}
	}
	return 1;
}

template <bool LuaErr = false
			, class T
			, OK_IF(ft::is_container<T>::value)
			>
int			push(lua_State *l, T const &cont)
{
	int			i(0);
	int			inc;
	int const	tabI = lua_gettop(l) + 1;
	int const	eltI = tabI + 1;

	push(l, newtab);				// []
	for (auto const &elt : cont)
	{
		inc = push(l, elt);			// vn, v1, []
		while (inc-- > 0)
		{
			push(l, i);				// 1, vn, v1, []
			push(l, dup(eltI));		// v1, 1, vn, v1, []
			lua_settable(l, tabI);	// vn, v1, []
			lua_remove(l, eltI);	// vn, []
			i++;
		}
	}
	return 1;
}


// ========================================================================== //
// ========================================================================== //
// MULTI-PUSH
//
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <bool LuaErr>
int			_pushLoop(lua_State *)
{
	return 0;
}

template <bool LuaErr, typename HEAD, typename ...TAIL>
int			_pushLoop(lua_State *l, HEAD const &h, TAIL const &...t)
{
	return push<LuaErr>(l, h) + _pushLoop<LuaErr>(l, t...);
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <bool LuaErr = false, typename ...ARGS>
int			multiPush(lua_State *l, ARGS const & ...args)
{
	return internal::_pushLoop<LuaErr>(l, args...);
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
#endif
