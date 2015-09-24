/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlTokenizer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 21:39:37 by juloo             #+#    #+#             */
/*   Updated: 2015/09/24 23:16:17 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLTOKENIZER_HPP
# define XMLTOKENIZER_HPP

# include "libftui.h"

# include <iostream>
# include <string>

namespace ftui
{

class	XmlTokenizer
{
public:
	enum class	Token
	{
		MARK_START,
		MARK_END,
		MARK_CLOSE,
		NAME,
		EQUAL,
		STRING
	};

	XmlTokenizer(std::istream &stream);
	virtual ~XmlTokenizer(void);

	std::string const	&next(Token &t);

protected:

	std::istream		&_is;
	std::ostringstream	&_oss;
	int					_line;

	struct		tokenDef_s
	{
		char const	*str;
		bool		(*f)(tokenDef_s const &);
		Token		token;
	};

	bool				token_char(tokenDef_s const &def);
	bool				token_name(tokenDef_s const &def);
	bool				token_str(tokenDef_s const &def);

	static tokenDef_s	g_tokens[];

private:
	XmlTokenizer(void) = delete;
	XmlTokenizer(XmlTokenizer const &src) = delete;
	XmlTokenizer		&operator=(XmlTokenizer const &rhs) = delete;
};

// template<typename ... Args>
// std::string		std::string::operator%(std::string const &str, ...)
// {
// }

template<typename HEAD, typename ... TAIL>
void			f_util(std::ostringstream &out, HEAD&& arg, TAIL&& ...tail)
{
	out << arg;
	f_util(out, std::forward<Tail>(tail)...);
}

template<typename ... ARGS>
std::string		f(ARGS ...args)
{
	ostringstream	out();

	f_util(out, std::forward(args)...);
	return (out.str());
}

};

#endif
