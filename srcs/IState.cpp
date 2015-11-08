// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IState.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 08:59:12 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 10:19:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "IState.hpp"
#include "StartState.hpp"
// #include "LoadingState.hpp"
// #include "ResultsState.hpp"

IState        *(*IState::createStartState)(
	ftui::Canvas &can, OCamlBinding &ocaml) = StartState::create;
// IState        *(*IState::createLoadingState)(void) = LoadingState::create;
// IState        *(*IState::createResultsState)(void) = ResultsState::create;


void		IState::globalInit(void)
{
	StartState::globalInit();
	return ;
}
