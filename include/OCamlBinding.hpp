// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OCamlBinding.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/05 12:38:10 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 17:13:21 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OCAMLBINDING_HPP
# define OCAMLBINDING_HPP

# include "Grid.hpp"
# include "ISolverListener.hpp"

class OCamlBinding
{
private:

	/* CONSTRUCTION ***************** */
	static OCamlBinding		*_instance;
public:
	static OCamlBinding		*instance(void);

	OCamlBinding();
	~OCamlBinding();

	OCamlBinding(OCamlBinding const &src) = delete;
	OCamlBinding			&operator=(OCamlBinding const &rhs) = delete;

	/* MECHANISMS ******************* */
	void					setListener(ISolverListener *el);
	Grid const				&getGrid(void) const;

	/* INTERACTIONS C-OCAML ********* */
	void					solve(Grid const &gr, int aid, int hid, int cost);
	void					poll_event(void);
	Grid					generate_grid(int w, bool solvable, int nloops);
	void					end_solver(void);
	std::vector<std::string>	algorithm_list(void);
	std::vector<std::string>	heuristic_list(void);
	std::vector<int>		transposition_toreal(unsigned int w);
	std::vector<int>		transposition_toabstract(unsigned int w);

protected:

	Grid					_currentGrid;
	ISolverListener			*_el;

};

#endif // ************************************************** OCAMLBINDING_HPP //
