// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IState.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 18:06:30 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:54:22 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISTATE_HPP
# define ISTATE_HPP

# include <memory>

# include "ftui/Activity.hpp"

class IState
{
public:

	/* CONSTRUCTION ***************** */
	virtual ~IState(){}

	virtual void			loop(
		std::unique_ptr<IState> &ptr
		, ftui::ACanvas &can) = 0;
	virtual ftui::Activity	&getActivity(void) = 0;

};

#endif /* ******************************************************** ISTATE_HPP */
