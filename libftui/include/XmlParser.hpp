/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:32 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 21:38:48 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef XMLPARSER_HPP
// #ifndef XMLPARSER_HPP
# define XMLPARSER_HPP

# include "libftui.h"

# include <istream>
# include <unordered_map>

/*
** Simple XML parser
** -
** MARKUP		= MARKUP_START '<' SPACE* MARKUP_NAME PARAMS SPACE* MARKUP_END
** MARKUP_START	= SPACE MARKUP_START | "<!--" .* "-->" | '<'
** SPACE		= ' ' | '\n' | '\t'
** MARKUP_NAME	= \w
** PARAMS		= SPACE+ PARAM_NAME SPACE* '=' SPACE* PARAM_DEF? PARAMS?
** PARAM_NAME	= \w
** PARAM_DEF	= '"' ( '\' '"' | !'"' )* '"'
** MARKUP_END	= '>' MARKUP* MARKUP_START '/' SPACE* ${STACKED_NAME} SPACE* '>' | "/>"
*/

namespace ftui
{

class	XmlParser
{
public:
	/*
	** Tokens
	*/
	enum	Token
	{
		TOKEN_ERROR,
		TOKEN_EOF,
		MARKUP_START,
		MARKUP_END
	};

	typedef std::unordered_map<std::string, std::string>	params_map_t;

	XmlParser(std::istream &stream);
	virtual ~XmlParser(void);

	/*
	** Return false on error of at the EOF
	** true otherwise
	** -
	** 'token' is set to the corresponding token
	*/
	bool				next(Token &token);

	/*
	** Return current markup name
	*/
	std::string const	&getMarkupName(void) const;

	/*
	** Return current markup params
	*/
	params_map_t const	&getParams(void) const;

protected:

	std::istream		&_stream;

	std::string			_markupName;
	params_map_t		_params;

	Token				_token;
	int					_line;

	bool				parseMarkup(void);
	bool				parseMarkupStart(void);
	bool				parseMarkupEnd(void);
	bool				parseMarkupName(void);
	bool				parseParams(void);
	bool				parseParamName(std::string &out);
	bool				parseParamDef(std::string &out);
	bool				parseSpace(void);
	bool				parseEqu(char const *equ);
	bool				parseTo(char const *to);

private:
	XmlParser(void) = delete;
	XmlParser(XmlParser const &src) = delete;
	XmlParser			&operator=(XmlParser const &rhs) = delete;
};

};

#endif
