// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pop.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/19 12:16:24 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 18:46:39 by juloo            ###   ########.fr       //
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

# include "ftlua/types.hpp"
# include "ftlua/utils.hpp"

# define DELPTR(T) typename std::remove_pointer<T>::type
# define DELCONST(T) typename std::remove_const<T>::type
# define ADDCONST(T) typename std::add_const<T>::type
# define OK_IFNODEF(PRED) typename std::enable_if<PRED>::type*
# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value
# define ISINT(A) std::is_integral<A>::value
# define ISFLOAT(A) std::is_floating_point<A>::value
# define ISCONST(A) std::is_const<A>::value
# define ISCONV(A, B) std::is_convertible<A, B>::value
# define ISSAME(A, B) std::is_same<A, B>::value


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T>
void		pushInteger(lua_State *l, T const&v)
{
	lua_pushinteger(l, v);
	return ;
}
template <class T>
T			popInteger(lua_State *l, int index)
{
	return luaL_checkinteger(l, index);
}


template <class T>
void		pushFloating(lua_State *l, T const&v)
{
	lua_pushnumber(l, v);
	return ;
}
template <class T>
T			popFloating(lua_State *l, int index)
{
	return luaL_checknumber(l, index);
}

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template <class T>
class Value
{
};

#define VALUE_OVERLOAD(TYPE, SIZE, PUSHFN, POPFN)			\
	template <>												\
	class Value<TYPE>										\
	{														\
	public:													\
		Value(TYPE const &ref) : _ref(ref) {}				\
		Value(Value const &src) : _ref(src._ref) {}			\
		~Value() {}											\
															\
		Value() = delete;									\
		Value	&operator=(Value &&rhs) = delete;			\
															\
		static constexpr auto		size = SIZE;			\
		static constexpr auto		pushFn = PUSHFN<TYPE>;	\
		static constexpr auto		popFn = POPFN<TYPE>;	\
															\
	private:												\
		TYPE const					&_ref;					\
															\
	};


VALUE_OVERLOAD(int8_t,	1, &internal::pushInteger, &internal::popInteger)
VALUE_OVERLOAD(int16_t,	1, &internal::pushInteger, &internal::popInteger)
VALUE_OVERLOAD(int32_t,	1, &internal::pushInteger, &internal::popInteger)
VALUE_OVERLOAD(int64_t,	1, &internal::pushInteger, &internal::popInteger)
VALUE_OVERLOAD(uint8_t,	1, &internal::pushInteger, &internal::popInteger)
VALUE_OVERLOAD(uint16_t,1, &internal::pushInteger, &internal::popInteger)
VALUE_OVERLOAD(uint32_t,1, &internal::pushInteger, &internal::popInteger)
VALUE_OVERLOAD(uint64_t,1, &internal::pushInteger, &internal::popInteger)

VALUE_OVERLOAD(float,	1, &internal::pushFloating, &internal::popFloating)
VALUE_OVERLOAD(double,	1, &internal::pushFloating, &internal::popFloating)


template <bool LuaErr = false
		  , class T
		  , class TNoC = DELCONST(T)
		  , class Val = Value<TNoC>
		  , OK_IF(ISCONV(TNoC, Val))
		  >
int				testpush(lua_State *l, T const &v)
{
	Val::pushFn(l, v);
	return Val::size;
}


// template <bool LuaErr, size_t acc>
// size_t		_pushLoop(lua_State *)
// {
// 	return acc;
// }

// template <bool LuaErr, size_t acc

// 		  , typename HEAD, typename ...TAIL>
// size_t		_pushLoop(lua_State *l, HEAD const &h, TAIL const &...t)
// {
// 	return push<LuaErr>(l, h) + _pushLoop<LuaErr>(l, t...);
// 	// return push<LuaErr>(l, h) + _pushLoop<LuaErr>(l, t...);
// }


// template <bool LuaErr = false>
// int				testmultipush(lua_State *l, ARGS const &args)
// {

// }


// inline void	test(void)
// {
// 	lua_State *l = nullptr;

// 	testpush(l, int8_t{});
// 	testpush(l, int{});
// 	testpush(l, (unsigned long long int){});

// }


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# undef DELPTR
# undef DELCONST
# undef ISCONV
# undef ISPTR
# undef ISCONST
# undef OK_IF
# undef ISSAME

#endif /* *********************************************************** POP_HPP */
