(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   subtype.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/18 13:09:04 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/18 17:26:23 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module GenericInterfaces = (* FILE *)
  struct
	module type ORDEREDTYPE =
	  sig
		type t
		val compare : t -> t -> int
	  end

	module type HEURISTIC =
	  sig
		type elt
		val calc	: elt->		int
	  end

	module type HEURISTIC_PATHFINDER_STATE =
	  sig
		type graph
		type t = {
			graph		: graph;
			g			: int;
			h			: int;
		  }
		include ORDEREDTYPE
				with type t := t
	  end
	module type HEURISTIC_PATHFINDER =
	  sig
		type graph
		val solve		: graph -> graph -> (graph -> int) -> graph list
	  end

  end


module Grid = (* FILE *)
  struct

	type t = (int array) array
	module type HEURISTIC =
	  sig
		include GenericInterfaces.HEURISTIC
				with type elt := t
	  end

	module type HEURISTIC_PATHFINDER =
	  sig
		include GenericInterfaces.HEURISTIC_PATHFINDER
				with type graph := t
									 (* with type State.t = int *)
	  end
		(* ... *)
  end

module type TRY =
  sig
	include GenericInterfaces.HEURISTIC_PATHFINDER_STATE
			with type graph := Grid.t
  end

module Try : TRY =
  struct
	type t = {
		graph		: Grid.t;
		g			: int;
		h			: int;
	  }
	let compare a b =
	  (a.g + a.h) - (b.g + b.h)
  end



module GridHeuristics = (* FILE *)
  struct
	module Manhattan : Grid.HEURISTIC =
	  struct
		let calc	gr =
		  let s = Array.length gr in
		  let rec foreach_line y acc =
			let rec foreach_cell x acc =
			  if x == s
			  then acc
			  else (
				let v = gr.(y).(x) in
				let dstx = v mod s in
				let dsty = v / s in
				let dx = abs (x - dstx) in
				let dy = abs (y - dsty) in
				foreach_cell (x + 1) (acc + dx + dy))
			in
			if y == s
			then acc
			else foreach_line (y + 1) (foreach_cell 0 acc)
		  in
		  foreach_line 0 0
	  end

	module Dijkstra : Grid.HEURISTIC =
	  struct
		let calc	gr =
		  0
	  end

	let l = [|
		("Manhattan", Manhattan.calc);
		("Dijkstra", Dijkstra.calc);
	   |]

  end


(* module type MAKE_HEURISTIC_PATHFINDER = *)
(* functor (He: GenericInterfaces.HEURISTIC) -> HEURISTIC_PATHFINDER *)

(* module type MAKE_PATHFINDER = *)
(*   functor (He: GenericInterfaces.HEURISTIC) -> PATHFINDER *)


module AStar : Grid.HEURISTIC_PATHFINDER =
  struct
	(* module State = *)
	(*   struct *)
	(* 	type t = { *)
	(* 		graph		: Grid.t; *)
	(* 		g			: int; *)
	(* 		h			: int; *)
	(* 	  } *)
	(* 	(\* include ORDEREDTYPE *\) *)
	(* 			(\* with type t := t *\) *)
	(*   end *)
	let solve grinit grgoal f =
	  []
  end
	(* 	module Make: MAKE_PATHFINDER = *)
	(* 	  functor (He: GenericInterfaces.HEURISTIC) -> *)
	(* 	  struct *)
	(* 		type elt = Grid.t *)
	(* 		let solve grinit grgoal = *)
	(* 		  [] *)
	(* 	  end *)
	(*   end *)

	(* let pathfinders = [||] *)
