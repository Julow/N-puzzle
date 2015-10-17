(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   Grid.mli                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 14:20:12 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/17 16:51:58 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t = (int array) array

module type HEURISTIC =
  sig
	val calc        : t	-> int
  end

(* Perf critical *)
val equal			: t -> t -> bool
val copy			: t -> t
val swap			: t -> int * int -> int * int -> unit
val find			: t -> int -> int * int

(* Iteration *)
val iter_cells		: t -> (int -> int -> int -> int -> unit) -> unit

(* Conversion *)
val init_transp_tables	: int -> unit
val to_real			: t -> t
val to_abstract		: t -> t
val of_cgrid		: Npuzzle.t -> t
							 
(* Printing *)
val print			: t -> unit

(* Misc *)
val goal			: int -> t
