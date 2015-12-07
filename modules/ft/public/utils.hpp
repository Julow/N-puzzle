// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   utils.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/25 13:42:20 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 15:43:33 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef UTILS_H
# define UTILS_H

# include <ostream>
# include <sstream>
# include <string>
# include <typeinfo>
# include <tuple>

# include "ft/type_traits.hpp"
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

/*
** valtostring
*/
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
template <bool, class T>
struct Stringify {};

template <class T>
struct Stringify<true, T>
{
	static std::string	toString(T const&v) { return ft::f("%", v); }
};

template <class T>
struct Stringify<false, T>
{
	static char const	*toString(T const&) { return typeid(T).name(); }
};
}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISPTR(A) std::is_pointer<A>::value

template <class T
		  // , OK_IF(!ISPTR(T))
		  >
std::string				valToString(T const &v)
{
	return internal::Stringify<ft::is_printable<T>::value, T>::toString(v);
}

// template <class T, class ...ARGS
// 		  // , OK_IF(ISPTR(T))
// 		  >
// std::string				valToString(T (*v)(ARGS...))
// {
// 	return internal::Stringify<ft::is_printable<T>::value, T>::toString(v);
// }

# undef OK_IF
# undef ISPTR

// tupletostring ============================================================ //
//
namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

inline std::string		_variadictostring(void)
{
	return "";
}

template <class Head>
std::string				_variadictostring(Head const &v)
{
	return valToString(v);
}

template <class Head, class ...Tail>
std::string				_variadictostring(Head const &v, Tail const &...tail)
{
	return valToString(v) + ", " + _variadictostring(tail...);
}

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
template <size_t I
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I == 1))
		  >
std::string				_tupletostring(std::tuple<ARGS...> const &wrap)
{
	return valToString(std::get<I>(wrap));
}

template <size_t I
		  , typename... ARGS
		  , OK_IF((sizeof...(ARGS) - I != 1))
		  >
std::string				_tupletostring(std::tuple<ARGS...> const &wrap)
{

	return valToString(std::get<I>(wrap)) + ", "
		+ _tupletostring<I + 1>(wrap);
}

inline std::string		_typestostring(void)
{
	return "";
}
template <class Head>
std::string				_typestostring(void)
{
	return std::string(typeid(Head).name());
}
template <class Head, class Head2, class... Args>
std::string				_typestostring(void)
{
	return std::string(typeid(Head).name()) + ", "
		+ _typestostring<Head2, Args...>();
}


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template <class ...Args>
std::string				variadicToString(Args const &...args)
{
	return internal::_variadictostring(args...);
}

template <class ...Args>
std::string				tupleToString(std::tuple<Args...> const &tup)
{
	return internal::_tupletostring<0>(tup);
}

template <class ...Args, OK_IF((sizeof...(Args) > 0))>
std::string				typesToString(void)
{
	return internal::_typestostring<Args...>();
}

template <class ...Args, OK_IF((sizeof...(Args) == 0))>
std::string				typesToString(void)
{
	return "";
}

# undef OK_IF

namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class F>
struct funType;

template <class Ret, class ...Args>
struct funType<Ret (*)(Args...)>
{
	static std::string	toString(void)
		{
			return ft::f("% (*)(%)"
						 , ft::typesToString<Ret>()
						 , ft::typesToString<Args...>()
				);
		}
};

template <class Ret, class C, class ...Args>
struct funType<Ret (C::*)(Args...)>
{
	static std::string	toString(void)
		{
			return ft::f("% (%::*)(%)"
						 , ft::typesToString<Ret>()
						 , ft::typesToString<C>()
						 , ft::typesToString<Args...>()
				);
		}
};


}; // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template <class Fun>
std::string			funTypeToString(void)
{
	return internal::funType<Fun>::toString();
}

};

#endif
