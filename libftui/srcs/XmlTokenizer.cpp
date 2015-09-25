/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlTokenizer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 21:50:50 by juloo             #+#    #+#             */
/*   Updated: 2015/09/25 14:58:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlTokenizer.hpp"
#include "ft/utils.hpp"
#include <exception>

XmlTokenizer::XmlTokenizer(std::istream &stream)
	: _is(stream), _oss(), _line(0)
{
}

XmlTokenizer::~XmlTokenizer(void)
{
}

std::string const	&XmlTokenizer::next(Token &t)
{
	int					i;

	parse_spaces();
	i = -1;
	while (++i < G_ARRAY_LEN(g_tokens))
	{
		_oss.clear();
		if (this->*(g_tokens[i].f)(g_tokens + i))
		{
			t = g_tokens[i].token;
			parse_spaces();
			return (_oss.str());
		}
	}
	throw domain_error(ftutils::f("Unknown token '%' at line %", _oss.peek(), _line));
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
		else if (!isspace(c))
			break ;
		_is.get();
	}
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

	ok = false,
	while (true)
	{
		c = _is.peek();
		if (!std::isspace(c) && std::strchr("_-:.", c) == NULL)
			break ;
		_is.get();
		_oss.put(c);
		ok = true;
	}
	return (ok);
	(void)def;
}

bool				XmlTokenizer::token_str(tokenDef_s const &def)
{
	char				c;
	bool				escape;

	c = _is.peek();
	if (c != '"')
		return (false);
	escape = false;
	while (_is.get(c))
	{
		if (!escape && c == '"')
			return (true);
		if (!escape && c == '\\')
			escape = true;
		else
		{
			escape = false;
			_oss.put(c);
		}
	}
	throw domain_error(ftutils::f("Missing '\"' at line %", _line));
	(void)def;
}

static tokenDef_s	g_tokens[] = {
	{"<", &XmlTokenizer::token_char, MARK_START},
	{">", &XmlTokenizer::token_char, MARK_END},
	{"/", &XmlTokenizer::token_char, MARK_CLOSE},
	{NULL, &XmlTokenizer::token_name, NAME},
	{"=", &XmlTokenizer::token_char, EQUAL},
	{NULL, &XmlTokenizer::token_str, STRING},
	{NULL, NULL, 0},
};
