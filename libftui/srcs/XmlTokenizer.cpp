/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlTokenizer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 21:50:50 by juloo             #+#    #+#             */
/*   Updated: 2015/10/02 10:25:30 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui/XmlTokenizer.hpp"
#include "ft/utils.hpp"
#include <stdexcept>
#include <cstring>

namespace ftui
{

XmlTokenizer::XmlTokenizer(std::istream &stream)
	: _is(stream), _oss(), _line(1)
{
}

XmlTokenizer::~XmlTokenizer(void)
{
}

std::string const	XmlTokenizer::next(Token &t)
{
	static tokenDef_s	tokens_def[] = {
		{"<", &XmlTokenizer::token_char, Token::MARK_START},
		{">", &XmlTokenizer::token_char, Token::MARK_END},
		{"/", &XmlTokenizer::token_char, Token::MARK_CLOSE},
		{"_-:.", &XmlTokenizer::token_name, Token::NAME},
		{"=", &XmlTokenizer::token_char, Token::EQUAL},
		{"\"", &XmlTokenizer::token_str, Token::STRING},
		{NULL, &XmlTokenizer::token_eof, Token::END_OF_FILE},
	};

	parse_spaces();
	for (auto const &def : tokens_def)
	{
		_oss.str("");
		if ((this->*def.f)(def))
		{
			t = def.token;
			parse_spaces();
			return (_oss.str());
		}
	}
	throw std::domain_error(ft::f("Unknown token '%' at line %", (char)_is.peek(), _line));
}

int					XmlTokenizer::getLine(void) const
{
	return (_line);
}

void				XmlTokenizer::parse_spaces(void)
{
	char				c;

	while (true)
	{
		c = _is.peek();
		if (c == '\n')
			_line++;
		else if (!std::isspace(c))
			break ;
		_is.get();
	}
}

bool				XmlTokenizer::token_eof(tokenDef_s const &def)
{
	if (_is.peek() == EOF)
		return (true);
	return (false);
	(void)def;
}

bool				XmlTokenizer::token_char(tokenDef_s const &def)
{
	char				c;

	c = _is.peek();
	if (c == def.str[0])
	{
		_is.get();
		_oss.put(c);
		return (true);
	}
	return (false);
}

bool				XmlTokenizer::token_name(tokenDef_s const &def)
{
	char				c;
	bool				ok;

	ok = false;
	while (true)
	{
		c = _is.peek();
		if (!std::isalnum(c) && std::strchr(def.str, c) == NULL)
			break ;
		_is.get();
		_oss.put(c);
		ok = true;
	}
	return (ok);
}

bool				XmlTokenizer::token_str(tokenDef_s const &def)
{
	char				c;
	bool				escape;

	c = _is.peek();
	if (c != def.str[0])
		return (false);
	escape = false;
	_is.get(c);
	while (_is.get(c))
	{
		if (!escape && c == def.str[0])
			return (true);
		if (!escape && c == '\\')
			escape = true;
		else
		{
			escape = false;
			_oss.put(c);
		}
	}
	throw std::domain_error(ft::f("Missing '%' at line %", def.str, _line));
}

};
