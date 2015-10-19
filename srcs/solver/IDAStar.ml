(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   IDAStar.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 18:14:20 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/19 18:26:10 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH) ->
  struct

	type graph = Graph.t

	let solved_val = -42

	let solve grainit gragoal he =
	  Printf.eprintf "IDAStar Beginning ...\n%!";

	  let rec search gra g threshold =
		let h = he gra in
		let f = g + h in
		if f > threshold then
		  (

			(* if h < 10 then ( *)
			(*   Printf.eprintf "g(%2d) h(%2d) threshold(%2d)\n%!" g h threshold; *)
			(*   Graph.print gra *)
			(* ); *)
			f
		  )
		else if Graph.equal gra gragoal then (
		  Printf.eprintf "g(%2d) h(%2d) threshold(%2d)\n%!" g h threshold;
		  Graph.print gra;
		  solved_val
		)
		else
		  min_successor gra g threshold
	  and min_successor gra g threshold =
		let rec aux successors decr =
		  match successors with
		  | hd::tl          ->
			 let v = search hd (g + (Graph.cost gra hd)) threshold in
			 if v = solved_val
			 then solved_val
			 else aux tl (min v decr)
		  | _               -> decr
		in
		aux (Graph.successors gra) max_int
	  in

	  let rec aux threshold =
		let threshold' = search grainit 0 threshold in
		Printf.eprintf "IDA* loop\n%!";
		if threshold' = solved_val
		then (
		  Printf.eprintf "IDAStar: solved\n%!";
		  ())
		else aux threshold'
	  in
	  aux (he grainit);
	  []

  end
