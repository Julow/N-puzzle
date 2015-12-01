// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:13:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/01 14:30:47 by ngoguey          ###   ########.fr       //
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

/*
template <bool FIRSTISTOP, bool LuaErr
		  , typename... ARGS>
int			push(lua_State *l, KeysWrapper<ARGS...> const &wrap);

// Push (T to Converter<T>) || (const-T to Converter<const-T>)
template <bool LuaErr, typename T
		  , OK_IFNODEF((sizeof(T) > 0u))
		  , OK_IFNODEF(ISCONV(T, Converter<T>)) >
int			push(lua_State *l, T &v);


// Push (T to Converter<T const>)
//TODO: validate this overload
template <bool LuaErr, typename T
		  , OK_IFNODEF((sizeof(T) > 0u))
	, OK_IFNODEF(!ISCONST(T))
	// , OK_IFNODEF(ISCONST(T))
	// , typename NOCONST
	, OK_IFNODEF(ISCONV(T, Converter<const T>)) >
int			push(lua_State *l, T &v);


// Push (const-T to Converter<T>) NOT(const-T to Converter<T const>)
// Overload allowing const cast in User's cast-operator
template <bool LuaErr, typename T
		  , OK_IFNODEF((sizeof(T) > 0u))
	, OK_IFNODEF(ISCONST(T))
	, typename NOCONST
	, OK_IFNODEF(ISCONV(T, Converter<NOCONST>))
	, OK_IFNODEF(!ISCONV(T, Converter<T>))>
	int			push(lua_State *l, T &v);

// Push (T* to push<T>) || (T-const * to push<T-const>)
template <bool LuaErr, typename T
		  , OK_IFNODEF(ISPTR(T))
		  , typename NOPTR
		  , OK_IFNODEF((sizeof(NOPTR) > 0u))
	, typename NOPTRCONST
	, OK_IFNODEF(ISCONV(NOPTRCONST, Converter<NOPTRCONST>))
	>
int			push(lua_State *l, T v);
*/

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
# define DEFINE_PUSH(TYPE, FUNCSUFFIX, ...)			\
	template <bool LuaErr = false>					\
	int			push(lua_State *l, TYPE const &v)	\
	{												\
		lua_push##FUNCSUFFIX(l, v __VA_ARGS__);		\
		return 1;									\
	}

DEFINE_PUSH(int8_t, integer)
DEFINE_PUSH(int16_t, integer)
DEFINE_PUSH(int32_t, integer)
DEFINE_PUSH(int64_t, integer)
DEFINE_PUSH(intmax_t, integer)

DEFINE_PUSH(uint8_t, integer)
DEFINE_PUSH(uint16_t, integer)
DEFINE_PUSH(uint32_t, integer)
DEFINE_PUSH(uint64_t, integer)
DEFINE_PUSH(uintmax_t, integer)
// TODO: more types from cstdint might be required here

DEFINE_PUSH(float, number)
DEFINE_PUSH(double, number)

DEFINE_PUSH(std::string, string, .c_str())

# undef DEFINE_PUSH

// BOOL/NUMBERS/STRING/ ==== POINTERS //
# define DEFINE_PUSH(TYPE, FUNCSUFFIX, ...)					\
	template <bool LuaErr = false>							\
	int			push(lua_State *l, TYPE const *const &v)	\
	{														\
		if (v == nullptr)									\
			lua_pushnil(l);									\
		else												\
			lua_push##FUNCSUFFIX(l, (*v) __VA_ARGS__);		\
		return 1;											\
	}

DEFINE_PUSH(bool, boolean)

DEFINE_PUSH(int8_t, integer)
DEFINE_PUSH(int16_t, integer)
DEFINE_PUSH(int32_t, integer)
DEFINE_PUSH(int64_t, integer)
DEFINE_PUSH(intmax_t, integer)

DEFINE_PUSH(uint8_t, integer)
DEFINE_PUSH(uint16_t, integer)
DEFINE_PUSH(uint32_t, integer)
DEFINE_PUSH(uint64_t, integer)
DEFINE_PUSH(uintmax_t, integer)

DEFINE_PUSH(float, number)
DEFINE_PUSH(double, number)

DEFINE_PUSH(std::string, string, .c_str())

# undef DEFINE_PUSH

template <bool LuaErr = false>
int			push(lua_State *l, char const *v)
{
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
// CONVERTER<T> PUSH-OVERLOADS
//
// 'OK_IF((sizeof(T) > 0u))'		Checks if T is a complete type
//

// template<typename T>
// struct is_complete : std::integral_constant<bool, (sizeof(T) == sizeof(T))>
// struct is_complete : std::integral_constant<bool, (typeid(T) == typeid(T))>
// struct is_complete : std::integral_constant<bool, (sizeof(T) > 0u)>
// {};

template<typename T>
auto	is_complete_fn(T*)
	-> typename std::enable_if<sizeof(T), std::true_type>::type;

auto	is_complete_fn(...)
	-> std::false_type;

template<
	typename T
	, bool value = decltype(is_complete_fn((T*)nullptr))::value
	>
struct is_complete : std::integral_constant<bool, value>
{};


// T -> Converter<T>
template <bool LuaErr = false, typename T
		  , OK_IF((sizeof(T) > 0u))
							  , OK_IF(!ISCONST(T))
							  , OK_IF(ISCONV(T, Converter<T>)) >
int			push(lua_State *l, T &v)
{
	return static_cast<Converter<T>>(v).callPush(l);
}

// T const -> Converter<T const>
template <bool LuaErr = false, typename T
		  , OK_IF((sizeof(T) > 0u))
	, OK_IF(ISCONST(T))
	, OK_IF(ISCONV(T, Converter<T>)) >
int			push(lua_State *l, T &v)
{
	return static_cast<Converter<T>>(v).callPush(l);
}

// T -> Converter<T const>   NOT(T -> Converter<T>)
template <bool LuaErr = false, typename T
		  , OK_IF((sizeof(T) > 0u))
	, OK_IF(!ISCONST(T))
	, OK_IF(ISCONV(T, Converter<const T>))
	, OK_IF(!ISCONV(T, Converter<T>))
	>
int			push(lua_State *l, T const &v)
{
	return static_cast<Converter<const T>>(v).callPush(l);
}

// T const -> Converter<T>  NOT(T const -> Converter<T const)
// Might require a const cast in user's cast-operator
template <bool LuaErr = false, typename T
		  , OK_IF((sizeof(T) > 0u))
	, OK_IF(ISCONST(T))
	, class TNoConst = DELCONST(T)
	, OK_IF(ISCONV(T, Converter<TNoConst>))
	, OK_IF(!ISCONV(T, Converter<T>))>
int			push(lua_State *l, T &v)
{
	return static_cast<Converter<T const>>(v).callPush(l);
}

// Pointers tmp function
template <bool LuaErr = false, typename T
		  , OK_IF(ISPTR(T))
		  , typename NOPTR = DELPTR(T)
		  // , OK_IF(is_complete<NOPTR>::value)
		  , OK_IF((sizeof(NOPTR) > 0u))
	, typename NOPTRCONST = DELCONST(NOPTR)
	, OK_IF(ISCONV(NOPTRCONST, Converter<NOPTRCONST>))
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
