// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 15:40:32 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/16 18:41:45 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include "ISolverListener.hpp"
# include "Grid.hpp"

namespace npuzzle
{

class	Solver
{
public:
	Solver(Grid const &grid, ISolverListener *listener);
	virtual ~Solver(void);

	bool			solve(void);

	Grid const		&getGrid(void) const;

	ISolverListener	*getListener(void);

protected:

	Grid const		&_initialGrid;

	ISolverListener	*_listener;

private:
	Solver(void);
	Solver(Solver const &src);
	Solver			&operator=(Solver const &rhs);
};

};

#endif
