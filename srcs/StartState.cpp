// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 16:54:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include <array>
#include "StartState.hpp"
#include "config_window.hpp"
#include "ftlua/ftlua.hpp"
#include "ftlua_extend.hpp"

using SS = StartState;

/* STATIC ATTRIBUTES  *********** */
ftui::Activity	SS::act{WIN_SIZEVI};
Tiles			SS::tiles;

#define MATRIX33I(...) std::array<int*, 3>{{__VA_ARGS__}}.data()
#define LINE3I(...) std::array<int, 3>{{__VA_ARGS__}}.data()

Grid const		SS::defaultGrid =
	Grid(MATRIX33I(LINE3I(0, 1, 2), LINE3I(3, 4, 5), LINE3I(6, 7, 8)), 3);

Grid			*SS::filegrid = nullptr;

/* CONSTRUCTION ***************** */
IState			*SS::create(ftui::Canvas &can, OCamlBinding &ocaml)
{
	return new SS(can, ocaml);
}

void			SS::globalInit(void)
{
	std::ifstream	is("res/layout/start_activity.xml");

	act.inflate(is);
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
	act.registerLuaCFun_global("launchSolving", &launchSolvingG);
	SS::tiles.init(WIN_SIZEVI);
	return ;
}

SS		*SS::_instance = nullptr;
SS		*SS::instance(void)
{ return (SS::_instance); }

// TODO:  loadFileGrid(std::string const &fileName);

SS::StartState(ftui::Canvas &can, OCamlBinding &ocaml)
	: _grid(defaultGrid), _algorithmId(0), _heuristicId(0), _cost(1)
	, _launchSolving(false)
{
	(void)can;
	(void)ocaml;
	ocaml.setListener(this);
	SS::_instance = this;
	return ;
}

SS::~StartState()
{
	return ;
}

/* ISTATE LEGACY **************** */
void			SS::loop(
	std::unique_ptr<IState> &ptr, ftui::Canvas &can, OCamlBinding &ocaml)
{
	(void)can;
	(void)ptr;
	(void)ocaml;
	SS::tiles.render();
	SS::act.render(can);
	return ;
}

ftui::Activity	&SS::getActivity(void)
{
	return SS::act;
}

/* ISOLVERLISTENER LEGACY ******* */
void			SS::onSuccess(report_s rep)
{
	FTASSERT(false, "Should not be reached");
	(void)rep;
	return ;
}
void			SS::onProgress(progress_s prog)
{
	FTASSERT(false, "Should not be reached");
	(void)prog;
	return ;
}

void			SS::onFail(std::string const &str)
{
	FTASSERT(false, "Should not be reached");
	(void)str;
	return ;
}

/* LIBFTUI INTERACTIONS ********* */
/* GETTERS ************ */
int				SS::getAlgorithms(lua_State *l)
{
	StartState *const	ss = SS::instance();
//TODO do
	(void)ss;
	(void)l;
	return 1;
}

int				SS::getHeuristics(lua_State *l)
{
	StartState *const	ss = SS::instance();
//TODO do
	(void)ss;
	(void)l;
	return 1;
}


int				SS::getGridG(lua_State *l)
{
	StartState *const	ss = SS::instance();

	FTASSERT(lua_gettop(l) == 0); //TODO: FTLUAASSERT
	ftlua::pushgrid(l, ss->getGrid());
	return 1;
}
Grid const		&SS::getGrid(void) const
{ return _grid; }


int				SS::getAlgorithmIdG(lua_State *l)
{
	return ftlua::handle<0, 1>(l, SS::instance(), &SS::getAlgorithmId);
}
int				SS::getAlgorithmId(void) const
{ return _algorithmId; }


int				SS::getHeuristicIdG(lua_State *l)
{
	return ftlua::handle<0, 1>(l, SS::instance(), &SS::getHeuristicId);
}
int				SS::getHeuristicId(void) const
{ return _heuristicId; }


int				SS::getCostG(lua_State *l)
{
	return ftlua::handle<0, 1>(l, SS::instance(), &SS::getCost);
}
int				SS::getCost(void) const
{ return _cost; }


/* SETTERS ************ */
int				SS::useFileGridG(lua_State *l)
{
	return ftlua::handle<0, 0>(l, SS::instance(), &SS::useFileGrid);
}


void			SS::useFileGrid(void)
{
	// TODO useFileGrid
	return ;
}


int				SS::useDefaultGridG(lua_State *l)
{
	return ftlua::handle<0, 0>(l, SS::instance(), &SS::useDefaultGrid);
}
void			SS::useDefaultGrid(void)
{ _grid = SS::defaultGrid; }


int				SS::useRandomGridG(lua_State *l)
{
	return ftlua::handle<2, 0>(l, SS::instance(), &SS::useRandomGrid);
}
void			SS::useRandomGrid(int w, bool solvable)
{
	OCamlBinding *const	ocaml = OCamlBinding::instance();

	_grid = ocaml->generate_grid(w, solvable);
	return ;
}


int				SS::setAlgorithmIdG(lua_State *l)
{
	return ftlua::handle<1, 0>(l, SS::instance(), &SS::setAlgorithmId);
}
void			SS::setAlgorithmId(int id)
{ _algorithmId = id; }


int				SS::setHeuristicIdG(lua_State *l)
{
	return ftlua::handle<1, 0>(l, SS::instance(), &SS::setHeuristicId);
}
void			SS::setHeuristicId(int id)
{ _heuristicId = id; }


int				SS::setCostG(lua_State *l)
{
	return ftlua::handle<1, 0>(l, SS::instance(), &SS::setCost);
}
void			SS::setCost(int cost)
{ _cost = cost; }


int				SS::launchSolvingG(lua_State *l)
{
	return ftlua::handle<0, 0>(l, SS::instance(), &SS::launchSolving);
}
void			SS::launchSolving(void)
{ _launchSolving = true; }
