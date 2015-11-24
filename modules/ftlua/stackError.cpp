// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stackError.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:16:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 10:47:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "ft/utils.hpp"

# include "ftlua/stackassert.hpp"
# include "ftlua/utils.hpp"


namespace ftlua // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


std::string		stackError(lua_State *l, char const *pred
						   , std::string const &where, std::string const &why)
{
	return ft::f("\"%\" failed in % \n%%"
				 , pred, where, ftlua::stacktostring(l), why);
}

StackError::StackError(StackError const &src) : std::runtime_error(src) {}
StackError::StackError(std::string const &str) : std::runtime_error(str) {}
StackError::~StackError() {}

}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
