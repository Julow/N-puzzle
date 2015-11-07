// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OCamlBinding.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/05 12:38:10 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 10:12:52 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OCAMLBINDING_HPP
# define OCAMLBINDING_HPP

# include "Grid.hpp"
# include "ISolverListener.hpp"
// # include "ft/Vec.hpp"

class OCamlBinding
{
public:

	OCamlBinding();
	~OCamlBinding();

	void					setListener(ISolverListener *el);
	void					solve(Grid const &gr);
	void					poll_event(void);

	Grid const				&getGrid(void) const;

protected:
private:

	Grid					_currentGrid;
	ISolverListener			*_el;

	OCamlBinding(OCamlBinding const &src) = delete;
	OCamlBinding				&operator=(OCamlBinding const &rhs) = delete;
};

#endif // ************************************************** OCAMLBINDING_HPP //
