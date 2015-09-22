/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ViewFactory.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:54 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 13:12:54 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWFACTORY_HPP
# define VIEWFACTORY_HPP

class	ViewFactory
{
public:
	ViewFactory(void);
	virtual ~ViewFactory(void);

protected:

private:
	ViewFactory(ViewFactory const &src);
	ViewFactory			&operator=(ViewFactory const &rhs);
};

#endif
