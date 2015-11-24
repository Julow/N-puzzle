// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stackassert.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:14:16 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 10:47:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FTLUA_STACKASSERT_HPP
# define FTLUA_STACKASSERT_HPP

# include <string>
# include <stdexcept>

# include "liblua/lua.hpp"

namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

std::string		stackError(lua_State *l, char const *pred
						   , std::string const &where, std::string const &why);


class StackError : public std::runtime_error
{
public:

	/* CONSTRUCTION ***************** */
	StackError(std::string const &str);
	StackError(StackError const &src);
	~StackError();

	StackError() = delete;
	StackError		&operator=(StackError const &rhs) = delete;

protected:
private:
};

# define FTLUA_SE_MSG(...) ftlua::stackError(__VA_ARGS__).c_str()
# define FTLUA_STACKASSERT(L, PRED, LUAERR, WHERE, WHY)					\
	do																	\
	{																	\
		if (!(PRED))													\
		{																\
			if (LUAERR)													\
				luaL_error(L, FTLUA_SE_MSG(L, #PRED, WHERE, WHY));		\
			else														\
				throw ftlua::StackError(FTLUA_SE_MSG(L, #PRED, WHERE, WHY)); \
		}																\
	} while(0)



}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


#endif /* ********************************************* FTLUA_STACKASSERT_HPP */
