/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbsoluteLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:51 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 13:12:51 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSOLUTELAYOUT_HPP
# define ABSOLUTELAYOUT_HPP

class	AbsoluteLayout
{
public:
	AbsoluteLayout(void);
	virtual ~AbsoluteLayout(void);

protected:

private:
	AbsoluteLayout(AbsoluteLayout const &src);
	AbsoluteLayout			&operator=(AbsoluteLayout const &rhs);
};

#endif
