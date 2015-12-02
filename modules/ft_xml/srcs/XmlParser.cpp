// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   XmlParser.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:13:45 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/02 11:55:14 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft_xml/XmlParser.hpp"
#include "ft/utils.hpp"
#include <stdexcept>

namespace ft
{

XmlParser::XmlParser(std::istream &stream) :
	_tokenizer(stream),
	_params(),
	_marks()
{
	_tokenizer.next(_token);
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
		token_str = _tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_CLOSE)
		{
// ft::f(std::cout, "</\n");
			token_str = _tokenizer.next(_token);
			if (_token == XmlTokenizer::Token::NAME)
			{
// ft::f(std::cout, "</%\n", token_str);
				if (_marks.size() == 0)
					throw std::domain_error(ft::f("Unexpected "
						"'\033[91m</%>\033[0m' at \033[97mline %\033[0m",
						token_str, _tokenizer.getLine()));
				if (_marks.top() != token_str)
					throw std::domain_error(ft::f("Expected '</%>' instead of"
						" '</\033[91m%\033[0m>' at \033[97mline %\033[0m",
						_marks.top(), token_str, _tokenizer.getLine()));
				_marks.pop();
				_tokenizer.next(_token);
				if (_token == XmlTokenizer::Token::MARK_END)
				{
// ft::f(std::cout, "</%>\n", token_str);
					state = State::END;
					return (true);
				}
			}
		}
		else if (_token == XmlTokenizer::Token::NAME)
		{
// ft::f(std::cout, "<%\n", token_str);
			_marks.push(token_str);
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
				_params.emplace_back(param_name, token_str);
			}
		}
	}
	else if (_token == XmlTokenizer::Token::MARK_END)
	{
// ft::f(std::cout, ">\n");
		_tokenizer.next(_token);
		if (_token == XmlTokenizer::Token::MARK_START)
		{
// ft::f(std::cout, "> <\n");
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
			_marks.pop();
			state = State::END;
			return (true);
		}
	}
	throw std::domain_error(ft::f("Unexpected token '\033[91m%\033[0m' "
		"(%) at \033[97mline %\033[0m",
		token_str, (int)_token, _tokenizer.getLine()));
}

std::string const				&XmlParser::getMarkupName(void) const
{
	return (_marks.top());
}

XmlParser::params_map_t const	&XmlParser::getParams(void) const
{
	return (_params);
}

};
