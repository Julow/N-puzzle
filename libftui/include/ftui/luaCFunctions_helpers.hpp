// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   luaCFunctions_helpers.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:23:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/05 16:04:54 by ngoguey          ###   ########.fr       //
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

template<size_t InCount, size_t OutCount, typename Ret, typename... Args>
struct Fun : Ifun
{
private:
	typedef Ret (*fun_t)(Args...);
public:
	Fun(fun_t funptr) : _funptr(funptr){};

	fun_t			_funptr;	
};

template<size_t InCount, size_t OutCount, typename Ret, typename... Args>
Fun<InCount, OutCount, Ret, Args...>	make_fun(Ret (*funptr)(Args...))
{
	return Fun<InCount, OutCount, Ret, Args...>{funptr};
}


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
};

template <size_t InCount, size_t OutCount
		  , typename Ret, class C, typename... Args>
MemFun<InCount, OutCount, Ret, C, Args...>	make_memfun(
	C *inst, Ret (C::*funptr)(Args...))
{
	return MemFun<InCount, OutCount, Ret, C, Args...>{inst, funptr};
}




template <size_t InCount, size_t OutCount, typename... DestFunctions>
int			helperFun(lua_State *l, DestFunctions... destfunctions)
{
	(void)l;
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
