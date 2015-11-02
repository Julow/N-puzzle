(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   EventHandler.ml                                    :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/11/02 07:50:05 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/02 10:21:18 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make =
  functor (State : GenericInterfaces.EVENT_HANDLER_STATE) ->
  struct

	type state = State.t

	type t = Success of state list
		   | Failed of string
		   | Progress of float
		   | Empty

	let q = (Queue.create () : t Queue.t)
	let m = Mutex.create ()

	(* ********************************************************************** *)
	(* MUTEXES *)


	(* ********************************************************************** *)
	(* DEBUG *)
	let dumpq () =
	  let i = ref 0 in
	  let aux ev =
		Printf.eprintf "i(%d) %!" !i;
		match ev with
		| Success l
		  -> Printf.eprintf "Solved of %d long list\n%!" (List.length l);
		| Failed s
		  -> Printf.eprintf "Failed of '%s'\n%!" s;
		| Progress n
		  -> Printf.eprintf "Progress of %6.2f%%\n%!" (n *. 100.);

		i := !i + 1;
	  in
	  Printf.eprintf "Events Queue:\n%!";
	  Queue.iter aux q;
	  ()

	(* ********************************************************************** *)
	let pushq t =
	  Mutex.lock m;
	  Queue.push t q;
	  Mutex.unlock m;
	  ()

	let popq _ =
	  Mutex.lock m;
	  let v = if Queue.is_empty q
			  then Empty
			  else Queue.pop q
	  in
	  Mutex.unlock m;
	  v

  end
