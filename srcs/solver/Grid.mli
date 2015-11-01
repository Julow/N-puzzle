(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   Grid.mli                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 14:20:12 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/01 15:27:02 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type matrix = int array array
type t = matrix * int

module Heuristic : (GenericInterfaces.HEURISTIC
					with type elt := t
					with type fn = t -> int
					with type maker = int -> t -> int
				   )

(* Perf critical *)
val pivxy				: int -> int * int
val pivv				: int * int -> int
val copy_mat			: matrix -> matrix
val copy				: t -> t
val copy_swap			: t -> int * int -> t

(* Perf critical - Required by pathfinder *)
val cost				: t -> t -> int
val equal				: t -> t -> bool
val successors			: t -> t list

(* Iteration *)
val iter_cells			: matrix -> (int -> int -> int -> int -> unit) -> unit
val find				: matrix -> int -> int * int

(* Conversion TODO: PARTIALLY MOVE TO CPP *)
val init_transp_tables	: int -> unit
val to_real				: t -> t
val to_abstract			: t -> t
val of_cgrid			: Npuzzle.t -> t

(* Printing *)
val print				: t -> unit
val print_real_to_abst	: t -> unit
val print_abst_to_real	: t -> unit

(* Misc *)
val goal				: int -> t
val to_filename			: matrix -> string
