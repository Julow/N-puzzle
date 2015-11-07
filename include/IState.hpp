// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IState.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 08:56:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 10:30:41 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISTATE_HPP
# define ISTATE_HPP

//# include <string>
# include <memory>
# include "ftui/Canvas.hpp"
# include "OCamlBinding.hpp"
//# include <iostream>
//# include <stdexcept>

class IState
{
public:
	IState(IState const &src) = delete;
	IState						&operator=(IState const &rhs) = delete;
	IState() {}

	virtual void				loop(
		std::unique_ptr<IState> &ptr
		, ftui::Canvas &can
		, OCamlBinding &ocaml) = 0;
	virtual ftui::Activity		&getActivity(void) = 0;

	static void					globalInit(void);

protected:
	static IState        *(*createStartState)
		(ftui::Canvas &can, OCamlBinding &ocaml);
	static IState        *(*createLoadingState)
		(ftui::Canvas &can, OCamlBinding &ocaml);
	static IState        *(*createResultsState)
		(ftui::Canvas &can, OCamlBinding &ocaml);

private:
};

#endif // ******************************************************** ISTATE_HPP //
