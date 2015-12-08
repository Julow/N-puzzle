// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ResultState.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 15:07:50 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/08 15:12:25 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <algorithm>

#include "ResultState.hpp"
#include "PickState.hpp"
#include "config_window.hpp"

using RS = ResultState;

/*
** ************************************************************************** **
** CONSTRUCTION
*/

RS::Bundle		*RS::loadBundle(Main &main, OCamlBinding &ocaml) /*static*/
{
	IBundle *const		ib = main.popBundle("ResultState");
	RS::Bundle *const	b = dynamic_cast<RS::Bundle*>(ib);

	if (b == nullptr)
	{
		FTASSERT(ib == nullptr, "Dynamic cast failed");
		return new RS::Bundle(main, ocaml);
	}
	return b;
}


RS::ResultState(Main &main, OCamlBinding &ocaml, ISolverListener::report_s r)
	: _main(main)
	, _ocaml(ocaml)
	, _b(loadBundle(main, ocaml))
	, _leave(false)
{
	lua_State	*l = this->_b->act.getLuaState();
	auto		*bun = this->_b;
	auto		&act = bun->act;
	int			ret;
// TODO: ftlua
	ret = lua_getglobal(l, "ResultState");
	FTASSERT(ret == LUA_TTABLE);

	lua_pushinteger(l, 0);
	lua_pushlightuserdata(l, this);
	lua_settable(l, -3);

	lua_pop(l, 1);
	// act.fireEvent("GRID_LIST_UPDATE", bun->extractGridNames()
	// 					, bun->grids.size());
	act.fireEvent("RESULT_DATA", r.time, r.g, r.init_h, r.avg_h, r.nodes
				  , r.max_open, r.max_closed, r.max_both, r.steps);

	// act.fireEvent("Bordel", 42, std::string("caca"));

	act.queryRedrawAll();

	return ;
}

RS::~ResultState()
{
	this->_main.pushBundle("ResultState", this->_b);
	return ;
}

/*
** ************************************************************************** **
** ISTATE LEGACY
*/

void            RS::loop(std::unique_ptr<IState> &ptr, ftui::ACanvas &can)
{
	(void)ptr;
	this->_b->tiles.render();
	this->_b->act.render(can);
	if (this->_leave)
	{
		can.clear();
		ptr.reset(new PickState(_main, _ocaml));
		// throw std::runtime_error("OK");
	}
	return ;
}

ftui::Activity  &RS::getActivity(void)
{
	return this->_b->act;
}

/*
** ************************************************************************** **
** LIBFTUI INTERACTIONS
*/

int				RS::tagForLeaveG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 0>(l, &RS::tagForLeave);
}
void			RS::tagForLeave(void)
{ _leave = true; }

ResultState		*RS::ftlua_pop(lua_State *l, int i,
						std::function<void(std::string)> panic)
{
	ResultState		*v;
	int				type;

	FTLUA_STACKASSERT_PANIC(
		l, lua_istable(l, i), panic
		, ft::f("ResultState::ftlua_pop(i = %)", i), ft::f("No table at i"));
	ftlua::push(l, 0);
	type = lua_gettable(l, i < 0 ? i - 1 : i);
	FTLUA_STACKASSERT_PANIC(
		l, type == LUA_TLIGHTUSERDATA, panic
		, ft::f("ResultState::ftlua_pop(i = %)", i), ft::f("No pointer at [0]"));
	v = reinterpret_cast<ResultState*>(lua_touserdata(l, -1));
	lua_pop(l, 1);
	lua_remove(l, i);
	return v;
}

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
		   , /*ft::Vec3<int> const gray =*/ ft::Vec3<int>(120, 181, 129)
		   , /*ft::Vec3<int> const pink =*/ ft::Vec3<int>(10, 150, 10)
		   // , /*ft::Vec3<int> const pink =*/ ft::Vec3<int>(230, 46, 77)
		   , /*ft::Vec3<int> const deltaPink =*/ ft::Vec3<int>(10, 45, 10));
		   // , /*ft::Vec3<int> const deltaPink =*/ ft::Vec3<int>(50, 10, 77));
	return t;
}

RS::Bundle::Bundle(Main &main, OCamlBinding &ocaml)
	: tiles(make_tiles())
	, act(WIN_SIZEVI)
{
	ftui::Activity			&act = this->act;
	auto					pushFun =
		[&](std::string const &fname, lua_CFunction f)
		{ act.registerLuaCFun_table("ResultState", fname, f); };
	std::ifstream			is("res/layout/result_state.xml");

	act.inflate(is);
	main.loadSharedScripts(act);
	luaL_dostring(act.getLuaState()
				  , "ResultState = {}; GridColor = 0x0000FF;");
	pushFun("tagForLeave", &tagForLeaveG);
	this->act.fireEvent("ON_GAME_LOADED");
	return ;
}

RS::Bundle::~Bundle()
{
}
