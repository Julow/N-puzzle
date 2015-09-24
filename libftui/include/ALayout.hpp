/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/24 07:13:25 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef ALAYOUT_HPP
# define ALAYOUT_HPP

# include "AView.hpp"

class	ALayout : public AView
{
public:
	// * CTORS / DTORS ************** //
	ALayout(void);
	virtual ~ALayout(void);

protected:

private:
	ALayout(ALayout const &src);
	ALayout			&operator=(ALayout const &rhs);
};

#endif
