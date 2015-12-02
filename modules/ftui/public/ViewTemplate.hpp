// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ViewTemplate.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/01 17:59:00 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/02 14:29:33 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VIEWTEMPLATE_HPP
# define VIEWTEMPLATE_HPP

# include "ft_xml/XmlParser.hpp"

namespace ftui
{

/*
** ViewTemplate
** -
** Recursively hold a view template
*/
class	ViewTemplate
{
public:
	typedef ft::XmlParser::params_map_t				params_map_t;
	typedef std::vector<ViewTemplate*>				child_vector_t;

	ViewTemplate(ft::XmlParser &xml, bool root = true);
	virtual ~ViewTemplate(void);

	std::string const		&getName(void) const;
	params_map_t const		&getParams(void) const;
	child_vector_t const	&getChilds(void) const;

protected:
	std::string const		*_viewName;
	params_map_t			_params;
	child_vector_t			_childs;

private:
	ViewTemplate(void) = delete;
	ViewTemplate(ViewTemplate &&src) = delete;
	ViewTemplate(ViewTemplate const &src) = delete;
	ViewTemplate		&operator=(ViewTemplate &&rhs) = delete;
	ViewTemplate		&operator=(ViewTemplate const &rhs) = delete;
};

};

#endif
