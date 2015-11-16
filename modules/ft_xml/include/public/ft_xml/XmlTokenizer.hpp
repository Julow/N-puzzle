/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlTokenizer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 21:39:37 by juloo             #+#    #+#             */
//   Updated: 2015/11/16 14:27:04 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLTOKENIZER_HPP
# define XMLTOKENIZER_HPP

# include <sstream>
# include <string>

namespace ft
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
		STRING,
		END_OF_FILE
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
		bool		(XmlTokenizer::*f)(char const *);
		Token		token;
	};

	void				parse_spaces(void);

	bool				token_eof(char const *str);
	bool				token_str(char const *str);
	int					token_str_hard(char const *str);
	bool				token_chr(char const *str);
	bool				token_mark_start(char const *str);
	bool				token_literal_str(char const *str);

private:
	XmlTokenizer(void) = delete;
	XmlTokenizer(XmlTokenizer const &src) = delete;
	XmlTokenizer		&operator=(XmlTokenizer const &rhs) = delete;
};

};

#endif
