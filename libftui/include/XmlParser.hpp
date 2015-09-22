/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XmlParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:32 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 13:12:33 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMLPARSER_HPP
# define XMLPARSER_HPP

class	XmlParser
{
public:
	XmlParser(void);
	virtual ~XmlParser(void);

protected:

private:
	XmlParser(XmlParser const &src);
	XmlParser			&operator=(XmlParser const &rhs);
};

#endif
