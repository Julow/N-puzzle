// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:42 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 15:35:20 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef STARTSTATE_HPP
# define STARTSTATE_HPP

//# include <string>
# include <iostream>
//# include <stdexcept>
# include "IState.hpp"
# include "tiles/Tiles.hpp"
# include "ftui/Activity.hpp"
# include "ftui/lua/lua.hpp"

class StartState final : public IState, public ISolverListener
{
public:

	/* CONSTRUCTION ***************** */
	static IState			*create(ftui::Canvas &can, OCamlBinding &ocaml);
	static void				globalInit(void);
	static void				loadFileGrid(std::string const &fileName);

	StartState() = delete;
	StartState(ftui::Canvas &can, OCamlBinding &ocaml);
	StartState(StartState const &src) = delete;
	StartState				&operator=(StartState const &rhs) = delete;
	~StartState();

	/* ISTATE LEGACY **************** */
	void					loop(
		std::unique_ptr<IState> &ptr
		, ftui::Canvas &can
		, OCamlBinding &ocaml) override;
	ftui::Activity			&getActivity(void) override;

	/* ISOLVERLISTENER LEGACY ******* */
	void					onSuccess(report_s rep) override;
	void					onProgress(progress_s prog) override;
	void					onFail(std::string const &str) override;

	/* LIBFTUI INTERACTIONS ********* */
	/* GETTERS ************ */
	static int				getAlgorithms(lua_State *l);
	static int				getHeuristics(lua_State *l);

	static int				getGridG(lua_State *l);
	Grid const				&getGrid(void) const;

	static int				getAlgorithmIdG(lua_State *l);
	int						getAlgorithmId(void) const;

	static int				getHeuristicIdG(lua_State *l);
	int						getHeuristicId(void) const;

	static int				getCostG(lua_State *l);
	int						getCost(void) const;

	/* SETTERS ************ */
	static int				useFileGridG(lua_State *l);
	void					useFileGrid(void);

	static int				useDefaultGridG(lua_State *l);
	void					useDefaultGrid(void);

	static int				useRandomGridG(lua_State *l);
	void					useRandomGrid(void);

	static int				setAlgorithmIdG(lua_State *l);
	void					setAlgorithmId(int id);

	static int				setHeuristicIdG(lua_State *l);
	void					setHeuristicId(int id);

	static int				setCostG(lua_State *l);
	void					setCost(int cost);

private:
	/* INTERNAL ********************* */
	Grid					_grid;
	unsigned int			_algorithmId;
	unsigned int			_heuristicId;
	int						_cost;

	static ftui::Activity	act;
	static Tiles			tiles;
	static const Grid		defaultGrid;
	static Grid				*filegrid;
	static StartState		*_instance;
public:
	static StartState		*instance(void);

};
//std::ostream					&operator<<(std::ostream &o, StartState const &rhs);

#endif // **************************************************** STARTSTATE_HPP //
