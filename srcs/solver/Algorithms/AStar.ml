(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   AStar.ml                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/19 17:34:55 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/12/07 19:52:36 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Make : GenericInterfaces.MAKE_HEPATHFINDER =
  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH)
			(EventHandler : GenericInterfaces.EVENT_HANDLER
			 with type state = Graph.t) ->
  struct
	type graph = Graph.t
	type parent = None | Some of graph * graph_info
	 and graph_info = { parent		: parent;
						g			: int;
						f			: int; }
	type graph_state = Closed of graph_info | Opened of graph_info

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
		  Printf.eprintf "f(%2d) = g(%2d) + h(%2d)%!"
						 sta.f sta.g (sta.f - sta.g);
		  Graph.print sta.graph
	  end
	module BatHeap = BatHeap.Make(Candidate)

	type opened_container = BatHeap.t
	type info_container = (graph, graph_info) Hashtbl.t

	let retreive_steps graph info =
	  let rec aux info acc =
	  	match info.parent with
	  	| Some (graph, info)		-> aux info (graph::acc)
		| _							-> acc
	  in
	  aux info [graph]

	let solve gra_init gra_goal he =
	  EventHandler.pushq (EventHandler.Progress 0.);

	  let he_init = he gra_init in
	  let cdt_init = { Candidate.graph  	 	= gra_init;
					   Candidate.g   	    	= 0;
					   Candidate.f       		= he_init; } in
	  let info_init = Opened { parent			= None;
							   g				= 0;
							   f				= he_init; } in
	  let candidates = ref (BatHeap.insert BatHeap.empty cdt_init) in
	  let infos = Hashtbl.create 100000 in
	  Hashtbl.add infos gra_init info_init;

	  (** 2.0 - Trying to expand successors *)
	  let expand ({Candidate.graph = cur_gra; Candidate.g = cur_g;})
				 (info:graph_info) =
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
	  		let neig_info = Opened { parent		= Some (cur_gra, info);
	  								 g			= neig_g;
	  								 f			= neig_f; } in
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
	  (** 1.2 - Retreive steps if candidate is goal *)
	  let rec aux rep ratio =
		let cdt = BatHeap.find_min !candidates in
		let cdt_graph = cdt.Candidate.graph in
		candidates := BatHeap.del_min !candidates;
		let rep = EventHandler.tick_report
					rep (cdt.Candidate.f - cdt.Candidate.g)
					(BatHeap.size !candidates + 1) (Hashtbl.length infos) in
		let ratio =
		  let ff = float_of_int cdt.Candidate.f in
		  let fg = float_of_int cdt.Candidate.g in
		  let ratio' = fg /. ff in
		  if ratio' > ratio then (
			EventHandler.pushq (EventHandler.Progress ratio');
			ratio')
		  else
			ratio
		in
		match Hashtbl.find infos cdt_graph with
		| Opened info when Graph.equal cdt_graph gra_goal
		  -> EventHandler.finalize_report
			   rep (retreive_steps cdt_graph info)
		| Opened info
		  -> let as_closed = Closed info in
			 Hashtbl.replace infos cdt_graph as_closed;
			 expand cdt info;
			 aux rep ratio
		| _
		  -> aux rep ratio
	  in  (** 1. END *)
	  try
		let rep = aux (EventHandler.new_report he_init) 0. in
		EventHandler.pushq (EventHandler.Success rep);
	  with
	  | Invalid_argument(_) ->
		 Printf.eprintf "AStar: NOT SOLVED\n%!";
		 ()
  end
