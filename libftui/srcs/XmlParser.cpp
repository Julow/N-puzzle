/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/26 13:30:28 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"
#include "ft/utils.hpp"
#include <stdexcept>

#include <iostream>

namespace ftui
{

XmlParser::XmlParser(std::istream &stream) :
	_tokenizer(stream),
	_markupName(),
	_params()
{
	// ft::f(std::cout, "LOL\n");
	_tokenizer.next(_token);
	// ft::f(std::cout, "LOL\n");
}

XmlParser::~XmlParser(void)
{
}

bool							XmlParser::next(State &state)
{
	std::string			token_str;

	if (_token == XmlTokenizer::Token::MARK_START)
	{
// ft::f(std::cout, "<\n");
		// < ...
		token_str = _tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_CLOSE)
		{
// ft::f(std::cout, "</\n");
			// </ ...
			token_str = _tokenizer.next(_token);
			if (_token == XmlTokenizer::Token::NAME)
			{
// ft::f(std::cout, "</%\n", token_str);
				// </name
				_markupName = token_str;
				_tokenizer.next(_token);
				if (_token == XmlTokenizer::Token::MARK_END)
				{
// ft::f(std::cout, "</%>\n", token_str);
					// </name>
					state = State::END;
					return (true);
				}
			}
		}
		else if (_token == XmlTokenizer::Token::NAME)
		{
// ft::f(std::cout, "<%\n", token_str);
			// <name
			_markupName = token_str;
			_params.clear();
			while (true)
			{
				token_str = _tokenizer.next(_token);
				if (_token == XmlTokenizer::Token::MARK_CLOSE
					|| _token == XmlTokenizer::Token::MARK_END)
				{
					state = State::START;
					return (true);
				}
				if (_token != XmlTokenizer::Token::NAME)
					break ;

				std::string		param_name = token_str;

				_tokenizer.next(_token);
				if (_token != XmlTokenizer::Token::EQUAL)
					break ;
				token_str = _tokenizer.next(_token);
				if (_token != XmlTokenizer::Token::STRING)
					break ;
// ft::f(std::cout, " %=\"%\"\n", param_name, token_str);
				_params[param_name] = token_str;
			}
		}
	}
	else if (_token == XmlTokenizer::Token::MARK_END)
	{
// ft::f(std::cout, ">\n");
		// >
		_tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_START)
		{
// ft::f(std::cout, "> <\n");
			// > <
			return (next(state));
		}
		else if (_token == XmlTokenizer::Token::END_OF_FILE)
		{
// ft::f(std::cout, "EOF\n");
			return (false);
		}
	}
	else if (_token == XmlTokenizer::Token::MARK_CLOSE)
	{
		_tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_END)
		{
// ft::f(std::cout, "/>\n");
			// />
			state = State::END;
			return (true);
		}
	}
	throw std::domain_error(ft::f("Unexpected token '%' (%) at line %",
		token_str, (int)_token, _tokenizer.getLine()));
}

std::string const				&XmlParser::getMarkupName(void) const
{
	return (_markupName);
}

XmlParser::params_map_t const	&XmlParser::getParams(void) const
{
	return (_params);
}

};
