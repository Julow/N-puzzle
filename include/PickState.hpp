// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PickState.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 18:05:46 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 16:59:24 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PICKSTATE_HPP
# define PICKSTATE_HPP

# include "Main.hpp"
# include "tiles/Tiles.hpp"

class PickState : public IState
{
	/* ATTRIBUTES ******************* */
private:
	class Bundle;
	static Bundle			*loadBundle(Main &main, OCamlBinding &ocaml);

	Main					&_main;
	OCamlBinding			&_ocaml;
	Bundle *const			_b;
	bool					_launchSolvingState;

	/* CONSTRUCTION ***************** */
public:
	PickState(Main &main, OCamlBinding &ocaml);
	~PickState();

	PickState() = delete;
	PickState(PickState const &src) = delete;
	PickState(PickState &&src) = delete;
	PickState				&operator=(PickState const &rhs) = delete;
	PickState				&operator=(PickState &&rhs) = delete;

	/* ISTATE LEGACY **************** */
	void					loop(
		std::unique_ptr<IState> &ptr
		, ftui::ACanvas &can) override;
	ftui::Activity			&getActivity(void) override;

	/* LIBFTUI INTERACTIONS ********* */
	typedef std::integral_constant<unsigned int, 1> ftlua_size;
	//TODO: Push application's classes too
	static PickState	*ftlua_pop(lua_State *l, int i, std::function<void(std::string)> panic)
		{
			PickState		*v;
			int				type;

			FTLUA_STACKASSERT_PANIC(
				l, lua_istable(l, i), panic
				, ft::f("PickState::ftlua_pop(i = %)", i), ft::f("No table at i"));
			ftlua::push(l, 0);
			type = lua_gettable(l, i < 0 ? i - 1 : i);
			FTLUA_STACKASSERT_PANIC(
				l, type == LUA_TLIGHTUSERDATA, panic
				, ft::f("PickState::ftlua_pop(i = %)", i), ft::f("No pointer at [0]"));
			v = reinterpret_cast<PickState*>(lua_touserdata(l, -1));
			lua_pop(l, 1);
			lua_remove(l, i);
			return v;
		}

	static int				selectGridG(lua_State *l);
	void					selectGrid(int i);
	static int				deleteGridG(lua_State *l);
	void					deleteGrid(int i);

	static int				pushRandomGridG(lua_State *l);
	void					pushRandomGrid(int w, bool solvable, int nloops);


	static int				getNumGridsG(lua_State *l);
	int						getNumGrids(void);
	static int				getGridNameG(lua_State *l);
	std::string const		&getGridName(int i);
	static int				getGridG(lua_State *l);
	Grid const				&getGrid(int i);
	static int				getMainGridIdG(lua_State *l);
	int						getMainGridId(void);


	static int				useDefaultGridG(lua_State *l);
	void					useDefaultGrid(void);


	static int				setAlgorithmIdG(lua_State *l);
	void					setAlgorithmId(int id);

	static int				setHeuristicIdG(lua_State *l);
	void					setHeuristicId(int id);

	static int				setCostG(lua_State *l);
	void					setCost(int cost);

	static int				tagForSolvingG(lua_State *l);
	void					tagForSolving(void);

};

/* BUNDLE DECLARATION *************** */
class PickState::Bundle : public IBundle
{
public:
	/* CONSTRUCTION ***************** */
	Bundle(Main &main, OCamlBinding &ocaml);
	~Bundle();

	Bundle() = delete;
	Bundle(Bundle const &src) = delete;
	Bundle(Bundle &&src) = delete;
	Bundle					&operator=(Bundle const &rhs) = delete;
	Bundle					&operator=(Bundle &&rhs) = delete;

	/* ATTRIBUTES ******************* */
	Tiles const				tiles;
	ftui::Activity			act;
	int						selectedId;
	std::vector<Grid>		grids;

	/* FUNCTIONALITIES ************** */
	std::vector<std::string const*>		extractGridNames(void);

};

#endif /* ***************************************************** PICKSTATE_HPP */
