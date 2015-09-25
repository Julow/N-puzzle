/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextView.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 12:01:15 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTVIEW_HPP
# define TEXTVIEW_HPP

# include "libftui.h"

namespace ftui
{

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