// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SolvingState.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/29 14:06:17 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:48:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLVINGSTATE_HPP
# define SOLVINGSTATE_HPP

# include "tiles/Tiles.hpp"

# include "Main.hpp"
# include "ISolverListener.hpp"

class SolvingState : public IState, public ISolverListener
{
	/* ATTRIBUTES ******************* */
private:
	class Bundle;
	static Bundle			*loadBundle(Main &main, OCamlBinding &ocaml);

	Main					&_main;
	OCamlBinding			&_ocaml;
	Bundle *const			_b;
	bool					_abortSolvingState;

	/* CONSTRUCTION ***************** */
public:
	SolvingState(Main &main, OCamlBinding &ocaml);
	~SolvingState();

	SolvingState() = delete;
	SolvingState(SolvingState const &src) = delete;
	SolvingState(SolvingState &&src) = delete;
	SolvingState				&operator=(SolvingState const &rhs) = delete;
	SolvingState				&operator=(SolvingState &&rhs) = delete;

	/* ISTATE LEGACY **************** */
	void					loop(
		std::unique_ptr<IState> &ptr
		, ftui::ACanvas &can) override;
	ftui::Activity			&getActivity(void) override;

	/* ISOLVERLISTENER LEGACY ******* */
	void					onSuccess(report_s rep) override;
	void					onProgress(progress_s prog) override;
	void					onFail(std::string const &str) override;


	/* LIBFTUI INTERACTIONS ********* */
	static int				tagForAbortG(lua_State *l);
	void					tagForAbort(void);

};

/* BUNDLE DECLARATION *************** */
class SolvingState::Bundle : public IBundle
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

	/* FUNCTIONALITIES ************** */
	std::vector<std::string const*>		extractGridNames(void);

};

#endif /* ************************************************** SOLVINGSTATE_HPP */
