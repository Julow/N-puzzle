// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AState.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/11 19:32:04 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 20:09:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <array>

#include "ftlua/ftlua.hpp"
#include "ftlua_extend.hpp"

#include "AState.hpp"
#include "StartState.hpp"
// #include "LoadingState.hpp"
// #include "ResultsState.hpp"

using AS = AState;

/* STATIC ATTRIBUTES	*********** */
#define MATRIX33I(...) std::array<int*, 3>{{__VA_ARGS__}}.data()
#define LINE3I(...) std::array<int, 3>{{__VA_ARGS__}}.data()

Grid const		AS::defaultGrid =
	Grid(MATRIX33I(LINE3I(0, 1, 2), LINE3I(3, 4, 5), LINE3I(6, 7, 8)), 3);

Grid			*AS::filegrid = nullptr;

/* CONSTRUCTION ***************** */
AS		*AS::_instance = nullptr;
AS		*AS::instance(void)
{ return (AS::_instance); }

// TODO:	loadFileGrid(std::string const &fileName);

void		AS::globalInit(void)
{
	StartState::globalInit();
	// LoadingState::globalInit();
	// ResultsState::globalInit();
	return ;
}

void		AS::loadGlobalScripts(ftui::Activity &act)
{
	act.registerLuaCFun_global("getAlgorithms", &AS::getAlgorithms);
	act.registerLuaCFun_global("getHeuristics", &AS::getHeuristics);
	act.registerLuaCFun_global("getGrid", &AS::getGridG);
	act.registerLuaCFun_global("getAlgorithmId", &AS::getAlgorithmIdG);
	act.registerLuaCFun_global("getHeuristicId", &AS::getHeuristicIdG);
	act.registerLuaCFun_global("getCost", &AS::getCostG);
	return ;
}

AS::AState()
	: _grid(defaultGrid), _algorithmId(0), _heuristicId(0), _cost(1)
{

}

AS::~AState()
{
	return ;
}

/* LIBFTUI INTERACTIONS ********* */
/* GETTERS ************ */
int			AS::getAlgorithms(lua_State *l)
{
	AS *const	as = AS::instance();
	//TODO do
	FTASSERT(lua_gettop(l) == 0); //TODO: FTLUAAASERT
	(void)as;
	(void)l;
	return 1;
}

int			AS::getHeuristics(lua_State *l)
{
	AS *const	as = AS::instance();
	//TODO do
	FTASSERT(lua_gettop(l) == 0); //TODO: FTLUAAASERT
	(void)as;
	(void)l;
	return 1;
}

int			AS::getTranspToReal(lua_State *l)
{
	AS *const	as = AS::instance();
	//TODO do
	FTASSERT(lua_gettop(l) == 0); //TODO: FTLUAAASERT
	(void)as;
	(void)l;
	return 1;
}


int			AS::getGridG(lua_State *l)
{
	AS *const	as = AS::instance();

	FTASSERT(lua_gettop(l) == 0); //TODO: FTLUAAASERT
	ftlua::pushgrid(l, as->getGrid());
	return 1;
}
Grid const	&AS::getGrid(void) const
{ return _grid; }


int			AS::getAlgorithmIdG(lua_State *l)
{
	return ftlua::handle<0, 1>(l, AS::instance(), &AS::getAlgorithmId);
}
int			AS::getAlgorithmId(void) const
{ return _algorithmId; }


int			AS::getHeuristicIdG(lua_State *l)
{
	return ftlua::handle<0, 1>(l, AS::instance(), &AS::getHeuristicId);
}
int			AS::getHeuristicId(void) const
{ return _heuristicId; }


int			AS::getCostG(lua_State *l)
{
	return ftlua::handle<0, 1>(l, AS::instance(), &AS::getCost);
}
int			AS::getCost(void) const
{ return _cost; }
