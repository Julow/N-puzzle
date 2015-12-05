// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pop.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:16:24 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 15:44:05 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_POP_HPP
# define FTLUA_POP_HPP

# include <cstdint>
# include <string>

# include "liblua/lua.hpp"
# include "ft/Vec.hpp"
# include "ft/Rect.hpp"
# include "ft/utils.hpp"
# include "ft/assert.hpp" //debug

# include "ftlua/conversions.hpp"
# include "ftlua/types.hpp"
# include "ftlua/utils.hpp"


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define ADDPTR(T) typename std::add_pointer<T>::type
# define DELCONSTPTR(T) ADDPTR(DELCONST(DELPTR(T)))
# define OK_IFNODEF(PRED) typename std::enable_if<PRED>::type*
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value
# define ISCONST(A) std::is_const<A>::value
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISSAME(A, B) std::is_same<A, B>::value
# define OK_IFSAME(A, B) OK_IF(ISSAME(A, B))

// ========================================================================== //
// ========================================================================== //
// STRAIGHTFORWARD PUSH-OVERLOADS
//

// IMPLICIT CASTS DISABLED ========== //
template <class T, bool LuaErr = true, OK_IFSAME(DELCONST(T), bool) >
T			pop(lua_State *l, int index)
{
	bool		v;

	FTLUA_STACKASSERT(
		l, lua_isboolean(l, index), LuaErr
		, ft::f("ftlua::pop<%>.", ft::typesToString<T>(), index)
		, ft::f("Wrong type at index %.", index)
		);
	v = lua_toboolean(l, index);
	lua_remove(l, index);
	return v;
}

template <class T, bool LuaErr = true, OK_IFSAME(DELCONSTPTR(T), void*) >
T			pop(lua_State *l, int index)
{
	void		*v;

	FTLUA_STACKASSERT(
		l, lua_islightuserdata(l, index), LuaErr
		, ft::f("ftlua::pop<%>.", ft::typesToString<T>(), index)
		, ft::f("Wrong type at index %.", index)
		);
	v = lua_touserdata(l, index);
	lua_remove(l, index);
	return v;
}

// NO nil_t newtab_t dup_t dup_t-panic lua_CFunction
// NUMBERS/STRING =================== //
template <class T, bool LuaErr = false
		  , OK_IF(!ISPTR(T))
		  , OK_IF(!ISSAME(bool, DELCONST(T)))
		  , OK_IF(!std::is_floating_point<T>::value)
		  , OK_IF(ISCONV(T, lua_Integer))
		  >
T			pop(lua_State *l, int index)
{
	T		v;

	FTLUA_STACKASSERT(
		l, lua_isinteger(l, index), LuaErr
		, ft::f("ftlua::pop<%>.", ft::typesToString<T>(), index)
		, ft::f("Wrong type at index %.", index)
		);
	v = static_cast<T>(lua_tointeger(l, index));
	lua_remove(l, index);
	return v;
}

template <class T, bool LuaErr = false
		  , OK_IF(std::is_floating_point<T>::value)
		  , OK_IF(ISCONV(T, lua_Number))
		  >
T			pop(lua_State *l, int index)
{
	T		v;

	FTLUA_STACKASSERT(
		l, lua_isnumber(l, index), LuaErr
		, ft::f("ftlua::pop<%>.", ft::typesToString<T>(), index)
		, ft::f("Wrong type at index %.", index)
		);
	v = static_cast<T>(lua_tonumber(l, index));
	lua_remove(l, index);
	return v;
}

template <class T, bool LuaErr = true, OK_IFSAME(DELCONST(T), std::string) >
T			pop(lua_State *l, int index)
{
	std::string	v;

	FTLUA_STACKASSERT(
		l, lua_isstring(l, index), LuaErr
		, ft::f("ftlua::pop<%>.", ft::typesToString<T>(), index)
		, ft::f("Wrong type at index %.", index)
		);
	v = lua_tostring(l, index);
	lua_remove(l, index);
	return v;
}

//NO int-ptr float-ptr std::string-ptr

template <class T, bool LuaErr = true, OK_IFSAME(DELCONST(T), char const *) >
T			pop(lua_State *l, int index)
{
	char const	*v;

	FTLUA_STACKASSERT(
		l, lua_isstring(l, index), LuaErr
		, ft::f("ftlua::pop<%>.", ft::typesToString<T>(), index)
		, ft::f("Wrong type at index %.", index)
		);
	v = lua_tostring(l, index);
	lua_remove(l, index);
	return v;
}

// 'ft::' COMPOUND TYPES ============ //
template <class TT, bool LuaErr = true
		  , class T1 = typename TT::value_type
		  , OK_IFSAME(DELCONST(TT), ft::Vec2<T1>) >
TT			pop(lua_State *l, int index)
{
	int const	dt = index < 0 ? 1 : 0;
	TT			v;

	v.x = ftlua::pop<T1, LuaErr>(l, index);
	index += dt;
	v.y = ftlua::pop<T1, LuaErr>(l, index);
	return v;
}

template <class TT, bool LuaErr = true
		  , class T1 = typename TT::value_type
		  , OK_IFSAME(DELCONST(TT), ft::Vec3<T1>) >
TT			pop(lua_State *l, int index)
{
	int const	dt = index < 0 ? 1 : 0;
	TT			v;

	v.x = ftlua::pop<T1, LuaErr>(l, index);
	index += dt;
	v.y = ftlua::pop<T1, LuaErr>(l, index);
	index += dt;
	v.z = ftlua::pop<T1, LuaErr>(l, index);
	return v;
}

template <class TT, bool LuaErr = true
		  , class T1 = typename TT::value_type
		  , OK_IFSAME(DELCONST(TT), ft::Vec4<T1>) >
TT			pop(lua_State *l, int index)
{
	int const	dt = index < 0 ? 1 : 0;
	TT			v;

	v.x = ftlua::pop<T1, LuaErr>(l, index);
	index += dt;
	v.y = ftlua::pop<T1, LuaErr>(l, index);
	index += dt;
	v.z = ftlua::pop<T1, LuaErr>(l, index);
	index += dt;
	v.w = ftlua::pop<T1, LuaErr>(l, index);
	return v;
}

// ========================================================================== //
// ========================================================================== //
// CUSTOM::ftlua_pop() PUSH-OVERLOADS
//

// (T::ftlua_pop() -> T)
template <typename T, bool LuaErr = false
		  , OK_IF(ftlua::has_size<T>::value)
		  , OK_IF(ftlua::has_pop<T>::value)
		  >
T			pop(lua_State *l, int index)
{
	std::function<void(std::string)>    panic =
		[=](std::string const &str)
		{
			FTLUA_ERR(l, LuaErr, ft::f("ftlua::pop<%>(%) failed from:\n%"
									   , ft::typesToString<T>(), index, str));
		};
	return T::ftlua_pop(l, index, panic);
}

// (T::ftlua_pop() -> T*)
//		ftlua::has_ptrpop checks that [T] is base of [ftlua_pop return type]
//	hence the reinterpret_cast.
template <typename T, bool LuaErr = false
		  , OK_IF(ISPTR(T))
		  , class NoPtr = DELPTR(T)
		  , OK_IF(ftlua::has_size<NoPtr>::value)
		  , OK_IF(ftlua::has_ptrpop<NoPtr>::value)
		  >
T			pop(lua_State *l, int index)
{
	std::function<void(std::string)>    panic =
		[=](std::string const &str)
		{
			FTLUA_ERR(l, LuaErr, ft::f("ftlua::pop<%>(%) failed from:\n%"
									   , ft::typesToString<T>(), index, str));
		};
	return reinterpret_cast<T>(NoPtr::ftlua_pop(l, index, panic));
}

//NO Keywrappers



// TODO: CONTAINERS :(




# undef DELPTR
# undef DELCONST
# undef ISCONV
# undef ISPTR
# undef ISCONST
# undef OK_IF
# undef OK_IFNODEF
# undef ISSAME
# undef OK_IFISSAME
# undef ADDPTR
# undef DELCONSTPTR

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
#endif /* *********************************************************** POP_HPP */
