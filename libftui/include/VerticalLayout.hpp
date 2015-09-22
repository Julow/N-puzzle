/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:43 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 13:12:45 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTICALLAYOUT_HPP
# define VERTICALLAYOUT_HPP

class	VerticalLayout
{
public:
	VerticalLayout(void);
	virtual ~VerticalLayout(void);

protected:

private:
	VerticalLayout(VerticalLayout const &src);
	VerticalLayout			&operator=(VerticalLayout const &rhs);
};

#endif
