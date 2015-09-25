/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/25 13:42:20 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/25 13:52:35 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <ostream>
# include <sstream>
# include <string>

namespace ft
{

/*
** Compute 'format' and return a new string
** format: the '%' is used to substitute arguments
** std::ostream::operator<< is used for convertions
*/
template<typename ... ARGS>
std::string		f(char const *format, ARGS ...args);

/*
** Same but write into 'out'
*/
template<typename ... ARGS>
void			f(std::ostream &out, char const *format, ARGS ...args);

/*
** Impl
*/
char const		*f_print(std::ostream &out, char const *format)
{
	while (*format != '\0' && *format != '%')
		out << *(format++);
	return (format);
}

void			f_loop(std::ostream &out, char const *format)
{
	out << format;
}

template<typename HEAD, typename ... TAIL>
void			f_loop(std::ostream &out, char const *format, HEAD&& arg, TAIL&& ...tail)
{
	if (*format != '%')
	{
		f_loop(out, format);
		return ;
	}
	out << arg;
	f_loop(out, f_print(out, format + 1), std::forward<TAIL>(tail)...);
}

template<typename ... ARGS>
std::string		f(char const *format, ARGS ...args)
{
	std::ostringstream	out;

	f_loop(out, f_print(out, format), std::forward<ARGS>(args)...);
	return (out.str());
}

template<typename ... ARGS>
void			f(std::ostream &out, char const *format, ARGS ...args)
{
	f_loop(out, f_print(out, format), std::forward<ARGS>(args)...);
}

};

#endif
