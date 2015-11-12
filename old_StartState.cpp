// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 14:10:49 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>

#include "StartState.hpp"
#include "config_window.hpp"

#include "ftlua/ftlua.hpp"
#include "ftlua_extend.hpp"

using AS = AState;
using SS = StartState;

/* STATIC ATTRIBUTES	*********** */
ftui::Activity	SS::act{WIN_SIZEVI};
Tiles			SS::tiles;

/* CONSTRUCTION ***************** */
AState			*SS::create(ftui::Canvas &can, OCamlBinding &ocaml)
{
	return new SS(can, ocaml);
}

void			SS::globalInit(void)
{
	std::ifstream	is("res/layout/start_activity.xml");

	act.inflate(is);
	AS::loadGlobalScripts(act);
	act.registerLuaCFun_global("useFileGrid", &useFileGridG);
	act.registerLuaCFun_global("useDefaultGrid", &useDefaultGridG);
	act.registerLuaCFun_global("useRandomGrid", &useRandomGridG);
	act.registerLuaCFun_global("setAlgorithmId", &setAlgorithmIdG);
	act.registerLuaCFun_global("setHeuristicId", &setHeuristicIdG);
	act.registerLuaCFun_global("setCost", &setCostG);
	act.registerLuaCFun_global("tagForSolving", &tagForSolvingG);
	SS::tiles.init(WIN_SIZEVI);
	return ;
}

StartState		*SS::instance(void)
{
	StartState *const	ins = dynamic_cast<StartState*>(SS::_instance);

	FTASSERT(ins != nullptr);
	return ins;
}

SS::StartState(ftui::Canvas &can, OCamlBinding &ocaml)
	: AState()
	, _tagSolve(false)
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
	std::unique_ptr<AState> &ptr, ftui::Canvas &can, OCamlBinding &ocaml)
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


int				SS::tagForSolvingG(lua_State *l)
{
	return ftlua::handle<0, 0>(l, SS::instance(), &SS::tagForSolving);
}
void			SS::tagForSolving(void)
{ _tagSolve = true; }
