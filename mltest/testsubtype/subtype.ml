(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   subtype.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/18 13:09:04 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/19 14:36:45 by ngoguey          ###   ########.fr       *)
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
	  end
  end(* END OF FILE ml *)

module Grid =
  struct(* FILE ml *)
	type t = int array array * int

	let pivxy piv =
	  piv land 0xFF, piv lsr 8

	let pivv x y =
	  x + y lsl 8

	let equal (gra, piva) (grb, pivb) =
	  piva = pivb && gra = grb

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

	let cost _ _ =
	  1

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





	(* module type ASTAR = *)
	(*   sig(\* FILE mli *\) *)
	(* 	include Grid.HEURISTIC_PATHFINDER *)

	(*   end(\* END OF FILE mli *\) *)


	(* module AStar : ASTAR = *)
	(*   struct(\* FILE ml *\) *)
	(* 	type graph = Grid.t *)
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

	(* 	let solve (grinit:graph) grgoal he = *)
	(* 	  [] *)

	(*   end(\* END OF FILE ml *\) *)

	(* module type IDASTAR = *)
	(*   sig(\* FILE mli *\) *)
	(* 	include Grid.HEURISTIC_PATHFINDER *)

	(*   end(\* END OF FILE mli *\) *)


	(* let equal gra grb = *)
	(*   gra = grb *)

	(* let cost gra grb = *)
	(*   1 *)

	(* let successors gr = *)
	(*   [] *)

	(* module IDAStar : IDASTAR = *)
	(*   struct(\* FILE ml *\) *)
	(* 	type graph = Grid.t *)

	(* 	let solve grinit grgoal he = *)
	(* 	  (\* let bound = he grinit in *\) *)

	(* 	  let rec search gr g bound = *)
	(* 		let f = g + (he gr) in *)
	(* 		if f > bound then *)
	(* 		  f *)
	(* 		else if equal gr grgoal then *)
	(* 		  42 *)
	(* 		else *)
	(* 		  min_successor gr g bound *)
	(* 	  and min_successor gr g bound = *)
	(* 		let rec aux successors decr = *)
	(* 		  match successors with *)
	(* 		  | hd::tl			-> *)
	(* 			 let v = search hd (g + (cost gr hd)) bound in *)
	(* 			 if v = 42 *)
	(* 			 then 42 *)
	(* 			 else aux tl (min v decr) *)
	(* 		  | _				-> decr *)
	(* 		in *)
	(* 		aux (successors gr) max_int *)

	(* 	  in *)

	(* 	  let rec aux bound = *)
	(* 		let threshold = search grinit 0 bound in *)
	(* 		if threshold = 42 *)
	(* 		then () *)
	(* 		else aux threshold *)
	(* 	  in *)
	(* 	  aux (he grinit); *)

	(* 	  [] *)

	(*   end(\* END OF FILE ml *\) *)
