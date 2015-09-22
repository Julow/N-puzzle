/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IViewHolder.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:56:47 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 15:20:43 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IVIEWHOLDER_HPP
# define IVIEWHOLDER_HPP

# include "Vec.hpp"

class	IViewHolder
{
public:
	virtual ~IViewHolder(void){}

	virtual Vec2<int>		getPos(void) = 0;
	virtual Vec2<int>		getSize(void) = 0;

protected:
private:
};

#endif
