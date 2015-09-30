/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACanvas.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:16:40 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 18:04:47 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACANVAS_HPP
# define ACANVAS_HPP

# include "libftui.hpp"

namespace ftui
{

class	ACanvas
{
public:
	ACanvas(void);
	virtual ~ACanvas(void);

protected:

private:
	ACanvas(ACanvas const &src);
	ACanvas			&operator=(ACanvas const &rhs);
};

};

#endif
