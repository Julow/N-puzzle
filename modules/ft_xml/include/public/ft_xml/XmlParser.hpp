/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:32 by jaguillo          #+#    #+#             */
//   Updated: 2015/11/16 14:43:44 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLPARSER_HPP
# define XMLPARSER_HPP

# include <istream>
# include <unordered_map>
# include <stack>

# include "ft_xml/XmlTokenizer.hpp"

namespace ft
{

/*
** Simple XML parser
** -
** throw a domain_error on error
** -
** State::START match	<name [param="value" ...] [>]
** State::END match		</name>		or		/>
*/
class	XmlParser
{
public:
	/*
	** Tokens
	*/
	enum class	State
	{
		ERROR,
		END_OF_FILE,
		START,
		END,
	};

	typedef std::unordered_map<std::string, std::string>	params_map_t;

	XmlParser(std::istream &stream);
	virtual ~XmlParser(void);

	/*
	** Parse
	** -
	** 'state' is set to the corresponding state
	*/
	bool				next(State &state);

	/*
	** Return current markup name
	*/
	std::string const	&getMarkupName(void) const;

	/*
	** Return current markup params
	*/
	params_map_t const	&getParams(void) const;

protected:

	XmlTokenizer			_tokenizer;

	XmlTokenizer::Token		_token;

	params_map_t			_params;

	std::stack<std::string>	_marks;

private:
	XmlParser(void) = delete;
	XmlParser(XmlParser const &src) = delete;
	XmlParser			&operator=(XmlParser const &rhs) = delete;
};

};

#endif
