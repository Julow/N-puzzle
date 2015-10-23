(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   IDAStar.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 18:14:20 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/23 16:41:56 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH) ->
  struct

	type graph = Graph.t

	let solved_val = -42

	let solve grasrc gragoal he =
	  Printf.eprintf "IDAStar Beginning ...\n%!";
	  let result = ref [] in

	  let rec search gra g threshold =

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
	  List.iteri (fun i gra ->Printf.eprintf "g(%2d) h(%2d)" i (he gra);
							  Graph.print gra) !result;
	  !result

  end
