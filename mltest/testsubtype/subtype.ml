(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   subtype.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/18 13:09:04 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/19 15:14:17 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module GenericInterfaces =
  struct(* FILE ml *)
	module type ORDEREDTYPE =
	  sig
		type t
		val compare : t -> t -> int
	  end

	module type HEPATHFINDER =
	  sig
		type graph
		val solve : graph -> graph -> (graph -> int) -> graph list
	  end

	module type PATHFINDER_GRAPH =
	  sig
		type t
		val cost		: t -> t -> int
		val equal		: t -> t -> bool
		val successors	: t -> t list
	  end

	module type MAKE_HEPATHFINDER =
	  functor (Graph : PATHFINDER_GRAPH) ->
	  HEPATHFINDER with type graph := Graph.t
  end(* END OF FILE ml *)

module Grid =
  struct(* FILE ml *)
	type t = int array array * int

	(* Perf critical *)
	let pivxy piv =
	  piv land 0xFF, piv lsr 8

	let pivv x y =
	  x + y lsl 8

	let copy_mat mat =
	  Array.map (fun line -> Array.copy line) mat

	let copy (mat, piv) =
	  copy_mat mat, piv

	let copy_swap (mat, piv) (dx, dy) =
	  let mat' = copy_mat mat in
	  let x0, y0 = pivxy piv in
	  let v0 = mat'.(y0).(x0) in
	  let x, y = x0 + dx, y0 + dy in
	  mat'.(y0).(x0) <- mat'.(y0).(x0);
	  mat'.(y).(x) <- v0;
	  mat', pivv x y


	(* Required by pathfinder *)
	let cost _ _ =
	  1

	let equal (gra, piva) (grb, pivb) =
	  piva = pivb && gra = grb

	let successors ((mat, piv) as gr) =
	  let w = Array.length mat in
	  let x0, y0 = pivxy piv in
	  let dirs = [(1, 0); (0, 1); (-1, 0); (0, -1)] in

	  let is_in_bounds x y =
		if x < 0 || y < 0 || x >= w || y >= w
		then false
		else true
	  in
	  let rec foreach_dirs dirs acc =
		match dirs with
		| (dx, dy) as dt::tl when is_in_bounds (dx + x0) (dy + y0)	->
		   foreach_dirs tl (copy_swap gr dt::acc)
		| _::tl                             	                  	->
		   foreach_dirs tl acc
		| _                                                   		->
		   acc
	  in
	  foreach_dirs dirs []


  end(* END OF FILE ml *)





module type IDASTAR =
  sig(* FILE mli *)
	(* include GenericInterfaces.HEPATHFINDER *)
	module Make : GenericInterfaces.MAKE_HEPATHFINDER

  end(* END OF FILE mli *)


module IDAStar : IDASTAR =
  struct(* FILE ml *)

	module Make : GenericInterfaces.MAKE_HEPATHFINDER =
	  functor (Graph : GenericInterfaces.PATHFINDER_GRAPH) ->
	  struct

		type graph = Graph.t
		(* 	module type STATE = *)
		(* 	  sig *)
		(* 		type t = { *)
		(* 			graph	: graph; *)
		(* 			g		: int; *)
		(* 			h		: int; *)
		(* 		  } *)
		(* 		val compare : t -> t -> int *)
		(* 	  end *)
		(* 	module State : STATE = *)
		(* 	  struct *)
		(* 		type t = { *)
		(* 			graph	: graph; *)
		(* 			g		: int; *)
		(* 			h		: int; *)
		(* 		  } *)
		(* 		let compare a b = *)
		(* 		  (a.g + a.h) - (b.g + b.h) *)
		(* 	  end *)

		let solve grainit gragoal he =

		  let rec search gra g threshold =
		  	let f = g + (he gra) in
		  	if f > threshold then
		  	  f
		  	else if Graph.equal gra gragoal then
		  	  42
		  	else
		  	  min_successor gra g threshold
		  and min_successor gra g threshold =
		  	let rec aux successors decr =
		  	  match successors with
		  	  | hd::tl			->
		  		 let v = search hd (g + (Graph.cost gra hd)) threshold in
		  		 if v = 42
		  		 then 42
		  		 else aux tl (min v decr)
		  	  | _				-> decr
		  	in
		  	aux (Graph.successors gra) max_int
		  in

		  let rec aux threshold =
		  	let threshold' = search grainit 0 threshold in
		  	if threshold' = 42
		  	then ()
		  	else aux threshold'
		  in
		  aux (he grainit);
		  []

	  end

  end(* END OF FILE ml *)

(* module GridIDAStar = IDAStar.Make(Grid) *)
module GridIDAStar : (GenericInterfaces.HEPATHFINDER
					  with type graph := Grid.t) = IDAStar.Make(Grid)
