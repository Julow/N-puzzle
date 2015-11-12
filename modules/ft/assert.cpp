/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 07:10:26 by ngoguey           #+#    #+#             */
//   Updated: 2015/11/09 15:17:23 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "ft/assert.hpp"
#include "ft/utils.hpp"
#include <iostream>

namespace ft
{
namespace Assert
{
void			report(std::string const &condition,
						  int line,
						  std::string const &file,
						  std::string const &function,
						  std::string const &msg /* = "" */)
{
	if (msg == "")
		ft::f(std::cerr, "[\e[31m%\e[0m] failed, %:%:%\n"
			  , condition, file, function.substr(0, 10), line);
	else
		ft::f(std::cerr, "[\e[31m%\e[0m] failed, %:%:% %\n"
			  , condition, file, function.substr(0, 10), line, msg);
	return ;
	(void)function;
}

std::string			reportStr(std::string const &condition,
							  int line,
							  std::string const &file,
							  std::string const &function,
							  std::string const &msg /* = "" */)
{
	if (msg == "")
		return ft::f("[%] failed, %:%:%", condition, file
					 , function.substr(0, 10), line);
	else
		return ft::f("[%] failed, %:%:% %", condition, file
					 , function.substr(0, 10), line, msg);
	(void)function;
}

};
};
