// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 09:48:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include "StartState.hpp"
#include "config_window.hpp"

// * STATICS ******************** //
IState			*StartState::create(void)
{
	return new StartState;
}

ftui::Activity	StartState::act{WIN_SIZEVI};
Tiles			StartState::tiles;

void			StartState::globalInit(void)
{
	std::ifstream	is("res/layout/start_activity.xml");

	act.inflate(is);
	// StartState::act.registerLuaCFun_global(
	// 	"getPuzzleSize", &Main::getPuzzleSize);
	StartState::tiles.init(WIN_SIZEVI);
	return ;
}

// * CTORS / DTORS ************** //
StartState::StartState()
{
	return ;
}

StartState::~StartState()
{
	return ;
}

// * MEMBER FUNCTIONS / METHODS * //
void			StartState::loop(
	std::unique_ptr<IState> &ptr, ftui::Canvas &can)
{
	(void)can;
	(void)ptr;
	return ;
}

void			StartState::_render(ftui::Canvas &can)
{
	StartState::tiles.render();
	StartState::act.render(can);
	return ;
}
