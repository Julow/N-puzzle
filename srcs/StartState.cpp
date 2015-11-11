// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 15:35:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include <array>
#include "StartState.hpp"
#include "config_window.hpp"

/* STATIC ATTRIBUTES  *********** */
ftui::Activity	StartState::act{WIN_SIZEVI};
Tiles			StartState::tiles;

#define MATRIX33I(...) std::array<int*, 3>{{__VA_ARGS__}}.data()
#define LINE3I(...) std::array<int, 3>{{__VA_ARGS__}}.data()

Grid const		StartState::defaultGrid =
	Grid(MATRIX33I(LINE3I(0, 1, 2), LINE3I(3, 4, 5), LINE3I(6, 7, 8)), 3);

Grid			*StartState::filegrid = nullptr;

/* CONSTRUCTION ***************** */
IState			*StartState::create(ftui::Canvas &can, OCamlBinding &ocaml)
{
	return new StartState(can, ocaml);
}

void			StartState::globalInit(void)
{
	std::ifstream	is("res/layout/start_activity.xml");

	act.inflate(is);
	act.registerLuaCFun_global("generate_grid", &OCamlBinding::generate_gridG);
	act.registerLuaCFun_global("getAlgorithms", &getAlgorithms);
	act.registerLuaCFun_global("getHeuristics", &getHeuristics);
	act.registerLuaCFun_global("getGrid", &getGridG);
	act.registerLuaCFun_global("getAlgorithmId", &getAlgorithmIdG);
	act.registerLuaCFun_global("getHeuristicId", &getHeuristicIdG);
	act.registerLuaCFun_global("getCost", &getCostG);
	act.registerLuaCFun_global("useFileGrid", &useFileGridG);
	act.registerLuaCFun_global("useDefaultGrid", &useDefaultGridG);
	act.registerLuaCFun_global("useRandomGrid", &useRandomGridG);
	act.registerLuaCFun_global("setAlgorithmId", &setAlgorithmIdG);
	act.registerLuaCFun_global("setHeuristicId", &setHeuristicIdG);
	act.registerLuaCFun_global("setCost", &setCostG);
	StartState::tiles.init(WIN_SIZEVI);
	return ;
}

StartState		*StartState::_instance = nullptr;
StartState		*StartState::instance(void)
{ return (StartState::_instance); }

// TODO:  loadFileGrid(std::string const &fileName);

StartState::StartState(ftui::Canvas &can, OCamlBinding &ocaml)
	: _grid(defaultGrid), _algorithmId(0), _heuristicId(0), _cost(1)
{
	(void)can;
	(void)ocaml;
	ocaml.setListener(this);
	StartState::_instance = this;
	return ;
}

StartState::~StartState()
{
	return ;
}

/* ISTATE LEGACY **************** */
void			StartState::loop(
	std::unique_ptr<IState> &ptr, ftui::Canvas &can, OCamlBinding &ocaml)
{
	(void)can;
	(void)ptr;
	(void)ocaml;
	StartState::tiles.render();
	StartState::act.render(can);
	return ;
}

ftui::Activity	&StartState::getActivity(void)
{
	return StartState::act;
}

/* ISOLVERLISTENER LEGACY ******* */
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

/* LIBFTUI INTERACTIONS ********* */
/* GETTERS ************ */

int				StartState::getAlgorithms(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 1;
}

int				StartState::getHeuristics(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 1;
}


int				StartState::getGridG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 1;
}

Grid const		&StartState::getGrid(void) const
{
	return _grid;
}


int				StartState::getAlgorithmIdG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 1;
}

int				StartState::getAlgorithmId(void) const
{
	return _algorithmId;
}


int				StartState::getHeuristicIdG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 1;
}

int				StartState::getHeuristicId(void) const
{
	return _heuristicId;
}


int				StartState::getCostG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 1;
}

int				StartState::getCost(void) const
{
	return _cost;
}


/* SETTERS ************ */
int				StartState::useFileGridG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 0;
}

void			StartState::useFileGrid(void)
{
	return ;
}


int				StartState::useDefaultGridG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 0;
}

void			StartState::useDefaultGrid(void)
{
	return ;
}


int				StartState::useRandomGridG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 0;
}

void			StartState::useRandomGrid(void)
{
	return ;
}


int				StartState::setAlgorithmIdG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 0;
}

void			StartState::setAlgorithmId(int id)
{
	_algorithmId = id;
	return ;
}


int				StartState::setHeuristicIdG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 0;
}

void			StartState::setHeuristicId(int id)
{
	_heuristicId = id;
	return ;
}


int				StartState::setCostG(lua_State *l)
{
	StartState *const	ss = StartState::instance();

	return 0;
}

void			StartState::setCost(int cost)
{
	_cost = cost;
	return ;
}
