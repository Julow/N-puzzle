// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   luaCFunctions_helpers.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:23:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/05 19:29:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "ftui/libftui.hpp"

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
T			retreiveParam(lua_State *)
{
	return T();
}

template <>
double		retreiveParam<double>(lua_State *l)
{
	return luaL_checknumber(l, -1);
}

template <>
std::string		retreiveParam<std::string>(lua_State *l)
{
	return std::string(luaL_checklstring(l, -1, NULL));
}

template <>
int				retreiveParam<int>(lua_State *l)
{
	return luaL_checkinteger(l, -1);
}

template <>
Vec2<int>		retreiveParam<Vec2<int>>(lua_State *l)
{
	return Vec2<int>(luaL_checkinteger(l, -1), luaL_checkinteger(l, -1));
}

template <>
Vec2<double>	retreiveParam<Vec2<double>>(lua_State *l)
{
	return Vec2<double>(luaL_checknumber(l, -1), luaL_checknumber(l, -1));
}



// * Fun ******** //
template<size_t InCount, size_t OutCount, typename Ret, typename... Args>
static inline void		helper(
	lua_State *l, Fun<InCount, OutCount, Ret, Args...> functor)
{
	std::cout << "helper for Fun \n";
	// helper2<Fun<InCount, OutCount, Ret, Args...>, Args...>(l, functor);
	// functor.ret = functor._funptr();
	(void)l;
	(void)functor;
	return ;
}

// * MemFun ***** //
template<size_t InCount, size_t OutCount
		 , typename Ret, class C, typename... Args>
static inline void		helper(
	lua_State *l, MemFun<InCount, OutCount, Ret, C, Args...> functor)
{
	std::cout << "helper for memFun \n";
	(void)l;
	(void)functor;
	return ;
}



static inline void		helperLoop(lua_State *l)
{
	std::cout << "helperloop end\n";
	(void)l;
	return ;
}

template <typename Head, typename... Tail>
static inline void		helperLoop(lua_State *l, Head &&h, Tail&& ... t)
{
	std::cout << "helperloop\n";	
	helperLoop(l, std::forward<Tail>(t)...);
	helper(l, h);
	return ;
}


template <size_t InCount, size_t OutCount, typename... DestFunctions>
int			helperFun(lua_State *l, DestFunctions... destfunctions)
{
	(void)l;
	helperLoop(l, std::forward<DestFunctions>(destfunctions)...);
	// (void)destfunctions...;
	return (OutCount);
}

// template <size_t InCount, size_t OutCount
// 		  , typename... ArgsIn, typename... ArgsOut>
// int			helperMemfun(lua_State *l
// 					  , std::tuple<ArgsIn...> in
// 					  , std::tuple<ArgsOut...> out)
// {
	
// 	return (OutCount);
// }

};
