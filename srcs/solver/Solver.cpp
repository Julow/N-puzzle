// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 15:43:35 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/04 17:50:54 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Solver.hpp"
#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <caml/printexc.h>
#include <stdexcept>
#include <stdio.h>
#include "ft/assert.hpp"

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
	else
	{
		res = caml_callback_exn(*f, (value)this); // TODO: memory leak ?
		if (Is_exception_result(res))
		{
			throw std::runtime_error(
				caml_format_exception(Extract_exception (res)));
		}
	}
	throw std::runtime_error("Debug from ngo");
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
