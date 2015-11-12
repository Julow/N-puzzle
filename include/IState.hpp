// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IState.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 18:06:30 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 18:20:28 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISTATE_HPP
# define ISTATE_HPP

// # include <iostream>
# include <memory>

# include "ftui/Canvas.hpp"
# include "ftui/Activity.hpp"

class IState
{
public:

	/* CONSTRUCTION ***************** */
	// IState();
	virtual ~IState(){}

	virtual void			loop(
		std::unique_ptr<IState> &ptr
		, ftui::Canvas &can) = 0;
	virtual ftui::Activity	&getActivity(void) = 0;


protected:
private:
};

#endif /* ******************************************************** ISTATE_HPP */
