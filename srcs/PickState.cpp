// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PickState.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 16:37:32 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 10:58:54 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>

#include "PickState.hpp"
#include "config_window.hpp"
#include "ftlua/ftlua.hpp"

using PS = PickState;

/*
** ************************************************************************** **
** CONSTRUCTION
*/

PS::Bundle		*PS::loadBundle(Main &main) /*static*/
{
	IBundle *const		ib = main.popBundle("PickState");
	PS::Bundle *const	b = dynamic_cast<PS::Bundle*>(ib);

	if (b == nullptr)
	{
		FTASSERT(ib == nullptr, "Dynamic cast failed");
		return new PS::Bundle(main);
	}
	return b;
}

PS::PickState(Main &main, OCamlBinding &ocaml)
	: _main(main)
	, _ocaml(ocaml)
	, _b(loadBundle(main))
	, _launchSolvingState(false)
{
	lua_State	*l = this->_b->act.getLuaState();
	int			ret;
// TTAG push0
	ret = lua_getglobal(l, "PickState");
	FTASSERT(ret == LUA_TTABLE);

	lua_pushinteger(l, 0);
	lua_pushlightuserdata(l, this);
	lua_settable(l, -3);

	lua_pop(l, 1);
	return ;
}

PS::~PickState()
{
	this->_main.pushBundle("PickState", this->_b);
	return ;
}

/*
** ************************************************************************** **
** ISTATE LEGACY
*/

void            PS::loop(std::unique_ptr<IState> &ptr, ftui::Canvas &can)
{
	(void)ptr;
	this->_b->tiles.render();
	this->_b->act.render(can);
	return ;
}

ftui::Activity  &PS::getActivity(void)
{
	return this->_b->act;
}

/*
** ************************************************************************** **
** LIBFTUI INTERACTIONS
*/

int				PS::useDefaultGridG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 0>(l, &PS::useDefaultGrid);
}
void			PS::useDefaultGrid(void)
{ _main.grid = Grid::def; }


int				PS::useRandomGridG(lua_State *l) /*static*/
{
	return ftlua::handle<3, 0>(l, &PS::useRandomGrid);
}
void			PS::useRandomGrid(int w, bool solvable)
{
	_main.grid = _ocaml.generate_grid(w, solvable);
	return ;
}


int				PS::setAlgorithmIdG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &PS::setAlgorithmId);
}
void			PS::setAlgorithmId(int id)
{ _main.algorithmId = id; }


int				PS::setHeuristicIdG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &PS::setHeuristicId);
}
void			PS::setHeuristicId(int id)
{ _main.heuristicId = id; }


int				PS::setCostG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &PS::setCost);
}
void			PS::setCost(int cost)
{ _main.cost = cost; }


int				PS::tagForSolvingG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 0>(l, &PS::tagForSolving);
}
void			PS::tagForSolving(void)
{ _launchSolvingState = true; }

/*
** ************************************************************************** **
** BUNDLE IMPLEMENTATION
*/

static Tiles	make_tiles(void)
{
	Tiles		t;

	t.init(WIN_SIZEVI);
	return t;
}

PS::Bundle::Bundle(Main &main)
	: tiles(make_tiles())
	, act(WIN_SIZEVI)
	, grids()
{
	ftui::Activity		&act = this->act;
	auto				pushFun =
		[&](std::string const &fname, lua_CFunction f)
		{ act.registerLuaCFun_table("PickState", fname, f); };
	std::ifstream		is("res/layout/start_activity.xml");

	act.inflate(is);
	main.loadSharedScripts(act);
	luaL_dostring(act.getLuaState(), "PickState = {}");
	pushFun("useDefaultGrid", &useDefaultGridG);
	pushFun("useRandomGrid", &useRandomGridG);
	pushFun("setAlgorithmId", &setAlgorithmIdG);
	pushFun("setHeuristicId", &setHeuristicIdG);
	pushFun("setCost", &setCostG);
	pushFun("tagForSolving", &tagForSolvingG);
	for (auto const &fileName : main.files)
		this->grids.emplace_back(fileName);
}

PS::Bundle::~Bundle()
{
}
