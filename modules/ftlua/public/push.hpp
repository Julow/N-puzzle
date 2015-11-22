// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:13:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/22 13:25:35 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_PUSH_HPP
# define FTLUA_PUSH_HPP

# include <cstdint>
# include <string>

# include "liblua/lua.hpp"
# include "ft/Vec.hpp"
# include "ft/Rect.hpp"
# include "ft/utils.hpp"
# include "ft/assert.hpp" //debug

# include "ftlua/types.hpp"
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

// TODO: Split hpp/cpp (ps: No default parameters in prototype)


template <bool FIRSTISTOP, bool USELUAERR
		  , typename... ARGS>
int			push(lua_State *l, KeysWrapper<ARGS...> const &wrap);


// Push (T to Converter<T>) || (const-T to Converter<const-T>)
template <bool USELUAERR, typename T
		  , OK_IFNODEF(ISCONV(T, Converter<T>)) >
int			push(lua_State *l, T &v);

// Push (const-T to Converter<T>)
// Overload allowing const cast in User's cast-operator
template <bool USELUAERR, typename T
		  , OK_IFNODEF(ISCONST(T))
		  , typename NOCONST
		  , OK_IFNODEF(ISCONV(T, Converter<NOCONST>)) >
int			push(lua_State *l, T &v);

// Push (T* to push<T>) || (T-const * to push<T-const>)
template <bool USELUAERR, typename T
		  , OK_IFNODEF(ISPTR(T))
		  , typename NOPTR
		  , typename NOPTRCONST
		  , OK_IFNODEF(ISCONV(NOPTRCONST, Converter<NOPTRCONST>))
		  >
int			push(lua_State *l, T v);


// ========================================================================== //
// ========================================================================== //
// STRAIGHTFORWARD PUSH-OVERLOADS
//


// IMPLICIT CASTS DISABLED ========== //
template <bool USELUAERR = false, typename T, OK_IF(ISSAME(T, bool))>
int			push(lua_State *l, T const &v)
{ lua_pushboolean(l, v); return 1; }
// ftlua::push<void*>	No const accepted here, const_cast yourself before call.
template <bool USELUAERR = false, typename T, OK_IF(ISSAME(T, void*))>
int			push(lua_State *l, T const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushlightuserdata(l, v); return 1; }


// LUA SPECIFIC ===================== //
template <bool USELUAERR = false>
int			push(lua_State *l, nil_t const &)
{ lua_pushnil(l); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, newtab_t const &)
{ lua_createtable(l, 0, 0); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, dup_t const &i)
{
	if ((i.i < 0 ? -i.i : i.i) > lua_gettop(l))
	{
		if (USELUAERR)
			luaL_error(
				l, ft::f("ftlua::push<dup(%)> wrong index:\n%", i.i
						 , ftlua::stacktostring(l)).c_str());
		else
			throw std::runtime_error(
				ft::f("ftlua::push<dup(%)> wrong index:\n%", i.i
					  , ftlua::stacktostring(l)).c_str());
	}
	lua_pushvalue(l, i.i);
	return 1;
}
template <bool USELUAERR = false>
int			push(lua_State *l, lua_CFunction const &v) {
	if (v == NULL) lua_pushnil(l);
	else lua_pushcfunction(l, v); return 1; }


// NUMBERS/STRING =================== //
template <bool USELUAERR = false>
int			push(lua_State *l, int8_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, int16_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, int32_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, int64_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint8_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint16_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint32_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint64_t const &v)
{ lua_pushinteger(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, float const &v)
{ lua_pushnumber(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, double const &v)
{ lua_pushnumber(l, v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, std::string const &v)
{ lua_pushstring(l, v.c_str()); return 1; }


// BOOL/NUMBERS/STRING/ ----- POINTER //
template <bool USELUAERR = false>
int			push(lua_State *l, bool const *const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushboolean(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, int8_t const *const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, int16_t const *const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, int32_t const *const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, int64_t const *const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint8_t const *const &v){
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint16_t const *const &v){
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint32_t const *const &v){
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, uint64_t const *const &v){
	if (v == nullptr) lua_pushnil(l);
	else lua_pushinteger(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, float const *const &v){
	if (v == nullptr) lua_pushnil(l);
	else lua_pushnumber(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, double const *const &v){
	if (v == nullptr) lua_pushnil(l);
	else lua_pushnumber(l, *v); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, std::string const *const &v) {
	if (v == nullptr) lua_pushnil(l);
	else lua_pushstring(l, v->c_str()); return 1; }
template <bool USELUAERR = false>
int			push(lua_State *l, char const *v) {
	if (v == NULL) lua_pushnil(l);
	else lua_pushstring(l, v); return 1; }


// 'ft::' COMPOUND TYPES ============ //
template <bool USELUAERR = false, typename T>
int	push(lua_State *l, ft::Vec2<T> const &v)
{ push(l, v.x); push(l, v.y); return 2; }
template <bool USELUAERR = false, typename T>
int	push(lua_State *l, ft::Vec3<T> const &v)
{ push(l, v.x); push(l, v.y); push(l, v.z); return 3; }
template <bool USELUAERR = false, typename T>
int	push(lua_State *l, ft::Vec4<T> const &v)
{ push(l, v.x); push(l, v.y); push(l, v.z); push(l, v.w); return 4; }
template <bool USELUAERR = false, typename T>
int	push(lua_State *l, ft::Rect<T> const &v) {
	push(l, v.left); push(l, v.top); push(l, v.right); push(l, v.bottom);
	return 4; }


// ========================================================================== //
// ========================================================================== //
// CONVERTER<T> PUSH-OVERLOADS
//
// 'OK_IF((sizeof(T) > 0u))'		Checks if T is a complete type
//


template <bool USELUAERR = false, typename T
		  , OK_IF((sizeof(T) > 0u))
	, OK_IF(ISCONV(T, Converter<T>)) >
int			push(lua_State *l, T &v)
{
	return Converter<T>{v}.callPush(l);
}

template <bool USELUAERR = false, typename T
		  , OK_IF((sizeof(T) > 0u))
	, OK_IF(ISCONST(T))
	, typename NOCONST = DELCONST(T)
	, OK_IF(ISCONV(T, Converter<NOCONST>)) >
int			push(lua_State *l, T &v)
{
	return Converter<NOCONST>{v}.callPush(l);
}

template <bool USELUAERR = false, typename T
		  , OK_IF(ISPTR(T))
		  , typename NOPTR = DELPTR(T)
		  , OK_IF((sizeof(NOPTR) > 0u))
	, typename NOPTRCONST = DELCONST(NOPTR)
	, OK_IF(ISCONV(NOPTRCONST, Converter<NOPTRCONST>))
	>
int			push(lua_State *l, T v)
{
	if (v == nullptr)
		return push<USELUAERR>(l, nil);
	else
		return push<USELUAERR>(l, *v);
}


// ========================================================================== //
// ========================================================================== //
// KeysWrapper<...> PUSH-OVERLOADS
//


namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <size_t I, bool USELUAERR
		  , typename... ARGS, class T = KeysWrapper<ARGS...>
		  >
void		_dereference(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	ftlua::push<USELUAERR>(l, std::get<I>(wrap.tup));
	if (!lua_istable(l, -2))
	{
		if (USELUAERR)
			luaL_error(
				l, ft::f("Stack(-2) should have been a table\n%"
						 , ftlua::stacktostring(l)).c_str());
		else
			throw std::runtime_error(
				ft::f("Stack(-2) should have been a table\n%"
					  , ftlua::stacktostring(l)));
	}
	lua_gettable(l, -2);
	lua_remove(l, -2);
	return ;
}

template <size_t I, bool USELUAERR
		  , typename... ARGS, class T = KeysWrapper<ARGS...>
		  , OK_IF((sizeof...(ARGS) - I == 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	_dereference<I, USELUAERR>(l, wrap);
	return ;
}

template <size_t I, bool USELUAERR
		  , typename... ARGS, class T = KeysWrapper<ARGS...>
		  , OK_IF((sizeof...(ARGS) - I != 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	_dereference<I, USELUAERR>(l, wrap);
	_loopKey<I + 1, USELUAERR>(l, wrap);
	return ;
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <bool FIRSTISTOP = false, bool USELUAERR = false
		  , typename ...ARGS, class T = KeysWrapper<ARGS...> >
int			push(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	if (!FIRSTISTOP)
		lua_pushglobaltable(l);
	internal::_loopKey<0, USELUAERR>(l, wrap);
	return 1;
}


// ========================================================================== //
// ========================================================================== //
// MULTI-PUSH
//


namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <bool USELUAERR>
int			_pushLoop(lua_State *)
{
	return 0;
}

template <bool USELUAERR, typename HEAD, typename ...TAIL>
int			_pushLoop(lua_State *l, HEAD const &h, TAIL const &...t)
{
	return push<USELUAERR>(l, h) + _pushLoop<USELUAERR>(l, t...);
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <bool USELUAERR = false, typename ...ARGS>
int			multiPush(lua_State *l, ARGS const & ...args)
{
	return internal::_pushLoop<USELUAERR>(l, args...);
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# undef DELPTR
# undef DELCONST
# undef ISCONV
# undef ISPTR
# undef ISCONST
# undef OK_IF
# undef ISSAME

#endif
