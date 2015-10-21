(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   IDAStar.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 18:14:20 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/21 13:26:23 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH) ->
  struct

	type graph = Graph.t

	let solved_val = -42

	let solve grainit gragoal he =
	  Printf.eprintf "IDAStar Beginning ...\n%!";
	  let result = ref [] in

	  let rec search gra g threshold =

		let rec try_successor successors decr =
		  match successors with
		  | hd::tl          ->
			 let v = search hd (g + (Graph.cost gra hd)) threshold in
			 if v = solved_val
			 then (result := hd::!result;
				   solved_val)
			 else try_successor tl (min v decr)
		  | _               -> decr
		in
		let h = he gra in
		let f = g + h in
		if f > threshold then
		  f
		else if Graph.equal gra gragoal then (
		  Printf.eprintf "g(%2d) h(%2d) threshold(%2d)\n%!" g h threshold;
		  Graph.print gra;
		  (* result := gra::!result; *)
		  solved_val
		)
		else
		  try_successor (Graph.successors gra) max_int
	  in

	  let rec aux threshold =
		Printf.eprintf "IDA* loop %d->threshold \n%!" threshold;
		let threshold' = search grainit 0 threshold in
		if threshold' = solved_val
		then (
		  Printf.eprintf "IDAStar: solved!!!!!!!!!!\n%!";
		  result := grainit::!result;
		  Printf.eprintf "%d steps\n%!" (List.length !result - 1);
		  (* List.iteri (fun i gra -> Printf.eprintf "(%2d)->%!" i; *)
		  (* 						   Graph.print gra) !result; *)


		  Printf.eprintf "IDAStar: solved!!!!!!!!!!\n%!";
		  !result

		)
		else aux threshold'
	  in
	  aux (he grainit)

  end
