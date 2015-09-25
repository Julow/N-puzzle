/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/25 19:03:31 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"
#include "ft/utils.hpp"
#include <exception>

#include <iostream>

namespace ftui
{

XmlParser::XmlParser(std::istream &stream) :
	_tokenizer(stream),
	_markupName(),
	_params()
{
	ft::f(std::cout, "LOL\n");
	_tokenizer.next(_token);
	ft::f(std::cout, "LOL\n");
}

XmlParser::~XmlParser(void)
{
}

bool							XmlParser::next(State &state)
{
	std::string			token_str;

	if (_token == XmlTokenizer::Token::MARK_START)
	{
		// < ...
		token_str = _tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_CLOSE)
		{
			// </ ...
			token_str = _tokenizer.next(_token);
			if (_token == XmlTokenizer::Token::NAME)
			{
				// </name
				_markupName = token_str;
				_tokenizer.next(_token);
				if (_token == XmlTokenizer::Token::MARK_END)
				{
					// </name>
					state = State::END;
					return (true);
				}
			}
		}
		else if (_token == XmlTokenizer::Token::NAME)
		{
			// <name
			_markupName = token_str;
			token_str = _tokenizer.next(_token);
			while (true)
			{
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
			}
		}
	}
	else if (_token == XmlTokenizer::Token::MARK_END)
	{
		// >
		_tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_START)
		{
			// > <
			return (next(state));
		}
	}
	else if (_token == XmlTokenizer::Token::MARK_CLOSE)
	{
		_tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_END)
		{
			// />
			state = State::END;
			return (true);
		}
	}
	throw std::domain_error(ft::f("Unexpected token '%' at line %", token_str, _tokenizer.getLine()));
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
