// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 15:43:35 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/16 19:46:53 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Solver.hpp"
#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <stdexcept>

namespace npuzzle
{

Solver::Solver(Grid const &grid, ISolverListener *listener) :
	_initialGrid(grid),
	_listener(listener)
{
	char		*args = NULL;

	caml_startup(&args);
}

Solver::~Solver(void)
{
}

void			Solver::solve(void)
{
	value *const	f = caml_named_value("solve");
	value			res; // TODO: memory leak ?

	if (f == NULL)
		throw std::runtime_error("Cannot start solver");
	res = caml_callback_exn(*f, (value)this); // TODO: memory leak ?
	if (Is_exception_result(res))
		throw std::runtime_error("Fail to solve");
}

Grid const		&Solver::getGrid(void) const
{
	return (_initialGrid);
}

ISolverListener	*Solver::getListener(void)
{
	return (_listener);
}

};
