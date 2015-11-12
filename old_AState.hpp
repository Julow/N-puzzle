// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AState.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/11 19:32:02 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 14:28:51 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ASTATE_HPP
# define ASTATE_HPP

# include <memory>

# include "ftui/Canvas.hpp"
# include "ftui/Activity.hpp"
# include "ftlua/ftlua.hpp"

# include "OCamlBinding.hpp"

class AState
{
public:

	/* CONSTRUCTION ***************** */
	static AState			*instance(void);
	static void				globalInit(void);
	static void				loadGlobalScripts(ftui::Activity &a);
	static void				loadFileGrid(std::string const &fileName);
protected:
	static AState			*_instance;
public:

	AState();
	virtual ~AState();

	AState(AState const &src) = delete;
	AState					&operator=(AState const &rhs) = delete;

	/* METHODS ********************** */
	virtual void			loop(
		std::unique_ptr<AState> &ptr
		, ftui::Canvas &can
		, OCamlBinding &ocaml) = 0;
	virtual ftui::Activity	&getActivity(void) = 0;

	/* LIBFTUI INTERACTIONS ********* */
	/* GETTERS ************ */
	static int				getAlgorithms(lua_State *l);
	static int				getHeuristics(lua_State *l);
	static int				getTranspToReal(lua_State *l);

	static int				getGridG(lua_State *l);
	Grid const				&getGrid(void) const;

	static int				getAlgorithmIdG(lua_State *l);
	int						getAlgorithmId(void) const;

	static int				getHeuristicIdG(lua_State *l);
	int						getHeuristicId(void) const;

	static int				getCostG(lua_State *l);
	int						getCost(void) const;

protected:
/* INTERNAL ********************* */
	Grid					_grid;
	unsigned int			_algorithmId;
	unsigned int			_heuristicId;
	int						_cost;

	static const Grid		defaultGrid;
	static Grid				*filegrid;

};

#endif // ******************************************************** ASTATE_HPP //
