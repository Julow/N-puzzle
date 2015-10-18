(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   subtype.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/18 13:09:04 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/18 15:11:52 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module GenericInterfaces = (* FILE *)
  struct

	module type HEURISTIC =
	  sig
		type t
		val calc		: t->		int
	  end

  end

module Grid = (* FILE *)
  struct

	type t = (int array) array
	module type HEURISTIC =
	  sig
		include GenericInterfaces.HEURISTIC with type t := t
	  end

		(* ... *)
  end

module GridHeuristics = (* FILE *)
  struct
	module Manhattan : Grid.HEURISTIC =
	  struct
		type t = Grid.t
		let calc	gr =
		  42
	  end

	module Dijkstra : Grid.HEURISTIC =
	  struct
		type t = Grid.t
		let calc	gr =
		  0
	  end

	let l = [|
		("Manhattan", Manhattan.calc);
		("Dijkstra", Dijkstra.calc);
	   |]

  end

(* module type PATHFINDER = *)
(*   sig *)
(* 	type elt *)
(* 	val solve		: elt->		elt->	elt list *)
(*   end *)

(* module type MAKE_PATHFINDER = *)
(*   functor (He: GenericInterfaces.HEURISTIC) -> PATHFINDER *)


(* module AStar = *)
(*   struct *)

(* 	module Make: MAKE_PATHFINDER = *)
(* 	  functor (He: GenericInterfaces.HEURISTIC) -> *)
(* 	  struct *)
(* 		type elt = Grid.t *)
(* 		let solve grinit grgoal = *)
(* 		  [] *)
(* 	  end *)
(*   end *)

	(* let pathfinders = [||] *)
