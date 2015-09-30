/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextView.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 18:22:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTVIEW_HPP
# define TEXTVIEW_HPP

# include "libftui.hpp"

namespace ftui
{

/*
** TextView
** -
** Represent a text
** Automatically request enougth size onMeasure
** -
** TODO: Implement TextView
*/
class	TextView
{
public:
	TextView(void);
	virtual ~TextView(void);

protected:

private:
	TextView(TextView const &src);
	TextView			&operator=(TextView const &rhs);
};

};

#endif
