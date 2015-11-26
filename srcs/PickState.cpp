// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PickState.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 16:37:32 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/26 19:12:13 by ngoguey          ###   ########.fr       //
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
	int			ret;
// TTAG push0
	ret = lua_getglobal(l, "PickState");
	FTASSERT(ret == LUA_TTABLE);

	lua_pushinteger(l, 0);
	lua_pushlightuserdata(l, this);
	lua_settable(l, -3);

	lua_pop(l, 1);

	this->_b->act.fireEvent("Bordel", 42, std::string("caca"));


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
	_main.grid = this->_b->grids[i]; //todo error check
	this->_b->act.fireEvent("onDisplayedGridChanged", i);
	return ;
}

int				PS::deleteGridG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 0>(l, &PS::deleteGrid);
}
void			PS::deleteGrid(int i)
{
	auto				&grids = this->_b->grids;

	FTASSERT(i >= 0 && i < (int)grids.size());
	if (grids.size() > 1)
	{
		grids.erase(grids.begin() + i);
		this->_b->act.fireEvent("onPuzzlesLoaded", this->_b->extractGridNames());
		// this->selectGrid(std::min(i, (int)grids.size() - 1));
	}
	return ;
}




int				PS::useDefaultGridG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 0>(l, &PS::useDefaultGrid);
}
void			PS::useDefaultGrid(void)
{ _main.grid = Grid::def; }


int				PS::pushRandomGridG(lua_State *l) /*static*/
{
	return ftlua::handle<3, 0>(l, &PS::pushRandomGrid);
}
void			PS::pushRandomGrid(int w, bool solvable)
{
	static int	count = 0;
	int const	newIndex = this->_b->grids.size();

	this->_b->grids.push_back(_ocaml.generate_grid(w, solvable));
	this->_b->grids[newIndex].setName(ft::f("Generated #%", count++));
	this->_b->act.fireEvent("onPuzzlesLoaded", this->_b->extractGridNames());
	this->selectGrid(newIndex);
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

PS::Bundle::Bundle(Main &main, OCamlBinding &ocaml)
	: tiles(make_tiles())
	, act(WIN_SIZEVI)
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
	pushFun("useDefaultGrid", &useDefaultGridG);
	pushFun("selectGrid", &selectGridG);
	pushFun("deleteGrid", &deleteGridG);
	pushFun("pushRandomGrid", &pushRandomGridG);
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
	act.fireEvent("onPuzzlesLoaded", this->extractGridNames());
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
