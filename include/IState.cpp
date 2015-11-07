// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IState.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 08:59:12 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 09:22:17 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "IState.hpp"
#include "StartState.hpp"
// #include "LoadingState.hpp"
// #include "ResultsState.hpp"


IState        *(*IState::createStartState)(void) = StartState::create;
// IState        *(*IState::createLoadingState)(void) = LoadingState::create;
// IState        *(*IState::createResultsState)(void) = ResultsState::create;


void		IState::globalInit(void)
{
	StartState::globalInit();
	return ;
}
