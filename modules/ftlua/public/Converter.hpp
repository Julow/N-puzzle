// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Converter.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/21 10:27:37 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/22 13:39:57 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CONVERTER_HPP
# define FTLUA_CONVERTER_HPP

# include <type_traits>
# include "liblua/lua.hpp"

namespace ftlua // ========================================================== //
{

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr

template<typename T
		 , OK_IF(!std::is_void<T>::value)>
class Converter
{
public:

	/* CONSTRUCTION ***************** */
	typedef int				(*push_t)(lua_State *l, T &);

	Converter(T &v, push_t p) : _v(v), _p(p) {}
	Converter(Converter const &src) : _v(src._v), _p(src._p) {}
	~Converter() {}

	Converter() = delete;
	Converter				&operator=(Converter &&rhs) = delete;


	/* BEHAVIOUR ******************** */
	template <bool USELUAERR = false>
	int			callPush(lua_State *l)
		{
			return this->_p(l, this->_v);
		}

private:
	T						&_v;
	push_t					_p;
};

}; // ================================================ END OF NAMESPACE FTLUA //

# undef OK_IF

#endif /* *********************************************** FTLUA_CONVERTER_HPP */
