/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SliderView.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 18:06:48 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLIDERVIEW_HPP
# define SLIDERVIEW_HPP

# include "libftui.hpp"

namespace ftui
{

class	SliderView
{
public:
	SliderView(void);
	virtual ~SliderView(void);

protected:

private:
	SliderView(SliderView const &src);
	SliderView			&operator=(SliderView const &rhs);
};

};

#endif
