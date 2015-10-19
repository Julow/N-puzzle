(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   AStar.ml                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 17:34:55 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/19 18:28:33 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH) ->
  struct
	type graph = Graph.t
	module type STATE =
	  sig
		type t = {
			graph   : graph;
			g       : int;
			h       : int;
		  }
		include GenericInterfaces.ORDEREDTYPE
				with type t := t
		val print	: t -> unit
	  end
	module State : STATE =
	  struct
		type t = {
			graph   : graph;
			g       : int;
			h       : int;
		  }
		let compare a b =
		  (a.g + a.h) - (b.g + b.h)
		let print sta =
		  Printf.eprintf "g(%2d) h(%2d)\n%!" sta.g sta.h;
		  Graph.print sta.graph

	  end
	module StateBatHeap = BatHeap.Make(State)

	type opened = StateBatHeap.t
	type closed = (graph, unit) Hashtbl.t

	let solve grainit gragoal he =
	  Printf.eprintf "AStar Beginning ...\n%!";
	  let stainit = {
		  State.graph   = grainit;
		  State.g       = 0;
		  State.h       = he grainit;
		} in
	  let opened = ref (StateBatHeap.insert StateBatHeap.empty stainit) in
	  let closed = Hashtbl.create 10000 in

	  let expand ({State.graph = par_gra; State.g = par_g;}) =
		let try_add succ_gra =
		  try
			Hashtbl.find closed succ_gra
		  with
		  | Not_found       ->
			 let succ_h = he succ_gra in
			 let succ_sta = {
				 State.graph    = succ_gra;
				 State.g        = par_g + 1;
				 State.h        = succ_h;
			   } in
			 if succ_h < 4 then
			   State.print succ_sta;
			 opened := StateBatHeap.insert !opened succ_sta
		in
		List.iter try_add (Graph.successors par_gra);
		()
	  in

	  let rec aux () =
		let sta = StateBatHeap.find_min !opened in
		opened := StateBatHeap.del_min !opened;
		Hashtbl.add closed sta.State.graph ();
		if Graph.equal sta.State.graph gragoal
		then (
		  Printf.eprintf "AStar: SOLVED\n%!";
		  [])
		else (expand sta;
			  aux ())
	  in
	  try
		aux ()
	  with
	  | Invalid_argument("find_min") ->
		 Printf.eprintf "AStar: NOT SOLVED\n%!";
		 []
  end
