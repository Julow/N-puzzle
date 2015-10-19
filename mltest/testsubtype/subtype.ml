(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   subtype.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/18 13:09:04 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/19 13:11:36 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module GenericInterfaces =
  struct(* FILE ml *)
	module type ORDEREDTYPE =
	  sig
		type t
		val compare : t -> t -> int
	  end
	module type PATHFINDER =
	  sig
		type graph
		val solve : graph -> graph -> graph list
	  end

	module type HEURISTIC_PATHFINDER =
	  sig
		include PATHFINDER
		val solve : graph -> graph -> (graph -> int) -> graph list

		module type STATE =
		  sig
		  	type t = {
		  		graph	: graph;
		  		g		: int;
		  		h		: int;
		  	  }
			include ORDEREDTYPE
					with type t := t
		  end
		(* module State : STATE *)
	  end
  end(* END OF FILE ml *)

module Grid =
  struct(* FILE ml *)
	type t = (int array) array
	module type HEURISTIC_PATHFINDER =
	  sig
		include GenericInterfaces.HEURISTIC_PATHFINDER
				with type graph := t
	  end
  end(* END OF FILE ml *)

module type ASTAR =
  sig(* FILE mli *)
	include Grid.HEURISTIC_PATHFINDER

  end(* END OF FILE mli *)


module AStar : ASTAR =
  struct(* FILE ml *)
	type graph = Grid.t
	module type STATE =
	  sig
		type t = {
			graph	: graph;
			g		: int;
			h		: int;
		  }
		val compare : t -> t -> int
	  end
	module State : STATE =
	  struct
		type t = {
			graph	: graph;
			g		: int;
			h		: int;
		  }
		let compare a b =
		  (a.g + a.h) - (b.g + b.h)
	  end

	let solve (grinit:graph) grgoal he =
	  []

  end(* END OF FILE ml *)
