/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlTokenizer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 21:50:50 by juloo             #+#    #+#             */
/*   Updated: 2015/09/24 23:17:03 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlTokenizer.hpp"

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

	i = -1;
	while (++i < G_ARRAY_LEN(g_tokens))
	{
		_oss.clear();
		if (this->*(g_tokens[i].f)(g_tokens + i))
		{
			t = g_tokens[i].token;
			return (_oss.str());
		}
	}
	// throw invalid_token;
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
	// throw "Invalid string"
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
