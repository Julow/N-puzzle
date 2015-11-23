// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stackError.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:16:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/23 13:46:14 by ngoguey          ###   ########.fr       //
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


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
