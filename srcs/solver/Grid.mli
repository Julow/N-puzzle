(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   Grid.mli                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 14:20:12 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/29 09:55:28 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type matrix = int array array
type t = matrix * int

module Heuristic : (GenericInterfaces.HEURISTIC
					with type elt := t
					with type fn = t -> int
					with type maker = int -> t -> int
				   )

val bit_per_piv_component : int

(* Perf critical *)
val pivxy				: int -> int * int
val pivv				: int * int -> int
val copy_mat			: matrix -> matrix
val copy				: t -> t
val copy_swap			: t -> int * int -> t
val iter_cells			: matrix -> (int -> int -> int -> int -> unit) -> unit

(* Perf critical - Required by pathfinder *)
val cost				: t -> t -> int
val equal				: t -> t -> bool
val successors			: t -> t list

(* Conversion *)
val transposition_toreal : (int array) ref
val transposition_toabstract : (int array) ref
val init_transp_tables	: int -> unit
val to_real				: t -> t
val to_abstract			: t -> t
val of_cgrid			: Npuzzle.t -> t

(* Misc *)
val find				: matrix -> int -> int * int
val zero_coords			: int -> int * int
val is_solvable			: t -> bool

val goal				: int -> t
val generate			: int -> bool -> int -> t
val to_filename			: matrix -> string

(* Printing *)
val print				: t -> unit
val print_real_to_abst	: t -> unit
val print_abst_to_real	: t -> unit
