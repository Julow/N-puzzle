// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OCamlBinding.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/05 12:38:10 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/09 13:27:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OCAMLBINDING_HPP
# define OCAMLBINDING_HPP

# include "Grid.hpp"
# include "ISolverListener.hpp"
# include "ftui/lua/lua.hpp"

class OCamlBinding
{
public:

	OCamlBinding();
	~OCamlBinding();

	void					setListener(ISolverListener *el);
	void					solve(Grid const &gr);
	void					poll_event(void);
	Grid					generate_grid(int w, bool solvable);
	static int				generate_gridG(lua_State *l);

	Grid const				&getGrid(void) const;

	static OCamlBinding		*instance(void);

protected:
private:

	static OCamlBinding		*_instance;

	Grid					_currentGrid;
	ISolverListener			*_el;

	OCamlBinding(OCamlBinding const &src) = delete;
	OCamlBinding				&operator=(OCamlBinding const &rhs) = delete;
};

#endif // ************************************************** OCAMLBINDING_HPP //
