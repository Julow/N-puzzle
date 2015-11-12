// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PickState.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/12 18:05:46 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 18:09:22 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PICKSTATE_HPP
# define PICKSTATE_HPP

// # include <iostream>
// # include <>

# include "Main.hpp"
# include "tiles/Tiles.hpp"
// # include ""

class PickState : public IState
{
	/* CONSTRUCTION ***************** */
private:
	static Tiles const		*tilesInstance(void);
	static ftui::Activity	*activityInstance(void);

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
		, ftui::Canvas &can) override;
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

private:
	Main					&_main;
	OCamlBinding			&_ocaml;
	bool					_launchSolvingState;

};
//std::ostream			&operator<<(std::ostream &o, PickState const &rhs);

#endif /* ***************************************************** PICKSTATE_HPP */
