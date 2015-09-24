/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 19:22:41 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"

namespace ftui
{

XmlParser::XmlParser(std::istream &stream)
	: _stream(stream), _markupName(""), _params(), _token(TOKEN_EOF), _line(0)
{
}

XmlParser::~XmlParser(void)
{
}

std::string const	&XmlParser::getMarkupName(void) const
{
	return (_markupName);
}

XmlParser::params_map_t const	&XmlParser::getParams(void) const
{
	return (_params);
}

bool				XmlParser::next(Token &token)
{
	bool const			status = this->parseMarkup();

	token = _token;
	return (status);
}

/*
** Parse a markup
*/
bool				XmlParser::parseMarkup(void)
{
	char				c;

	c = _stream.peek();
	if (c == '/')
	{
		if (!this->parseEqu("/>"))
			throw std::invalid_argument("Expected '/>' at line %d");
			// throw std::invalid_argument("Expected '/>' at line %d" % _line);
		_token = MARKUP_END;
		return (true);
	}
	if (!this->parseMarkupStart() || !this->parseSpace())
		return (false);
	_markupName.clear();
	if (!this->parseMarkupName())
		return (false);
	_params.clear();
	if (!this->parseParams() || !this->parseSpace())
		return (false);
	c = _stream.peek();
	if (c == '>')
		_stream.get();
	_token = MARKUP_START;
	return (true);
}

/*
** Parse spaces, comments and the first '<'
*/
bool				XmlParser::parseMarkupStart(void)
{
	char				c;

	if (!this->parseSpace() || !_stream.get(c))
		return (false);
	if (c != '<')
		throw std::invalid_argument("Invalid character '%c' at line %d");
		// throw std::invalid_argument("Invalid character '%c' at line %d" % (c, _line));
	if (!this->parseSpace())
		return (false);
	c = _stream.peek();
	if (c == '!')
	{
		if (!this->parseEqu("--"))
			throw std::invalid_argument("Expected '--' at line %d");
			// throw std::invalid_argument("Expected '--' at line %d" % _line);
		this->parseTo("-->");
		return (this->parseMarkupStart());
	}
	if (c == '/')
		return (this->parseMarkupEnd());
	return (true);
}

/*
** Parse '/name>'
*/
bool				XmlParser::parseMarkupEnd(void)
{
	char				c;

	if (!_stream.get(c) || c != '/')
		throw std::invalid_argument("Expected '</' at line %d");
		// throw std::invalid_argument("Expected '</' at line %d" % _line);
	if (!this->parseSpace() || !this->parseMarkupName() || !this->parseSpace())
		return (false);
	if (!_stream.get(c) || c != '>')
		throw std::invalid_argument("Expected '>' at line %d");
		// throw std::invalid_argument("Expected '>' at line %d" % _line);
	_token = MARKUP_END;
	return (true);
}

/*
** Parse a markup name
** fill _markupName
*/
bool				XmlParser::parseMarkupName(void)
{
	char				c;

	while (_stream.get(c))
	{
		if (!std::isalnum(c) && c != '_' && c != '-')
			return (true);
		_markupName += c;
	}
	return (false);
}

/*
** Parse a markup param
** put it in _params
*/
bool				XmlParser::parseParams(void)
{
	std::string			param_name;
	std::string			param_def;

	while (true)
	{
		if (!this->parseSpace() || !this->parseParamName(param_name))
			return (false);
		if (param_name.length() == 0)
			return (true);
		if (!this->parseSpace() || !this->parseParamDef(param_def))
			return (false);
		if (_params.count(param_name))
			throw std::invalid_argument("Redefined param '%s' at line %d");
			// throw std::invalid_argument("Redefined param '%s' at line %d" % (param_name, _line));
		_params.insert(std::make_pair(param_name, param_def));
		param_name.clear();
		param_def.clear();
	}
}

bool				XmlParser::parseParamName(std::string &out)
{
	char				c;

	while (_stream.get(c))
	{
		if (!std::isalnum(c) && c != '_' && c != '-')
			return (true);
		out += c;
	}
	return (false);
}

bool				XmlParser::parseParamDef(std::string &out)
{
	char				c;
	bool				escaped;

	c = _stream.peek();
	if (c != '=')
		throw std::invalid_argument("Expected '=' at line %d");
		// throw std::invalid_argument("Expected '=' at line %d" % _line);
	_stream.get();
	if (!this->parseSpace())
		return (false);
	c = _stream.peek();
	if (c != '"')
		return (true);
	escaped = false;
	while (_stream.get(c))
	{
		if (!escaped && c == '"')
			return (true);
		escaped = (c == '\\') ? true : false;
		out += c;
	}
	return (false);
}

/*
** Utils
*/

/*
** Parse {0,} spaces
*/
bool				XmlParser::parseSpace(void)
{
	char				c;

	while (true)
	{
		c = _stream.peek();
		if (c == EOF)
			return (false);
		if (c == '\n')
			_line++;
		else if (!std::isspace(c))
			break ;
		_stream.get();
	}
	return (true);
}

/*
** Return true if equ is next char sequence
** also parse it
*/
bool				XmlParser::parseEqu(char const *equ)
{
	int					i;
	char				c;

	i = 0;
	if (*equ == '\0')
		return (true);
	while (_stream.get(c))
		if (c == equ[i])
		{
			if (equ[++i] == '\0')
				return (true);
		}
		else
			break ;
	return (false);
}

/*
** Skip everything until parseEqu(to)
*/
bool				XmlParser::parseTo(char const *to)
{
	int					i;
	char				c;

	i = 0;
	if (*to == '\0')
		return (true);
	while (_stream.get(c))
		if (c == to[i])
		{
			if (to[++i] == '\0')
				return (true);
		}
		else
			i = 0;
	return (false);
}

};
