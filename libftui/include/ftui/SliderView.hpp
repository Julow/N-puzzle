/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SliderView.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/02 10:25:17 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLIDERVIEW_HPP
# define SLIDERVIEW_HPP

# include "ftui/libftui.hpp"

namespace ftui
{

/*
** SliderView
** -
** Represent a slider that the cursor can be moved by the user
** -
** TODO: Implement SliderView
*/
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
