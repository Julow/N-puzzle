// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PickState.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 16:37:32 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 18:25:13 by ngoguey          ###   ########.fr       //
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

Tiles const				*PS::tilesInstance(void)
{
	static Tiles			*t = nullptr;

	if (t == nullptr)
	{
		t = new Tiles;
		t->init(WIN_SIZEVI);
	}
	return t;
}

ftui::Activity			*PS::activityInstance(void)
{
	static ftui::Activity	*act = nullptr;
	auto					pushFun =
		[&](std::string const &fname, lua_CFunction f)
		{ act->registerLuaCFun_table("PickState", fname, f); };

	if (act == nullptr)
	{
		act = new ftui::Activity(WIN_SIZEVI);
		std::ifstream		is("res/layout/start_activity.xml");
		act->inflate(is);
		Main::loadSharedScripts(*act);
		luaL_dostring(act->getLuaState(), "PickState = {}");
		pushFun("useDefaultGrid", &useDefaultGridG);
		pushFun("useRandomGrid", &useRandomGridG);
		pushFun("setAlgorithmId", &setAlgorithmIdG);
		pushFun("setHeuristicId", &setHeuristicIdG);
		pushFun("setCost", &setCostG);
		pushFun("tagForSolving", &tagForSolvingG);
	}
	return act;
}

PS::PickState(Main &main, OCamlBinding &ocaml)
	:
	_main(main), _ocaml(ocaml), _launchSolvingState(false)
{
	lua_State	*l = PS::activityInstance()->getLuaState();
	int			ret;

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
	return ;
}

/*
** ************************************************************************** **
** CONSTRUCTION
*/

void            PS::loop(std::unique_ptr<IState> &ptr, ftui::Canvas &can)
{
	(void)ptr;
	PS::tilesInstance()->render();
	PS::activityInstance()->render(can);
	return ;
}

ftui::Activity  &PS::getActivity(void)
{
	return *PS::activityInstance();
}

/*
** ************************************************************************** **
** LIBFTUI INTERACTIONS
*/

int				PS::useDefaultGridG(lua_State *l)
{
	return ftlua::handle<1, 0>(l, &PS::useDefaultGrid);
}
void			PS::useDefaultGrid(void)
{ _main.grid = DEFGRID; }


int				PS::useRandomGridG(lua_State *l)
{
	return ftlua::handle<3, 0>(l, &PS::useRandomGrid);
}
void			PS::useRandomGrid(int w, bool solvable)
{
	_main.grid = _ocaml.generate_grid(w, solvable);
	return ;
}


int				PS::setAlgorithmIdG(lua_State *l)
{
	return ftlua::handle<2, 0>(l, &PS::setAlgorithmId);
}
void			PS::setAlgorithmId(int id)
{ _main.algorithmId = id; }


int				PS::setHeuristicIdG(lua_State *l)
{
	return ftlua::handle<2, 0>(l, &PS::setHeuristicId);
}
void			PS::setHeuristicId(int id)
{ _main.heuristicId = id; }


int				PS::setCostG(lua_State *l)
{
	return ftlua::handle<2, 0>(l, &PS::setCost);
}
void			PS::setCost(int cost)
{ _main.cost = cost; }


int				PS::tagForSolvingG(lua_State *l)
{
	return ftlua::handle<1, 0>(l, &PS::tagForSolving);
}
void			PS::tagForSolving(void)
{ _launchSolvingState = true; }
