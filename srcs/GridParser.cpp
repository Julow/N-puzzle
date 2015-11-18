// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GridParser.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/18 17:14:03 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/18 18:11:01 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GridParser.hpp"
#include "ft/utils.hpp"
#include "ft/assert.hpp"
#include <stdexcept>

Tokenizer::token_def_s const	GridParser::gridTokens[] = {
	{{.str="#"}, Tokenizer::TOKEN_CHR1, GridParser::TOKEN_COMMENT},
	{{.str="\n"}, Tokenizer::TOKEN_CHR1, GridParser::TOKEN_ENDL},
	{{.f=&std::isspace}, Tokenizer::TOKEN_F, GridParser::TOKEN_SPACE},
	{{.f=&std::isdigit}, Tokenizer::TOKEN_F, GridParser::TOKEN_NUMBER}
};

GridParser::GridParser(std::string const &fileName) :
	_fileName(fileName),
	_in(fileName),
	_tokenizer(gridTokens, sizeof(gridTokens) / sizeof(*gridTokens)),
	_newLine(false),
	_line(1)
{
}

GridParser::~GridParser(void)
{
}

GridParser::Token	GridParser::next(void)
{
	while (_tokenizer.next(_in))
	{
		if (_newLine)
		{
			_newLine = false;
			_line++;
		}
		switch (_tokenizer.getTokenId())
		{
		case GridParser::TOKEN_COMMENT:
			_in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		case GridParser::TOKEN_ENDL:
			_newLine = true;
			return (GridParser::Token::ENDL);
		case GridParser::TOKEN_SPACE:
			break ;
		case GridParser::TOKEN_NUMBER:
			return (GridParser::Token::NUMBER);
		}
	}
	if (!_in.eof())
		error(ft::f("Unexpected token: %", _tokenizer.getToken()));
	return (GridParser::Token::END_OF_FILE);
}

std::string			GridParser::getStrToken(void) const
{
	return (_tokenizer.getToken());
}

int					GridParser::getIntToken(void) const
{
	FTASSERT(_tokenizer.getTokenId() == GridParser::TOKEN_NUMBER);
	return (std::stoi(_tokenizer.getToken()));
}

int					GridParser::getLine(void) const
{
	return (_line);
}

void				GridParser::error(std::string const &err) const
{
	throw std::runtime_error(ft::f("%:%: %", _fileName, _line, err));
}
