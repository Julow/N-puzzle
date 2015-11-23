// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stackError.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/23 13:16:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/23 13:39:37 by ngoguey          ###   ########.fr       //
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
	std::string		ret("");

	ret += "\"";
	ret += pred;
	ret += "\" failed in ";
	ret += where;
	ret += "\n";
	ret += ftlua::stacktostring(l);
	ret += why;
	ret += "\n";
	return ret;
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE FTLUA //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
