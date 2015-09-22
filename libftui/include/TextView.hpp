/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextView.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 13:13:32 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTVIEW_HPP
# define TEXTVIEW_HPP

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

#endif
