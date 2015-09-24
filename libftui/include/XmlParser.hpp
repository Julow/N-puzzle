/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:32 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 12:01:18 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLPARSER_HPP
# define XMLPARSER_HPP

# include "libftui.h"

# include <istream>
# include <unordered_map>

namespace ftui
{

class	XmlParser
{
public:
	enum	Token
	{
		MARKUP_START,
		MARKUP_END
	};

	XmlParser(std::istream &stream);
	virtual ~XmlParser(void);

	bool				next(void);
	Token				getToken(void) const { return (_token); }

	std::string const	&getMarkupName(void) const { return (_markupName); }

	std::unordered_map<std::string, std::string> const	&getParams(void) const;

protected:

	std::istream		&_stream;

	Token											_token;
	std::string										_markupName;
	std::unordered_map<std::string, std::string>	_params;

private:
	XmlParser(void) = delete;
	XmlParser(XmlParser const &src) = delete;
	XmlParser			&operator=(XmlParser const &rhs) = delete;
};

};

#endif
