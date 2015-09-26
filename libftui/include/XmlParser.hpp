/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:32 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/26 13:56:20 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLPARSER_HPP
# define XMLPARSER_HPP

# include "libftui.h"

# include <istream>
# include <unordered_map>
# include <stack>

# include "XmlTokenizer.hpp"

/*
** Simple XML parser
** -
** throw a domain_error on error
*/

namespace ftui
{

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
