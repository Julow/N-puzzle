// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:42 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 19:52:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef STARTSTATE_HPP
# define STARTSTATE_HPP

//# include <string>
# include <iostream>
//# include <stdexcept>
# include "AState.hpp"
# include "tiles/Tiles.hpp"
# include "ftui/Activity.hpp"
# include "ftui/lua/lua.hpp"

class StartState final : public AState, public ISolverListener
{
public:

	/* CONSTRUCTION ***************** */
	static AState			*create(ftui::Canvas &can, OCamlBinding &ocaml);
	static void				globalInit(void);
	static StartState		*instance(void);

	StartState(ftui::Canvas &can, OCamlBinding &ocaml);
	~StartState();

	StartState() = delete;
	StartState(StartState const &src) = delete;
	StartState				&operator=(StartState const &rhs) = delete;

	/* ISTATE LEGACY **************** */
	void					loop(
		std::unique_ptr<AState> &ptr
		, ftui::Canvas &can
		, OCamlBinding &ocaml) override;
	ftui::Activity			&getActivity(void) override;

	/* ISOLVERLISTENER LEGACY ******* */
	void					onSuccess(report_s rep) override;
	void					onProgress(progress_s prog) override;
	void					onFail(std::string const &str) override;

	/* LIBFTUI INTERACTIONS ********* */
	/* SETTERS ************ */
	static int				useFileGridG(lua_State *l);
	void					useFileGrid(void);

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

	static int				launchSolvingG(lua_State *l);
	void					launchSolving(void);

private:
	/* INTERNAL ********************* */
	bool					_launchSolving;

	static ftui::Activity	act;
	static Tiles			tiles;

};

#endif // **************************************************** STARTSTATE_HPP //
