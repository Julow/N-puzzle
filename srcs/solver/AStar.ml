(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   AStar.ml                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 17:34:55 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/21 18:36:50 by ngoguey          ###   ########.fr       *)
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
		  Printf.eprintf "g(%2d) f(%2d) %!" sta.g sta.f;
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

	  (** 2.0 - Trying to expand successors *)
	  let expand ({Candidate.graph = cur_gra; Candidate.g = cur_g;}) =
		(** 3.0 - If already opened -> update info and push in opened *)
		(** 3.1 - If already closed -> discard *)
		(** 3.2 - If no info about it -> add info and push in opened *)
		let try_add neig_gra =
	  	  let neig_h = he neig_gra in
		  let neig_g = cur_g + (Graph.cost cur_gra neig_gra) in
		  (** 4.0 - Adding in both containers *)
		  let add info_insert =
			let neig_f = neig_h + neig_g in
	  		let neig_cdt = { Candidate.graph	= neig_gra;
	  						 Candidate.g		= neig_g;
	  						 Candidate.f		= neig_f; } in
	  		let neig_info = Opened { parent	= Some cur_gra;
	  								 g			= neig_g;
	  								 f			= neig_f; } in
			if neig_h < 2 then
			  Candidate.print neig_cdt;
			candidates := BatHeap.insert !candidates neig_cdt;
			info_insert infos neig_gra neig_info
		  in (** 4. END *)
		  try
			let info = Hashtbl.find infos neig_gra in
			match info with
			| Opened {g = g;} when neig_g < g	-> add Hashtbl.replace
			| _									-> ()
	  	  with
	  	  | Not_found							-> add Hashtbl.add
	  	in (** 3. END *)
	  	List.iter try_add (Graph.successors cur_gra)
	  in (** 2. END *)

	  (** 1.0 - Main loop popping one candidate *)
	  (** 1.1 - Expanding it if it was not closed in the meantime *)
	  let rec aux () =
		let cdt = BatHeap.find_min !candidates in
		let cdt_graph = cdt.Candidate.graph in
		candidates := BatHeap.del_min !candidates;
		if Graph.equal cdt_graph gra_goal then (
		  Printf.eprintf "AStar: SOLVED!!!!!!!!\n%!";
		  [])
		else match Hashtbl.find infos cdt_graph with
			 | Opened {parent = p; g = g; f = f;} ->
				let as_closed = Closed {parent = p; g = g; f = f;} in
				Hashtbl.replace infos cdt_graph as_closed;
				expand cdt;
				aux ()
			 | _ ->
				aux ()
	  in  (** 1. END *)
	  try
		aux ()
	  with
	  | Invalid_argument("find_min") ->
		 Printf.eprintf "AStar: NOT SOLVED\n%!";
		 []
  end