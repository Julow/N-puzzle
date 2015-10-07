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
# include <functional>

# include "ft/Vec.hpp"

namespace ftui
{


void        luaFT_stackdump(lua_State *L)
{
	int const               top = lua_gettop(L);
	int                     i;
	std::function<void()>   funcs[] =
	{
		[=, &i](){std::cout << "  none" << "\n";},
		[=, &i](){std::cout << "   nil" << "\n";},
		[=, &i](){std::cout << "  bool: " << lua_toboolean(L, i) << "\n";},
		[=, &i](){std::cout << " lusrd" << "\n";},
		[=, &i](){std::cout << "   nbr: " << lua_tonumber(L, i) <<  "\n";},
		[=, &i](){std::cout << "   str: " << lua_tostring(L, i) << "\n";},
		[=, &i](){std::cout << "   tab" << "\n";},
		[=, &i](){std::cout << "  func: " << (void*)lua_tocfunction(L, i) << "\n";},
		[=, &i](){std::cout << "  usrd" << "\n";},
		[=, &i](){std::cout << "thread" << "\n";},
	};
	std::cout << "Stack dump: " << top << " Elements" << std::endl;
	for (i = 1; i <= top; i++)
	{
		std::cout << "[" << i << "]";
		funcs[lua_type(L, i) + 1]();
	}
	return ;
}



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
/*
template <typename T>
inline void			popStack(lua_State *l)
{
	std::cout << "popStack x1\n";
	lua_pop(l, 1);
	return ;
}
*/
/*
template <>
inline void		popStack<ft::Vec2<int>>(lua_State *l)
{
	std::cout << "popStack x2\n";
	lua_pop(l, 2);
	return ;
}
*/


template <typename T>
constexpr inline int	decay(){ return 1; }

template <>
constexpr inline int	decay<ft::Vec2<int>>(){ return 2; }


template <typename T>
inline T			retreiveParam(lua_State *, int)
{
	return T();
}

template <>
inline double		retreiveParam<double>(lua_State *l, int numIn)
{
	std::cout << "retreive double with numIn=" << numIn << "\n";
	luaFT_stackdump(l);
	double	v(luaL_checknumber(l, -numIn));
	ft::f(std::cout, "got '%'\n", v);
	
	lua_remove(l, -numIn);
	return v;
}

template <>
inline std::string		retreiveParam<std::string>(lua_State *l, int numIn)
{
	std::cout << "retreive string with numIn=" << numIn << "\n";
	luaFT_stackdump(l);
	std::string		v(luaL_checklstring(l, -numIn, NULL));
	ft::f(std::cout, "got '%'\n", v);
	
	lua_remove(l, -numIn);
	return v;
}

template <>
inline int				retreiveParam<int>(lua_State *l, int numIn)
{
	std::cout << "\n";
	luaFT_stackdump(l);
	int	v(luaL_checkinteger(l, -numIn));
	ft::f(std::cout, "got '%'\n", v);
	
	lua_remove(l, -numIn);
	return v;
}

template <>
inline ft::Vec2<int>		retreiveParam<ft::Vec2<int>>(lua_State *l, int numIn)
{
	std::cout << "retreive Vec2<int> with numIn=" << numIn << "\n";
	luaFT_stackdump(l);
	ft::Vec2<int>		v(luaL_checkinteger(l, -numIn)
						  , luaL_checkinteger(l, -numIn + 1));
	ft::f(std::cout, "got '%' '%'\n", v.x, v.y);
	
	lua_remove(l, -numIn + 1);
	lua_remove(l, -numIn + 1);
	return v;
}



template <int NumIn, int NumOut
		  , typename Ret, typename... Retreived>
void		helper(lua_State *, Ret (*f)(), Retreived...r)
{
	std::cout << "helper last\n";
	reinterpret_cast<Ret (*)(Retreived...)>(f)(r...);
	return ;
}

template <int NumIn, int NumOut
		  , typename Ret, typename Head, typename... ArgsLeft
		  , typename... Retreived>
void		helper(lua_State *l, Ret (*f)(Head, ArgsLeft...), Retreived...r)
{
	std::cout << "helper mid all\n";
	Head		p{retreiveParam<Head>(l, NumIn)};

	
	std::cout << "helper mid\n";
	helper<NumIn - decay<Head>(), NumOut>(l, reinterpret_cast<Ret (*)(ArgsLeft...)>(f)
		   , (r)...
		   , p
		);
	return ;
}

// * Fun ******** //
template <int NumIn, int NumOut, typename Ret, typename... Args>
int			helperFun(lua_State *l, Ret (*f)(Args...))
{
	std::cout << "helperFun entry\n";
	helper<NumIn, NumOut>(l, f);
	return (0);
}

// * MemFun ***** //


};

#endif
