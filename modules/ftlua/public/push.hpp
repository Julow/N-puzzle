// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:13:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/26 14:09:02 by ngoguey          ###   ########.fr       //
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
template <bool FIRSTISTOP, bool USELUAERR
		  , typename... ARGS>
int			push(lua_State *l, KeysWrapper<ARGS...> const &wrap);

// Push (T to Converter<T>) || (const-T to Converter<const-T>)
template <bool USELUAERR, typename T
		  , OK_IFNODEF((sizeof(T) > 0u))
		  , OK_IFNODEF(ISCONV(T, Converter<T>)) >
int			push(lua_State *l, T &v);


// Push (T to Converter<T const>)
//TODO: validate this overload
template <bool USELUAERR, typename T
		  , OK_IFNODEF((sizeof(T) > 0u))
	, OK_IFNODEF(!ISCONST(T))
	// , OK_IFNODEF(ISCONST(T))
	// , typename NOCONST
	, OK_IFNODEF(ISCONV(T, Converter<const T>)) >
int			push(lua_State *l, T &v);


// Push (const-T to Converter<T>) NOT(const-T to Converter<T const>)
// Overload allowing const cast in User's cast-operator
template <bool USELUAERR, typename T
		  , OK_IFNODEF((sizeof(T) > 0u))
	, OK_IFNODEF(ISCONST(T))
	, typename NOCONST
	, OK_IFNODEF(ISCONV(T, Converter<NOCONST>))
	, OK_IFNODEF(!ISCONV(T, Converter<T>))>
	int			push(lua_State *l, T &v);

// Push (T* to push<T>) || (T-const * to push<T-const>)
template <bool USELUAERR, typename T
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
	int const	index = i.i < 0 ? -i.i : i.i;

	FTLUA_STACKASSERT(
		l, index <= lua_gettop(l), USELUAERR
		, ft::f("ftlua::push(dup(%)).", i.i)
		, ft::f("Stack index does not exist.")
		);
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
		  , typename... ARGS
		  >
void		_dereference(lua_State *l, KeysWrapper<ARGS...> const &wrap)
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
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I == 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	_dereference<I, LuaErr>(l, wrap);
	return ;
}

template <size_t I, bool LuaErr
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I != 1))
		  >
void		_loopKey(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	_dereference<I, LuaErr>(l, wrap);
	_loopKey<I + 1, LuaErr>(l, wrap);
	return ;
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <bool FIRSTISTOP = false, bool LuaErr = false
		  , typename ...ARGS>
int			push(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	if (!FIRSTISTOP)
		lua_pushglobaltable(l);
	internal::_loopKey<0, LuaErr>(l, wrap);
	return 1;
}


// ========================================================================== //
// ========================================================================== //
// CONTAINERS<...> PUSH-OVERLOADS
//

template<typename T>
struct has_const_iterator
{
private:
	typedef char						yes;
	typedef struct { char array[2]; }	no;

	template<typename C>
	static yes							test(typename C::const_iterator*);
	template<typename C>
	static no							test(...);
public:
	static const bool					value = sizeof(test<T>(0)) == sizeof(yes);
	typedef T							type;
};

template <typename T>
struct has_begin_end //TODO understand and rewrite
{

#define CONSTIT typename C::const_iterator (C::*)() const
#define VOID_IF(PRED) typename std::enable_if<PRED, void>::type*

	template<typename C>
	static char		(&f(
						VOID_IF(ISSAME(decltype(static_cast<CONSTIT>(&C::begin)), CONSTIT)))
		)[1];

	template<typename C>
	static char		(&f(...))[2];

	template<typename C>
	static char		(&g(
						VOID_IF(ISSAME(decltype(static_cast<CONSTIT>(&C::end)), CONSTIT)))
		)[1];
	template<typename C>
	static char		(&g(...))[2];

	static bool const beg_value = sizeof(f<T>(0)) == 1;
	static bool const end_value = sizeof(g<T>(0)) == 1;
};

template<typename T>
struct is_container : std::integral_constant<bool, has_const_iterator<T>::value && has_begin_end<T>::beg_value && has_begin_end<T>::end_value>
{ };

template <bool LuaErr = false
		  , class T
		  , OK_IF(is_container<T>::value)
		  >
int			push(lua_State *l, T &cont)
{
	int			i(0);
	int			inc;
	int const	tabI = lua_gettop(l) + 1;
	int const	eltI = tabI + 1;

	push(l, newtab);				// []
	for (auto it : cont)
	{
		inc = push(l, it);			// vn, v1, []
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
