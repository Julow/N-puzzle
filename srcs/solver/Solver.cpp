// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 15:43:35 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/19 18:21:29 by ngoguey          ###   ########.fr       //
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

#define FUCK(a)
#define if			if(
#define then		)
#define raise		throw
#define let
#define in			;
#define begin		{ FUCK(})
#define end			}

let void		Solver::solve(void)
begin
	let value *const	f = caml_named_value("solve") in
	let value			res in // TODO: memory leak ?

	if f == NULL then
		raise std::runtime_error("Cannot start solver");
	else begin
		let res = caml_callback_exn(*f, (value)this) in // TODO: memory leak ?
		if Is_exception_result(res) then
			raise std::runtime_error("Fail to solve");
end
	throw std::runtime_error("Debug");
end

Grid const		&Solver::getGrid(void) const
{
	return (_initialGrid);
}

ISolverListener	*Solver::getListener(void)
{
	return (_listener);
}

};
