/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlTokenizer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 21:39:37 by juloo             #+#    #+#             */
/*   Updated: 2015/09/25 18:08:13 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLTOKENIZER_HPP
# define XMLTOKENIZER_HPP

# include "libftui.h"

# include <sstream>
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

	std::string const	next(Token &t);

	int					getLine(void) const;

protected:

	std::istream		&_is;
	std::ostringstream	_oss;
	int					_line;

	struct		tokenDef_s
	{
		char const	*str;
		bool		(XmlTokenizer::*f)(tokenDef_s const &);
		Token		token;
	};

	void				parse_spaces(void);

	bool				token_char(tokenDef_s const &def);
	bool				token_name(tokenDef_s const &def);
	bool				token_str(tokenDef_s const &def);

private:
	XmlTokenizer(void) = delete;
	XmlTokenizer(XmlTokenizer const &src) = delete;
	XmlTokenizer		&operator=(XmlTokenizer const &rhs) = delete;
};

};

#endif
