// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/09 13:18:03 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include "StartState.hpp"
#include "config_window.hpp"

// * STATICS ******************** //
IState			*StartState::create(ftui::Canvas &can, OCamlBinding &ocaml)
{
	return new StartState(can, ocaml);
}

ftui::Activity	StartState::act{WIN_SIZEVI};
Tiles			StartState::tiles;

void			StartState::globalInit(void)
{
	std::ifstream	is("res/layout/start_activity.xml");

	act.inflate(is);
	act.registerLuaCFun_global("generate_grid", &OCamlBinding::generate_gridG);
	// StartState::act.registerLuaCFun_global(
	// 	"getPuzzleSize", &Main::getPuzzleSize);
	StartState::tiles.init(WIN_SIZEVI);
	return ;
}

// * CTORS / DTORS ************** //
StartState::StartState(ftui::Canvas &can, OCamlBinding &ocaml)
{
	(void)can;
	(void)ocaml;
	ocaml.setListener(this);
	return ;
}

StartState::~StartState()
{
	return ;
}

// * MEMBER FUNCTIONS / METHODS * //
ftui::Activity	&StartState::getActivity(void)
{
	return StartState::act;
}

// * IState ********************* //
void			StartState::loop(
	std::unique_ptr<IState> &ptr, ftui::Canvas &can, OCamlBinding &ocaml)
{
	(void)can;
	(void)ptr;
	(void)ocaml;
	this->_render(can);
	return ;
}

void			StartState::_render(ftui::Canvas &can)
{
	StartState::tiles.render();
	StartState::act.render(can);
	return ;
}
// * ISolverListener ************ //
void			StartState::onSuccess(report_s rep)
{
	(void)rep;
	return ;
}
void			StartState::onProgress(progress_s prog){
	(void)prog;
	return ;
}

void			StartState::onFail(std::string const &str)
{
	(void)str;
	return ;
}
