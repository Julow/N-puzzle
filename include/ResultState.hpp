// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ResultState.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 15:07:48 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/08 15:08:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef RESULTSTATE_HPP
# define RESULTSTATE_HPP

# include "ISolverListener.hpp"
# include "Main.hpp"
# include "tiles/Tiles.hpp"

class ResultState : public IState
{
	/* ATTRIBUTES ******************* */
private:
	class Bundle;
	static Bundle			*loadBundle(Main &main, OCamlBinding &ocaml);

	Main					&_main;
	OCamlBinding			&_ocaml;
	Bundle *const			_b;
	bool					_leave;

	/* CONSTRUCTION ***************** */
public:
	ResultState(Main &main, OCamlBinding &ocaml, ISolverListener::report_s r);
	~ResultState();

	ResultState() = delete;
	ResultState(ResultState const &src) = delete;
	ResultState(ResultState &&src) = delete;
	ResultState				&operator=(ResultState const &rhs) = delete;
	ResultState				&operator=(ResultState &&rhs) = delete;

	/* ISTATE LEGACY **************** */
	void					loop(
		std::unique_ptr<IState> &ptr
		, ftui::ACanvas &can) override;
	ftui::Activity			&getActivity(void) override;

	/* LIBFTUI INTERACTIONS ********* */
	typedef std::integral_constant<unsigned int, 1> ftlua_size;
	//TODO: Push application's classes too
	static ResultState		*ftlua_pop(lua_State *l, int i,
								std::function<void(std::string)> panic);

	static int				tagForLeaveG(lua_State *l);
	void					tagForLeave(void);

};

/* BUNDLE DECLARATION *************** */
class ResultState::Bundle : public IBundle
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

};

#endif /* *************************************************** RESULTSTATE_HPP */
