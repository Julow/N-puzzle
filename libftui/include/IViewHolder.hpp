/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IViewHolder.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:56:47 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/24 07:12:34 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef IVIEWHOLDER_HPP
# define IVIEWHOLDER_HPP

# include "Vec.hpp"

class	IViewHolder
{
public:
	virtual ~IViewHolder(void){}

	virtual Vec2<int>		getPos(void) const = 0;
	virtual Vec2<int>		getSize(void) const = 0;

protected:
private:
};

#endif
