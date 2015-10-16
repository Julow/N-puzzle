// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver_hooks.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 15:47:38 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/16 19:26:25 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Solver.hpp"
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>

namespace npuzzle
{

extern "C"
{

CAMLprim value	solver_hook_get_size(value solver)
{
	int				size;

	CAMLparam1(solver);
	size = reinterpret_cast<Solver*>(solver)->getGrid().getSize();
	CAMLreturn(Val_int(size));
}

CAMLprim value	solver_hook_get(value solver, value x, value y)
{
	int				c;

	CAMLparam3(solver, x, y);
	c = reinterpret_cast<Solver*>(solver)->getGrid().get(Int_val(x), Int_val(y));
	CAMLreturn(Val_int(c));
}

CAMLprim value	solver_hook_put_progress(value solver, value progress)
{
	ISolverListener		*listener;

	CAMLparam2(solver, progress);
	listener = reinterpret_cast<Solver*>(solver)->getListener();
	if (listener != nullptr)
		listener->put_progress(Double_val(progress));
	CAMLreturn(Val_unit);
}

CAMLprim value	solver_hook_put_step(value solver, value step)
{
	CAMLparam2(solver, step);
	CAMLreturn(Val_unit);
}

}

};
