(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   IDAStar.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 18:14:20 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/04 17:49:09 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH)
			(EventHandler : GenericInterfaces.EVENT_HANDLER
			 with type state = Graph.t) ->
  struct

	type graph = Graph.t

	let solved_val = -42

	let solve grasrc gragoal he =
	  Printf.eprintf "IDAStar Beginning ...\n%!";
	  let result = ref [] in

	  (** 2.0 - *)
	  let rec search gra g threshold =

		(** 3.0 - Trying to expand successors *)
		let rec try_successor successors decr =
		  match successors with
		  | hd::tl						->
			 let v = search hd (g + Graph.cost gra hd) threshold in
			 if v = solved_val
			 then (result := hd::!result;
				   solved_val)
			 else try_successor tl (min v decr)
		  | _							-> decr
		in
		let h = he gra in
		let f = g + h in
		if f > threshold then
		  f
		else if Graph.equal gra gragoal then (
		  Printf.eprintf "Found sol g(%2d) h(%2d) f(%2d) threshold(%2d)\n%!"
						 g h f threshold;
		  solved_val)
		else
		  try_successor (Graph.successors gra) max_int
	  in

	  (** 1.0 - Main loop launches a Depth-first search increasing threshold *)
	  (** 1.0 - If threshold' = magic solved_val then solution is found *)
	  let rec aux threshold =
		Printf.eprintf "IDA* loop %d->threshold \n%!" threshold;
		let threshold' = search grasrc 0 threshold in
		if threshold' = solved_val
		then (result := grasrc::!result;
			  Printf.eprintf "IDA*: solved with %d steps\n%!"
							 (List.length !result - 1))
		else aux threshold'
	  in
	  aux (he grasrc);
	  (* List.iteri (fun i gra ->Printf.eprintf "g(%2d) h(%2d)" i (he gra); *)
	  (* 						  Graph.print gra) !result; *)
	  EventHandler.pushq (EventHandler.Progress 1.);
	  EventHandler.pushq (EventHandler.Success !result);
	  ()

  end
