// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   XmlTokenizer.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/24 21:50:50 by juloo             #+#    #+#             //
//   Updated: 2015/11/16 14:44:05 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft_xml/XmlTokenizer.hpp"
#include "ft/utils.hpp"
#include <stdexcept>
#include <cstring>

namespace ft
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
		{NULL, &XmlTokenizer::token_mark_start, Token::MARK_START},
		{">", &XmlTokenizer::token_str, Token::MARK_END},
		{"/", &XmlTokenizer::token_str, Token::MARK_CLOSE},
		{"_-:.", &XmlTokenizer::token_chr, Token::NAME},
		{"=", &XmlTokenizer::token_str, Token::EQUAL},
		{"\"", &XmlTokenizer::token_literal_str, Token::STRING},
		{NULL, &XmlTokenizer::token_eof, Token::END_OF_FILE},
	};

	parse_spaces();
	for (auto const &def : tokens_def)
	{
		_oss.str("");
		if ((this->*def.f)(def.str))
		{
			t = def.token;
			parse_spaces();
			return (_oss.str());
		}
	}
	throw std::domain_error(ft::f("Unknown token '\033[91m%\033[0m' at "
		"\033[97mline %\033[0m",
		(char)_is.peek(), _line));
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

bool				XmlTokenizer::token_eof(char const *str)
{
	_is.peek();
	if (_is.eof())
		return (true);
	return (false);
	(void)str;
}

bool				XmlTokenizer::token_mark_start(char const *str)
{
	char				c;

	c = _is.peek();
	if (c == '<')
	{
		_is.get();
		_oss.put(c);
		c = _is.peek();
		if (c != '!')
			return (true);
		_is.get();
		if (token_str_hard("--") >= 0)
			throw std::domain_error(ft::f("Expected '<!\033[91m--\033[0m'"
				" at \033[97mline %\033[0m", _line));
		while (token_str_hard("-->") >= 0)
			continue ;
		parse_spaces();
		return (token_mark_start(NULL));
	}
	return (false);
	(void)str;
}

bool				XmlTokenizer::token_str(char const *str)
{
	char				c;
	int					tmp;

	c = _is.peek();
	if (c == str[0])
	{
		_is.get();
		if ((tmp = token_str_hard(str + 1)) >= 0)
			throw std::domain_error(ft::f("Expected '%\033[91m%\033[0m'"
				" at \033[97mline %\033[0m",
				std::string(str, tmp), str + tmp, _line));
		return (true);
	}
	return (false);
}

/*
** Return the index it stop
** or -1 on success
*/
int				XmlTokenizer::token_str_hard(char const *str)
{
	char				c;
	int					i;

	i = 0;
	while (str[i] != '\0')
	{
		_is.get(c);
		_oss.put(c);
		if (c != str[i])
			return (i);
		if (_is.eof())
			throw std::domain_error(ft::f("Unexpected \033[91mEOF\033[0m at "
				"\033[97mline %\033[0m", _line));
		i++;
	}
	return (-1);
}

bool				XmlTokenizer::token_chr(char const *str)
{
	char				c;
	bool				ok;

	ok = false;
	while (true)
	{
		c = _is.peek();
		if (!std::isalnum(c) && std::strchr(str, c) == NULL)
			break ;
		_is.get();
		_oss.put(c);
		ok = true;
	}
	return (ok);
}

bool				XmlTokenizer::token_literal_str(char const *str)
{
	char				c;
	bool				escape;

	c = _is.peek();
	if (c != str[0])
		return (false);
	escape = false;
	_is.get(c);
	while (_is.get(c))
	{
		if (!escape && c == str[0])
			return (true);
		if (!escape && c == '\\')
			escape = true;
		else
		{
			escape = false;
			_oss.put(c);
		}
	}
	throw std::domain_error(ft::f("Missing '%' at \033[97mline %\033[0m",
		str, _line));
}

};
