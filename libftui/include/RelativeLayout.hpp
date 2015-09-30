/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RelativeLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 18:06:42 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RELATIVELAYOUT_HPP
# define RELATIVELAYOUT_HPP

# include "libftui.hpp"

namespace ftui
{

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
