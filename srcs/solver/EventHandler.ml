(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   EventHandler.ml                                    :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/11/02 07:50:05 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/12/07 15:28:09 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make =
  functor (State : GenericInterfaces.EVENT_HANDLER_STATE) ->
  struct

	type state = State.t
	type report = { initial_h	: int;

					nodes		: int;			(* SUBJECT.PDF *)
					sum_h		: int;
					max_open	: int;
					max_closed	: int;
					max_both	: int * int;	(* SUBJECT.PDF *)

					average_h	: float;
					time		: float;
					states		: state list;	(* SUBJECT.PDF *)
				  }

	type t = Success of report
		   | Failed of string
		   | Progress of float (* TODO: * string *)
		   | Empty

	let pipe = ref None

	(* ********************************************************************** *)
	(* DEBUG *)
	let dump_event = function
	  | Success l
		-> let steps = List.length l.states - 1 in
		   let ma, mb = l.max_both in
		   let m = ma + mb in
		   Printf.eprintf "Solved (%d steps) (%d plan) (%.2f avgplan) "
						  steps l.initial_h l.average_h;
		   Printf.eprintf "(%.2fsec) (%d maxo / %d maxc) (%d max(%d, %d)) "
						  l.time l.max_open l.max_closed m ma mb;
		   Printf.eprintf "(%d nodes)\n%!"
						  l.nodes;
		   ()
	  | Failed s
		-> Printf.eprintf "Failed of '%s'\n%!" s;
		   ()
	  | Progress n
		-> Printf.eprintf "Progress of %6.2f%%\n%!" (n *. 100.);
		   ()
	  | _
		-> Printf.eprintf "Empty\n%!";
		   ()

	(* ********************************************************************** *)
	(* PIPE OPERATIONS *)

	(* From SlaveThread after fork *)
	let pushq ev =
	  Printf.eprintf "........Writing pipe:\n%!";
	  dump_event ev;
	  Printf.eprintf "........\n%!";
	  let chanin = match !pipe with
		| Some (_, pipein)	-> Unix.out_channel_of_descr pipein
		| _					-> failwith "Error pushq"
	  in
	  Marshal.to_channel chanin ev [];
	  ()

	(* From MainThread after fork *)
	let popq _ =
	  Printf.eprintf "...........Reading pipe\n%!";
	  let chanout = match !pipe with
		| Some (pipeout, _)	-> Unix.in_channel_of_descr pipeout
		| _					-> failwith "Error pushq"
	  in
	  try
		let ev = (Marshal.from_channel chanout : t) in
		dump_event ev;
		ev
	  with
	  | _	->
		 Printf.eprintf "failed :(\n.........\n%!";
		 Empty

	(* From MainThread before fork *)
	let makepipe _ =
	  Printf.eprintf "Making pipe\n%!";
	  let ((pipeout, _) as p) = Unix.pipe () in
	  Unix.set_nonblock pipeout;
	  pipe := Some p;
	  ()

	let killpipe _ =
	  match !pipe with
	  | Some (pipeout, pipein)	-> Unix.close pipeout;
								   Unix.close pipein
	  | _						-> ()

	(* ********************************************************************** *)
	(* REPORT OPERATIONS *)
	let new_report initial_h =
	  { initial_h	= initial_h;
		nodes		= 0;
		sum_h		= 0;
		max_open	= 0;
		max_closed	= 0;
		max_both	= 0, 0;
		average_h	= 0.;
		time		= Unix.gettimeofday ();
		states		= []; }

	let tick_report rep h n_open n_closed =
	  { rep with
		nodes		= rep.nodes + 1;
		sum_h		= rep.sum_h + h;
		max_open	= max rep.max_open n_open;
		max_closed	= max rep.max_closed n_closed;
		max_both	= if n_open + n_closed > (fun (o, c) -> o + c) rep.max_both
					  then n_open, n_closed
					  else rep.max_both;}

	let finalize_report rep states =
	  { rep with
		average_h	= float rep.sum_h /. float rep.nodes;
		time		= Unix.gettimeofday () -. rep.time;
		states		= states;}


  end

(* ************************************************************************** *)
