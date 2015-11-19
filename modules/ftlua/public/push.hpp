// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   push.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:13:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 18:36:39 by ngoguey          ###   ########.fr       //
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

# include "ftlua/types.hpp"
# include "ftlua/utils.hpp"

namespace ftlua // ========================================================== //
{

template<bool USELUAERR = false >
int			push(lua_State *l, bool const &v)
{ lua_pushboolean(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int8_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int16_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int32_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int64_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint8_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint16_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint32_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint64_t const &v)
{ lua_pushinteger(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, float const &v)
{ lua_pushnumber(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, double const &v)
{ lua_pushnumber(l, v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, std::string const &v)
{ lua_pushstring(l, v.c_str()); return 1;}

template<bool USELUAERR = false>
int			push(lua_State *l, bool const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushboolean(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int8_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int16_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int32_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, int64_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint8_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint16_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint32_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, uint64_t const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushinteger(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, float const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushnumber(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, double const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushnumber(l, *v); return 1;}
template<bool USELUAERR = false>
int			push(lua_State *l, std::string const *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushstring(l, v->c_str()); return 1;}


template<bool USELUAERR = false>
int			push(lua_State *l, char const *v)
{ if (v == NULL) lua_pushnil(l); else lua_pushstring(l, v); return 1; }
template<bool USELUAERR = false>
int			push(lua_State *l, void *const &v)
{ if (v == nullptr) lua_pushnil(l); else lua_pushlightuserdata(l, v); return 1; }
template<bool USELUAERR = false>
int			push(lua_State *l, nil_t const &)
{ lua_pushnil(l); return 1; }

template <bool USELUAERR = false, typename T>
inline int	push(lua_State *l, ft::Vec2<T> const &v)
{ push(l, v.x); push(l, v.y); return 2; }
template <bool USELUAERR = false, typename T>
inline int	push(lua_State *l, ft::Vec3<T> const &v)
{ push(l, v.x); push(l, v.y); push(l, v.z); return 3; }
template <bool USELUAERR = false, typename T>
inline int	push(lua_State *l, ft::Vec4<T> const &v)
{ push(l, v.x); push(l, v.y); push(l, v.z); push(l, v.w); return 4; }
template <bool USELUAERR = false, typename T>
inline int	push(lua_State *l, ft::Rect<T> const &v)
{ push(l, v.left); push(l, v.top); push(l, v.right); push(l, v.bottom); return 4; }

namespace internal // ======================================================= //
{

template<size_t I, bool USELUAERR
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

template<size_t I, bool USELUAERR
		 , typename... ARGS, class T = KeysWrapper<ARGS...>
		 , typename std::enable_if<(sizeof...(ARGS) - I == 1)>::type* = nullptr
		 >
void		_loopKey(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	_dereference<I, USELUAERR>(l, wrap);
	return ;
}

template<size_t I, bool USELUAERR
		 , typename... ARGS, class T = KeysWrapper<ARGS...>
		 , typename std::enable_if<(sizeof...(ARGS) - I != 1)>::type* = nullptr
		 >
void		_loopKey(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	_dereference<I, USELUAERR>(l, wrap);
	_loopKey<I + 1, USELUAERR>(l, wrap);
	return ;
}

}; // ============================================= END OF NAMESPACE INTERNAL //

template<bool FIRSTISTOP = false, bool USELUAERR = false
		 , typename... ARGS, class T = KeysWrapper<ARGS...> >
int					push(lua_State *l, KeysWrapper<ARGS...> const &wrap)
{
	(void)l;
	(void)wrap;
	if (!FIRSTISTOP)
		lua_pushglobaltable(l);
	internal::_loopKey<0, USELUAERR>(l, wrap);
	return 1;
}


}; // ================================================ END OF NAMESPACE FTLUA //

#endif
