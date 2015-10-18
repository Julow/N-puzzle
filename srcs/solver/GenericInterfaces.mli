(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   GenericInterfaces.mli                              :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/18 15:36:53 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/18 15:37:38 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module type HEURISTIC =
  sig
	type elt
	val calc    : elt->     int
  end

module type ORDEREDTYPE =
  sig
	type t
	val compare : t -> t -> int
  end
