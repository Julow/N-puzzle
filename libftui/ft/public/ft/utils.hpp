// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 13:42:20 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/12 13:30:28 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef UTILS_H
# define UTILS_H

# include <iostream>

# include <ostream>
# include <sstream>
# include <string>
# include "ft/Vec.hpp"
# include "ft/Rect.hpp"

namespace ft
{

/*
** Compute 'format' and return a new string
** format: the '%' is used to substitute arguments
** std::ostream::operator<< is used for convertions
*/
template<typename ... ARGS>
std::string			f(char const *format, ARGS ...args);

/*
** Same but write into 'out'
*/
template<typename ... ARGS>
void				f(std::ostream &out, char const *format, ARGS ...args);

/*
** -
*/
template <typename T>
std::ostream		&operator<<(std::ostream &o, Vec2<T> const &rhs);

template <typename T>
std::ostream		&operator<<(std::ostream &o, Vec3<T> const &rhs);

template <typename T>
std::ostream		&operator<<(std::ostream &o, Vec4<T> const &rhs);

template <typename T>
std::ostream		&operator<<(std::ostream &o, Rect<T> const &rhs);

/*
** Impl
*/
static inline char const	*f_print(std::ostream &out, char const *format)
{
	while (*format != '\0' && *format != '%')
		out << *(format++);
	return (format);
}

static inline void			f_loop(std::ostream &out, char const *format)
{
	out << format;
}

template<typename HEAD, typename ... TAIL>
void				f_loop(std::ostream &out, char const *format,
						   HEAD&& arg, TAIL&& ...tail)
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
std::string			f(char const *format, ARGS ...args)
{
	std::ostringstream	out;

	f_loop(out, f_print(out, format), std::forward<ARGS>(args)...);
	return (out.str());
}

template<typename ... ARGS>
void				f(std::ostream &out, char const *format, ARGS ...args)
{
	f_loop(out, f_print(out, format), std::forward<ARGS>(args)...);
}

template <typename T>
std::ostream		&operator<<(std::ostream &o, Vec2<T> const &rhs)
{
	return (o << "{ " << rhs.x << ", " << rhs.y << " }");
}

template <typename T>
std::ostream		&operator<<(std::ostream &o, Vec3<T> const &rhs)
{
	return (o << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }");
}

template <typename T>
std::ostream		&operator<<(std::ostream &o, Vec4<T> const &rhs)
{
	return (o << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << ", "
			<< rhs.w << " }");
}

template <typename T>
std::ostream		&operator<<(std::ostream &o, Rect<T> const &rhs)
{
	return (o << "{ " << rhs.left << ", " << rhs.top
			<< " w:" << rhs.getWidth() << " h:" << rhs.getHeight() << " }");
}

std::string		truncmid(std::string const &str, int w = 11);

/*
** FT::pad printing
*/

std::string	padformat_openlvl(
	int line, std::string const &file, std::string const &function);
void		padformat_closelvl();
std::string	padformat_singlelvl(
	int line, std::string const &file, std::string const &function);

inline void	padformat_begin(
	int line, std::string const &file, std::string const &function)
{
	std::string const	header = padformat_openlvl(line, file, function);

	std::cout << header << '\n';
	return ;
}

template <typename ...ARGS>
void		padformat_begin(
	int line, std::string const &file, std::string const &function,
	const char *fmt , ARGS ...args)
{
	std::string const	header = padformat_openlvl(line, file, function);

	std::cout << header << "-> " << ft::f(fmt, args...) << '\n';
	return ;
}

inline void	padformat_end(void)
{
	padformat_closelvl();
	return ;
}

inline void	padformat_single(
	int line, std::string const &file, std::string const &function)
{
	std::string const	header = padformat_singlelvl(line, file, function);

	std::cout << header << '\n';
	return ;
}

template <typename ...ARGS>
void		padformat_single(
	int line, std::string const &file, std::string const &function,
	const char *fmt , ARGS ...args)
{
	std::string const	header = padformat_singlelvl(line, file, function);

	std::cout << header << "-> " << ft::f(fmt, args...) << '\n';
	return ;
}

# define FTPADARGS(...) __LINE__, __FILE__, __FUNCTION__, ##__VA_ARGS__

# define FTPADB(...) ft::padformat_begin(FTPADARGS(__VA_ARGS__))
# define FTPADE() ft::padformat_end()
# define FTPAD(...) ft::padformat_single(FTPADARGS(__VA_ARGS__))

};

#endif
