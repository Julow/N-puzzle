// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PickState.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 16:37:32 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/28 17:58:35 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <algorithm>

#include "PickState.hpp"
#include "config_window.hpp"

using PS = PickState;

/*
** ************************************************************************** **
** CONSTRUCTION
*/

PS::Bundle		*PS::loadBundle(Main &main, OCamlBinding &ocaml) /*static*/
{
	IBundle *const		ib = main.popBundle("PickState");
	PS::Bundle *const	b = dynamic_cast<PS::Bundle*>(ib);

	if (b == nullptr)
	{
		FTASSERT(ib == nullptr, "Dynamic cast failed");
		return new PS::Bundle(main, ocaml);
	}
	return b;
}

PS::PickState(Main &main, OCamlBinding &ocaml)
	: _main(main)
	, _ocaml(ocaml)
	, _b(loadBundle(main, ocaml))
	, _launchSolvingState(false)
{
	lua_State	*l = this->_b->act.getLuaState();
	auto		*bun = this->_b;
	auto		&act = bun->act;
	int			ret;
// TODO: ftlua
	ret = lua_getglobal(l, "PickState");
	FTASSERT(ret == LUA_TTABLE);

	lua_pushinteger(l, 0);
	lua_pushlightuserdata(l, this);
	lua_settable(l, -3);

	lua_pop(l, 1);
	act.fireEvent("GRID_LIST_UPDATE", bun->extractGridNames()
						, bun->grids.size());
	act.fireEvent("SELECTED_GRID_CHANGED", bun->selectedId);

	act.fireEvent("Bordel", 42, std::string("caca"));


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

void            PS::loop(std::unique_ptr<IState> &ptr, ftui::ACanvas &can)
{
	(void)ptr;
	this->_b->tiles.render();
	this->_b->act.render(can);
	if (this->_launchSolvingState)
	{
		ft::f(std::cout, "Algo % Heu % Cost % Grid %:\n%\n"
			  , _main.algorithmId
			  , _main.heuristicId
			  , _main.cost
			  , _b->selectedId
			  , _main.grid
			);

		throw std::runtime_error("OK");
	}
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

int				PS::selectGridG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &PS::selectGrid);
}
void			PS::selectGrid(int i)
{
	auto		*bun = this->_b;
	auto		&grids = bun->grids;

	FTASSERT(i >= 0 && i < (int)grids.size());
	_main.grid = grids[i];
	bun->selectedId = i;
	bun->act.fireEvent("SELECTED_GRID_CHANGED", i);
	return ;
}

int				PS::deleteGridG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &PS::deleteGrid);
}
void			PS::deleteGrid(int i)
{
	auto		*bun = this->_b;
	auto		&grids = bun->grids;

	FTASSERT(i >= 0 && i < (int)grids.size());
	if (grids.size() > 1)
	{
		grids.erase(grids.begin() + i);
		if (i == bun->selectedId)
		{
			bun->selectedId = std::min(i, (int)grids.size() - 1);
			_main.grid = bun->grids[bun->selectedId];
			bun->act.fireEvent(
				"GRID_LIST_UPDATE", bun->extractGridNames(), grids.size());
			bun->act.fireEvent("SELECTED_GRID_CHANGED", bun->selectedId);
		}
		else if (bun->selectedId > i)
		{
			bun->selectedId -= 1;
			bun->act.fireEvent(
				"GRID_LIST_UPDATE", bun->extractGridNames(), grids.size());
		}
		else
			bun->act.fireEvent(
				"GRID_LIST_UPDATE", bun->extractGridNames(), grids.size());
	}
	return ;
}


int				PS::pushRandomGridG(lua_State *l) /*static*/
{
	return ftlua::handle<3, 0>(l, &PS::pushRandomGrid);
}
void			PS::pushRandomGrid(int w, bool solvable)
{
	static int	count = 0;
	auto		*bun = this->_b;
	auto		&grids = bun->grids;
	int const	newIndex = grids.size();

	grids.push_back(_ocaml.generate_grid(w, solvable));
	grids[newIndex].setName(ft::f("Generated #%", count++));
	_main.grid = bun->grids[newIndex];
	bun->selectedId = newIndex;
	bun->act.fireEvent("GRID_LIST_UPDATE", bun->extractGridNames(), grids.size());
	bun->act.fireEvent("SELECTED_GRID_CHANGED", newIndex);
	return ;
}


int				PS::getNumGridsG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &PS::getNumGrids);
}
int				PS::getNumGrids(void)
{
	return this->_b->grids.size();
}

int				PS::getGridNameG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 1>(l, &PS::getGridName);
}
std::string const	&PS::getGridName(int i)
{
	auto		*bun = this->_b;
	auto		&grids = bun->grids;

	FTASSERT(i >= 0 && i < (int)grids.size());
	return grids[i].getName();
}

int				PS::getGridG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 1>(l, &PS::getGridName);
}
Grid const		&PS::getGrid(int i)
{
	auto		*bun = this->_b;
	auto		&grids = bun->grids;

	FTASSERT(i >= 0 && i < (int)grids.size());
	return grids[i];
}

int				PS::getMainGridIdG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &PS::getMainGridId);
}
int				PS::getMainGridId(void)
{
	return this->_b->selectedId;
}












int				PS::useDefaultGridG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 0>(l, &PS::useDefaultGrid);
}
void			PS::useDefaultGrid(void)
{ _main.grid = Grid::def; }
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

PS::Bundle::Bundle(Main &main, OCamlBinding &ocaml)
	: tiles(make_tiles())
	, act(WIN_SIZEVI)
	, selectedId(0)
	, grids({Grid::def})
{
	ftui::Activity			&act = this->act;
	auto					pushFun =
		[&](std::string const &fname, lua_CFunction f)
		{ act.registerLuaCFun_table("PickState", fname, f); };
	std::ifstream			is("res/layout/pick_state.xml");
	Grid					*gr;

	act.inflate(is);
	main.loadSharedScripts(act);
	luaL_dostring(act.getLuaState(), "PickState = {}");
	pushFun("selectGrid", &selectGridG);
	pushFun("deleteGrid", &deleteGridG);

	pushFun("pushRandomGrid", &pushRandomGridG);

	pushFun("getNumGrids", &getNumGridsG);
	pushFun("getGridName", &getGridNameG);
	pushFun("getGrid", &getGridG);
	pushFun("getMainGridId", &getMainGridIdG);

	pushFun("useDefaultGrid", &useDefaultGridG);
	pushFun("setAlgorithmId", &setAlgorithmIdG);
	pushFun("setHeuristicId", &setHeuristicIdG);
	pushFun("setCost", &setCostG);
	pushFun("tagForSolving", &tagForSolvingG);
	for (auto const &fileName : main.files)
	{
		this->grids.emplace_back(fileName);
		gr = &this->grids[this->grids.size() - 1];
		gr->convert(ocaml.transposition_toabstract(gr->getSize()));
	}
	// this->act.fireEvent("GRID_LIST_UPDATE", this->extractGridNames()
	// 					, this->grids.size());
	this->act.fireEvent("ON_GAME_LOADED");
	return ;
}

PS::Bundle::~Bundle()
{
}

// std::vector<std::string>	PS::Bundle::extractGridNames(void)
std::vector<std::string const*>	PS::Bundle::extractGridNames(void)
{
	std::vector<std::string const*>		ret;

	for (auto const &it : this->grids)
		ret.push_back(&it.getName());
	return ret;
}
