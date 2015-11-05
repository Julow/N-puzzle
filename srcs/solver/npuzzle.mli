(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   npuzzle.mli                                        :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/11/05 11:39:55 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/05 11:39:56 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t

(* return initial grid size *)
val get_size : t -> int

(* retrieve a value from the initial grid *)
val get : t -> int -> int ->int
