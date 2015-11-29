// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolvingState.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/29 14:06:13 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/29 15:47:26 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread>

#include "SolvingState.hpp"
#include "config_window.hpp"

using SS = SolvingState;

/*
** ************************************************************************** **
** CONSTRUCTION
*/

SS::Bundle		*SS::loadBundle(Main &main, OCamlBinding &ocaml) /*static*/
{
	IBundle *const		ib = main.popBundle("SolvingState");
	SS::Bundle *const	b = dynamic_cast<SS::Bundle*>(ib);

	if (b == nullptr)
	{
		FTASSERT(ib == nullptr, "Dynamic cast failed");
		return new SS::Bundle(main, ocaml);
	}
	return b;
}

// static void		launch(OCamlBinding *ocaml)
static void		launch(OCamlBinding *ocaml, Grid const *gr)
{
	std::cout << "from thread" << std::endl;
	ocaml->solve(*gr);
}

SS::SolvingState(Main &main, OCamlBinding &ocaml)
	: _main(main)
	, _ocaml(ocaml)
	, _b(loadBundle(main, ocaml))
	, _abortSolvingState(false)
{
	lua_State	*l = this->_b->act.getLuaState();
	auto		*bun = this->_b;
	auto		&act = bun->act;
	int			ret;
// TODO: ftlua
	ret = lua_getglobal(l, "SolvingState");
	FTASSERT(ret == LUA_TTABLE);

	lua_pushinteger(l, 0);
	lua_pushlightuserdata(l, this);
	lua_settable(l, -3);

	lua_pop(l, 1);
	// act.fireEvent("GRID_LIST_UPDATE", bun->extractGridNames()
	// 					, bun->grids.size());
	// act.fireEvent("SELECTED_GRID_CHANGED", bun->selectedId);

	// act.fireEvent("Bordel", 42, std::string("caca"));

	std::thread		th (launch, &ocaml, &main.grid);

	th.join();
	// std::thread		th (launch, ocaml, main.grid);
	// ocaml.solve(main.grid);

	return ;
}

SS::~SolvingState()
{
	this->_main.pushBundle("SolvingState", this->_b);
	return ;
}

/*
** ************************************************************************** **
** ISTATE LEGACY
*/

void            SS::loop(std::unique_ptr<IState> &ptr, ftui::ACanvas &can)
{
	(void)ptr;
	this->_b->tiles.render();
	this->_b->act.render(can);
	// if (this->_launchSolvingState)
	// {
	// 	ft::f(std::cout, "Algo % Heu % Cost % Grid %:\n%\n"
	// 		  , _main.algorithmId
	// 		  , _main.heuristicId
	// 		  , _main.cost
	// 		  , _b->selectedId
	// 		  , _main.grid
	// 		);

	// 	throw std::runtime_error("OK");
	// }
	return ;
}

ftui::Activity  &SS::getActivity(void)
{
	return this->_b->act;
}

/*
** ************************************************************************** **
** LIBFTUI INTERACTIONS
*/

// int				SS::tagForSolvingG(lua_State *l) /*static*/
// {
// 	return ftlua::handle<1, 0>(l, &SS::tagForSolving);
// }
// void			SS::tagForSolving(void)
// { _launchSolvingState = true; }

/*
** ************************************************************************** **
** BUNDLE IMPLEMENTATION
*/

static Tiles	make_tiles(void)
{
	Tiles		t;

	t.init(WIN_SIZEVI
		   , /*ft::Vec2<int> const triangleSize =*/ ft::Vec2<int>(95, 95)
		   , /*int const pointRandomRadius =*/ 30
		   , /*float const percentGray =*/ 0.33f
		   , /*ft::Vec3<int> const gray =*/ ft::Vec3<int>(181, 120, 129)
		   , /*ft::Vec3<int> const pink =*/ ft::Vec3<int>(230, 46, 77)
		   , /*ft::Vec3<int> const deltaPink =*/ ft::Vec3<int>(50, 10, 77));
	return t;
}

SS::Bundle::Bundle(Main &main, OCamlBinding &ocaml)
	: tiles(make_tiles())
	, act(WIN_SIZEVI)
{
	ftui::Activity			&act = this->act;
	auto					pushFun =
		[&](std::string const &fname, lua_CFunction f)
		{ act.registerLuaCFun_table("SolvingState", fname, f); };
	std::ifstream			is("res/layout/solving_state.xml");
	Grid					*gr;


	act.inflate(is);
	main.loadSharedScripts(act);
	luaL_dostring(act.getLuaState()
				  , "SolvingState = {}; GridColor = 0x0000FF;");
	// pushFun("tagForSolving", &tagForSolvingG);
	this->act.fireEvent("ON_GAME_LOADED");
	return ;
}

SS::Bundle::~Bundle()
{
}
