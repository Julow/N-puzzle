/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 23:17:10 by juloo             #+#    #+#             */
/*   Updated: 2015/09/25 00:38:43 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>
#include <tuple>

void			f_loop(std::ostringstream &out)
{
}

template<typename HEAD, typename ... TAIL>
void			f_loop(std::ostringstream &out, HEAD&& arg, TAIL&& ...tail)
{
	out << arg;
	f_loop(out, std::forward<TAIL>(tail)...);
}

template<typename ... ARGS>
std::string		f(ARGS ...args)
{
	std::ostringstream	out;

	f_loop(out, std::forward<ARGS>(args)...);
	return (out.str());
}
