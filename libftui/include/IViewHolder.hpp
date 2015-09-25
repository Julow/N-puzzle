/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IViewHolder.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 08:37:05 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 14:26:35 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef IVIEWHOLDER_HPP
# define IVIEWHOLDER_HPP

# include "libftui.h"

# include "Vec.hpp"

namespace ftui
{

class	IViewHolder
{
public:
	virtual ~IViewHolder(void) {}

	virtual ALayout			*getParent(void) = 0;
	virtual ALayout const	*getParent(void) const = 0;

	virtual AView			*getView(void) = 0;
	virtual AView const		*getView(void) const = 0;

	virtual Vec2<int>		getPos(void) const = 0;
	virtual Vec2<int>		getSize(void) const = 0;

	virtual void			setParam(std::string const &k
									 , std::string const &v) = 0;
};

};

#endif
