(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   AStar.ml                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 17:34:55 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/21 16:45:19 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH) ->
  struct
	type graph = Graph.t

	type parent = None | Some of graph
	type graph_info = Closed of { parent	: parent;
								  g			: int;
								  f			: int; }
					| Opened of { parent	: parent;
								  g			: int;
								  f			: int; }

	module type CANDIDATE =
	  sig
		type t = {
			graph   : graph;
			g       : int;
			f       : int;
		  }
		include GenericInterfaces.ORDEREDTYPE
				with type t := t
		val print	: t -> unit
	  end
	module Candidate : CANDIDATE =
	  struct
		type t = {
			graph   : graph;
			g       : int;
			f       : int;
		  }
		let compare a b =
		  a.f - b.f
		let print sta =
		  Printf.eprintf "g(%2d) f(%2d)\n%!" sta.g sta.f;
		  Graph.print sta.graph

	  end
	module BatHeap = BatHeap.Make(Candidate)

	type opened_container = BatHeap.t
	type info_container = (graph, graph_info) Hashtbl.t

	let solve gra_init gra_goal he =
	  Printf.eprintf "AStar Beginning ...\n%!";
	  let he_init = he gra_init in
	  let cdt_init = { Candidate.graph  	 	= gra_init;
					   Candidate.g   	    	= 0;
					   Candidate.f       		= he_init; } in
	  let info_init = Opened { parent			= None;
							   g				= 0;
							   f				= he_init; } in
	  let candidates = ref (BatHeap.insert BatHeap.empty cdt_init) in
	  let infos = Hashtbl.create 10000 in (* Try a lot more *)
	  Hashtbl.add infos gra_init info_init;

	  let expand ({Candidate.graph = cur_gra; Candidate.g = cur_g;}) =
		let try_add neig_gra =
		  try
			let info = Hashtbl.find infos neig_gra in
			()
	  	  with
	  	  | Not_found       ->
	  		 let neig_h = he neig_gra in
			 let neig_g = cur_g + (Graph.cost cur_gra neig_gra) in
			 let neig_f = neig_h + neig_g in
	  		 let neig_cdt = { Candidate.graph   = neig_gra;
	  						  Candidate.g       = neig_g;
	  						  Candidate.f     	= neig_f; } in
	  		 let neig_info = Opened { parent	= Some neig_gra;
	  								  g			= neig_g;
	  								  f			= neig_f; } in
			 if neig_h < 4 then
			   Candidate.print neig_cdt;
			 candidates := BatHeap.insert !candidates neig_cdt;
			 Hashtbl.add infos neig_gra neig_info;
			 ()
	  	in
	  	List.iter try_add (Graph.successors cur_gra);
	  	()
	  in

	  let close_info graph =
		let old_info = Hashtbl.find infos graph in
		let new_info = match old_info with
		  | Opened {parent = p; g = g; f = f;}
			-> Closed {parent = p; g = g; f = f;}
		  | _
			->
			 assert(false)
			 (* Closed {parent = p; g = g; f = f;} *)
		in
		Hashtbl.replace infos graph new_info
		(* new_info *)
	  in

	  let rec aux () =
		let cdt = BatHeap.find_min !candidates in
		candidates := BatHeap.del_min !candidates;
		close_info cdt.Candidate.graph;
		(* let info = get_new_info cdt.Candidate.graph in *)
		(* Check cdt.dat = info.dat *)
		if Graph.equal cdt.Candidate.graph gra_goal
		then (
		  Printf.eprintf "AStar: SOLVED\n%!";
		  [])
		else (expand cdt;
			  aux ())
	  in
	  try
		aux ()
	  with
	  | Invalid_argument("find_min") ->
		 Printf.eprintf "AStar: NOT SOLVED\n%!";
		 []
  end
