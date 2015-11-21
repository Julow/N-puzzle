// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Converter.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/21 10:27:37 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/21 15:04:07 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_CONVERTER_HPP
# define FTLUA_CONVERTER_HPP

# include "liblua/lua.hpp"

namespace ftlua // ========================================================== //
{

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr

template<typename T
		, OK_IF(!std::is_void<T>)>
class Converter
{
public:

	/* CONSTRUCTION ***************** */
	typedef int				(*push_t)(lua_State *l, T const &);

	Converter(T const &v, push_t p) : _v(v), _p(p) { }
	Converter(Converter const &src) : _v(src._v), _p(src._p) { }
	~Converter();

	Converter() = delete;
	Converter				&operator=(Converter &&rhs) = delete;


	/* BEHAVIOUR ******************** */
	template <bool USELUAERR = false>
	int			push(lua_State *l)
		{
			return this->_p(l, this->_v);
		}

private:
	T const					&_v;
	push_t					_p;
};

}; // ================================================ END OF NAMESPACE FTLUA //

# undef OK_IF

#endif /* *********************************************** FTLUA_CONVERTER_HPP */
