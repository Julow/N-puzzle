// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PickState.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 18:05:46 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/24 11:20:43 by jaguillo         ###   ########.fr       //
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
	static Bundle			*loadBundle(Main &main);

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
	static int				useDefaultGridG(lua_State *l);
	void					useDefaultGrid(void);

	static int				useRandomGridG(lua_State *l);
	void					useRandomGrid(int w, bool solvable);

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
	Bundle(Main &main);
	~Bundle();

	Bundle() = delete;
	Bundle(Bundle const &src) = delete;
	Bundle(Bundle &&src) = delete;
	Bundle					&operator=(Bundle const &rhs) = delete;
	Bundle					&operator=(Bundle &&rhs) = delete;

	/* ATTRIBUTES ******************* */
	Tiles const				tiles;
	ftui::Activity			act;
	std::vector<Grid>		grids;

};

#endif /* ***************************************************** PICKSTATE_HPP */
