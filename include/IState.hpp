// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IState.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 08:56:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 09:35:12 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISTATE_HPP
# define ISTATE_HPP

//# include <string>
# include <memory>
# include "ftui/Canvas.hpp"
//# include <iostream>
//# include <stdexcept>

class IState
{
public:
	IState(IState const &src) = delete;
	IState						&operator=(IState const &rhs) = delete;
	IState() {}

	virtual void		loop(
		std::unique_ptr<IState> &ptr, ftui::Canvas &can) = 0;

	static void			globalInit(void);

protected:
	static IState        *(*createStartState)(void);
	static IState        *(*createLoadingState)(void);
	static IState        *(*createResultsState)(void);

private:
};

#endif // ******************************************************** ISTATE_HPP //
