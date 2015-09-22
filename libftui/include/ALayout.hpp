/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/22 13:13:00 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALAYOUT_HPP
# define ALAYOUT_HPP

class	ALayout
{
public:
	ALayout(void);
	virtual ~ALayout(void);

protected:

private:
	ALayout(ALayout const &src);
	ALayout			&operator=(ALayout const &rhs);
};

#endif
