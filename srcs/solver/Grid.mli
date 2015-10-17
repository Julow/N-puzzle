(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   Grid.mli                                           :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 14:20:12 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/17 15:32:54 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t = (int array) array

val iter_cells		: t -> (int -> int -> int -> int -> unit) -> unit
val print			: t -> unit
val equal			: t -> t -> bool
val copy			: t -> t
val goal			: int -> t
val of_cgrid		: Npuzzle.t -> t

val to_real			: t -> t
val to_abstract		: t -> t
val init_transp_tables	: int -> unit
