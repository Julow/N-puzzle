/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RelativeLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/02 10:25:17 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RELATIVELAYOUT_HPP
# define RELATIVELAYOUT_HPP

# include "ftui/libftui.hpp"

namespace ftui
{

/*
** RelativeLayout
** -
** Childs:
** * Are placed relatively to a point of the layout
** * Cannot go outside layout's bounds (shrinked)
** * Cannot set position or size
** -
** TODO: Implement RelativeLayout
*/
class	RelativeLayout
{
public:
	RelativeLayout(void);
	virtual ~RelativeLayout(void);

protected:

private:
	RelativeLayout(RelativeLayout const &src);
	RelativeLayout			&operator=(RelativeLayout const &rhs);
};

};

#endif
