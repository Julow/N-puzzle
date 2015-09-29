// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   assert.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/29 07:10:26 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/29 08:01:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/assert.hpp"
#include "ft/utils.hpp"
#include <iostream>

namespace ft
{
namespace Assert
{
void			Report(std::string const &condition,
						  int line,
						  std::string const &file,
						  std::string const &function,
						  std::string const &msg /* = "" */)
{
	if (msg == "")
		ft::f(std::cerr, "[\e[31m%\e[0m] failed, %:%\n"
			  , condition, file, line);
	else
		ft::f(std::cerr, "[\e[31m%\e[0m] failed, %:% %\n"
			  , condition, file, line, msg);
	return ;
	(void)function;
}

std::string			ReportStr(std::string const &condition,
							  int line,
							  std::string const &file,
							  std::string const &function,
							  std::string const &msg /* = "" */)
{
	if (msg == "")
		return ft::f("[%] failed, %:%", condition, file, line);
	else
		return ft::f("[%] failed, %:% %", condition, file, line, msg);
	(void)function;
}

};
};
