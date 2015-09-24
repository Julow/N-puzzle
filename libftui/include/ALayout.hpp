/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALayout.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:13:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 11:41:38 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALAYOUT_HPP
# define ALAYOUT_HPP

# include "libftui.h"
# include "AView.hpp"
# include <iterator>

namespace ftui
{

class	ALayout : public AView
{
public:
	virtual ~ALayout(void);

	virtual void	addView(AView *view);

	// virtual AView	*popView();

protected:

	ALayout(XmlParser const &xml);

private:
	ALayout(void) = delete;
	ALayout(ALayout const &src) = delete;
	ALayout			&operator=(ALayout const &rhs) = delete;
};

};

#endif
