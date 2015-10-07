// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   luaCFunctions_helpers.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:23:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/06 12:42:52 by juloo            ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef LUACFUNCTIONS_HELPERS_HPP
# define LUACFUNCTIONS_HELPERS_HPP

#include "ftui/libftui.hpp"

# include <iostream>

# include "ft/Vec.hpp"

namespace ftui
{

class Ifun
{
public:
	virtual ~Ifun(){};
};

// * Fun ******** //
template<size_t InCount, size_t OutCount, typename Ret, typename... Args>
struct Fun
{
private:
	typedef Ret (*fun_t)(Args...);
public:
	Fun(fun_t funptr) : _funptr(funptr){};

	fun_t			_funptr;
	Ret				ret;
};

template<size_t InCount, typename... Args>
struct Fun<InCount, 0u, void, Args...>
{
private:
	typedef void (*fun_t)(Args...);
public:
	Fun(fun_t funptr) : _funptr(funptr){};

	fun_t			_funptr;
};

template<size_t InCount, size_t OutCount, typename Ret, typename... Args>
Fun<InCount, OutCount, Ret, Args...>	make_fun(Ret (*funptr)(Args...))
{
	return Fun<InCount, OutCount, Ret, Args...>{funptr};
}



// * MemFun ***** //
template<size_t InCount, size_t OutCount
		 , typename Ret, class C, typename... Args>
struct MemFun : Ifun
{
private:
	typedef Ret (C::*fun_t)(Args...);
public:
	MemFun(C *inst, fun_t funptr) : _instance(inst), _funptr(funptr){};

	C				*_instance;
	fun_t			_funptr;	
	Ret				ret;
};

template <size_t InCount, size_t OutCount
		  , typename Ret, class C, typename... Args>
MemFun<InCount, OutCount, Ret, C, Args...>	make_memfun(
	C *inst, Ret (C::*funptr)(Args...))
{
	return MemFun<InCount, OutCount, Ret, C, Args...>{inst, funptr};
}


/*
  template <typename Ret, typename... Args, std::size_t ...I>
  Ret                call_func(
  Ret (*fptr)(Args...), std::tuple<Args...> params, std::index_sequence<I...>)
  {
  return fptr(std::get<I>(params)...);
  }
  template <typename Ret, typename... Args>
  Ret					delayed_dispatch(
  Ret (*fptr)(Args...), std::tuple<Args...> params)
  {
  return call_func(fptr, params, std::index_sequence_for<Args...>{});
  }
*/

template <typename T>
inline void			popStack(lua_State *l)
{
	std::cout << "popStack x1\n";
	lua_pop(l, 1);
	return ;
}


template <>
inline void		popStack<ft::Vec2<int>>(lua_State *l)
{
	std::cout << "popStack x2\n";
	lua_pop(l, 2);
	return ;
}



template <typename T>
inline T			retreiveParam(lua_State *)
{
	return T();
}

template <>
inline double		retreiveParam<double>(lua_State *l)
{
	std::cout << "\n";
	return luaL_checknumber(l, -1);
}

template <>
inline std::string		retreiveParam<std::string>(lua_State *l)
{
	std::cout << "\n";
	return std::string(luaL_checklstring(l, -1, NULL));
}

template <>
inline int				retreiveParam<int>(lua_State *l)
{
	std::cout << "\n";
	return luaL_checkinteger(l, -1);
}

template <>
inline ft::Vec2<int>		retreiveParam<ft::Vec2<int>>(lua_State *l)
{
	std::cout << "\n";
	return ft::Vec2<int>(luaL_checkinteger(l, -2), luaL_checkinteger(l, -1));
}

template <>
inline ft::Vec2<double>	retreiveParam<ft::Vec2<double>>(lua_State *l)
{
	std::cout << "\n";
	return ft::Vec2<double>(luaL_checknumber(l, -2), luaL_checknumber(l, -1));
}


template <typename Ret, typename... Retreived>
void		helper(lua_State *l, Ret (*f)(), Retreived...r)
{
	std::cout << "helper last\n";
	reinterpret_cast<Ret (*)(Retreived...)>(f)(r...);
	return ;
}

template <typename Ret, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helper(lua_State *l, Ret (*f)(Head, ArgsLeft...), Retreived...r)
{
	Head		p{retreiveParam<Head>(l)};

	popStack<Head>(l);
	std::cout << "helper mid\n";
	helper(l, reinterpret_cast<Ret (*)(ArgsLeft...)>(f)
		   , p
		   , (r)...
		);
	return ;
}

// * Fun ******** //
template <typename Ret, typename... Args>
int			helperFun(lua_State *l, Ret (*f)(Args...))
{
	(void)l;
//	helper<func<Ret, Args...>>(reinterpret_cast<func<Ret, Args...>>(f));
/*	helper< Wrap<Ret, Args...> >(
 		static_cast<typename Wrap<Ret, Args...>::fun_t>(f)

		);*/

	std::cout << "helperFun entry\n";
	helper(l, f);
//	helper(static_cast<typename Wrap<Ret, Args...> >(f));
//	reinterpret_cast<Wrap<Ret, Args...> >(f);
	return (0);
}

// * MemFun ***** //


};

#endif
