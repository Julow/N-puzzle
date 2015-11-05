// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OCamlBinding.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/05 11:51:35 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/05 18:08:54 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OCamlBinding.hpp"
#include "Grid.hpp"
#include "ft/assert.hpp" // Tester d'autres prositions dans l'ordre d'include
#include <stdexcept>
#include <stdio.h>

#include <vector>
#include <tuple>


#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/printexc.h>

namespace npuzzle
{


OCamlBinding::OCamlBinding(ISolverListener *el)
	: _currentGrid(), _el(el)
{
	char		*args = NULL;

	FTASSERT(el != nullptr);
	caml_startup(&args);
}

OCamlBinding::~OCamlBinding()
{
}

Grid const	&OCamlBinding::getGrid(void) const
{
	return (_currentGrid);
}

// ISolverListener *Solver::getListener(void)
// {
// 	return (_listener);
// }


/* ************************************************************************** */
/* C -> OCaml */

void		OCamlBinding::solve(Grid const &gr)
{
	value *const	f = caml_named_value("solve");
	value			res;

	FTASSERT(f != nullptr);
	this->_currentGrid = gr;
	res = caml_callback_exn(*f, (value)this); // TODO: memory leak ?
	if (Is_exception_result(res))
		throw std::runtime_error(
			caml_format_exception(Extract_exception(res)));
	return ;
}

/* ************************************************************************** */
/* C -> OCaml */

static double						valToDouble(value &val)
{
	FTASSERT(Is_block(val));
	FTASSERT(Tag_val(val) == Double_tag);
	return Double_val(val);
}

static int							valToInt(value &val)
{
	FTASSERT(Is_long(val));
	return Int_val(val);
}

static ft::Vec2<int>				valToIntTuple(value &val)
{
	FTASSERT(Is_block(val));
	FTASSERT(Wosize_val(val) == 2);
	return {valToInt(Field(val, 0)), valToInt(Field(val, 1))};
}

static std::string					valToString(value &val)
{
	FTASSERT(Is_block(val));
	FTASSERT(Tag_val(val) == String_tag);
	return String_val(val);
}

//0 initial_h   : int;

//1 nodes       : int;          (* SUBJECT.PDF *)
//2 sum_h       : int;
//3 max_open    : int;
//4 max_closed  : int;
//5 max_both    : int * int;    (* SUBJECT.PDF *)

//6 average_h   : float;
//7 time        : float;
//8 states      : state list;   (* SUBJECT.PDF *)

static ISolverListener::report_s	valToReport(value &val)
{
	value							val2 = Field(val, 0);
	ISolverListener::report_s		rep;

	FTASSERT(Wosize_val(val2) == 9);
	rep.time = valToDouble(Field(val2, 7));
	//TODO: retreive g
	rep.init_h = valToInt(Field(val2, 0));
	rep.avg_h = valToDouble(Field(val2, 6));
	rep.nodes = valToInt(Field(val2, 1));
	rep.max_open = valToInt(Field(val2, 3));
	rep.max_closed = valToInt(Field(val2, 4));
	rep.max_both = valToIntTuple(Field(val2, 5));
	//TODO: retreive steps
	return (rep);
}

static ISolverListener::progress_s	valToProgress(value &val)
{
	ISolverListener::progress_s	prog;

	FTASSERT(Wosize_val(val) == 1);
	prog.str = "nomsg"; //DOTO: Retreive Msg from ocaml
	prog.val = valToDouble(Field(val, 0));
	return (prog);
}


static std::string					valToFail(value &val)
{
	FTASSERT(Wosize_val(val) == 1);
	return (valToString(Field(val, 0)));
}

void		OCamlBinding::poll_event(void)
{
	value *const	f = caml_named_value("poll_event");
	value			res;

	FTASSERT(f != nullptr);
	while (1)
	{
		res = caml_callback_exn(*f, Val_unit); // TODO: memory leak ?
		if (Is_exception_result(res))
			throw std::runtime_error(
				caml_format_exception(Extract_exception(res)));
		if (Is_long(res))
		break ;
		FTASSERT(Wosize_val(res) == 1);
		FTASSERT(Tag_val(res) >=0 && Tag_val(res) <= 3);
		if (Tag_val(res) == 0)
			this->_el->onSuccess(valToReport(res));
		else if (Tag_val(res) == 1)
			this->_el->onFail(valToFail(res));
		else if (Tag_val(res) == 2)
			this->_el->onProgress(valToProgress(res));
	}
	return ;
}

/* ************************************************************************** */
/* C <- OCaml */

extern "C"
{
CAMLprim value  solver_hook_get_size(value binding)
{
	int             size;
	OCamlBinding	*b;

	CAMLparam1(binding);
	b = reinterpret_cast<OCamlBinding*>(binding);
	FTASSERT(b != nullptr);
	size = b->getGrid().getSize();
	CAMLreturn(Val_int(size));
}

CAMLprim value  solver_hook_get(value binding, value x, value y)
{
	int				v;
	OCamlBinding	*b;

	CAMLparam3(binding, x, y);
	b = reinterpret_cast<OCamlBinding*>(binding);
	FTASSERT(b != nullptr);
	v = b->getGrid().get(Int_val(x), Int_val(y));
	CAMLreturn(Val_int(v));
}
}

};
