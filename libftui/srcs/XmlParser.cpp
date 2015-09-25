/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/25 16:15:09 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "XmlParser.hpp"

namespace ftui
{

XmlParser::XmlParser(std::istream &stream) :
	_tokenizer(stream),
	_lastState(END),
	_markupName(),
	_params()
{
	_tokenizer.next(_token);
}

XmlParser::~XmlParser(void)
{
}

void				XmlParser::next(State &state)
{
	std::string const	&token_str;

	if (_lastToken == XmlTokenizer::Token::MARK_START)
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
					return ;
				}
			}
		}
		else if (_token == XmlTokenizer::Token::NAME)
		{
			// <name
			_markupName = token_str;
			token_str = _tokenizer.next(_token);
			while (_token == XmlTokenizer::Token::NAME)
			{
				std::string		param_name = token_str;

				_tokenizer.next(_token);
			}
		}
	}
	else if (_lastToken == XmlTokenizer::Token::MARK_END)
	{
		// >
		_tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_START)
		{
			// > <
			next(state);
			return ;
		}
	}
	else if (_lastToken == XmlTokenizer::Token::MARK_CLOSE)
	{
		_tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_END)
		{
			// />
			state = END;
			return ;
		}
	}
	throw domain_error("Unexpected token '%' at line %", token_str, _tokenizer.getLine());
}

std::string const	&XmlParser::getMarkupName(void) const
{
	return (_markupName);
}

params_map_t const	&XmlParser::getParams(void) const
{
	return (_params);
}

};
