(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   GenericInterfaces.mli                              :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/18 15:36:53 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/29 14:54:21 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module type HEURISTIC =
  sig
	type elt
	type fn = elt -> int
	type maker = int -> fn
  end

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
	val cost        : t -> t -> int
	val equal       : t -> t -> bool
	val successors  : t -> t list
	val print		: t -> unit
  end

module type MAKE_HEPATHFINDER =
  functor (Graph : PATHFINDER_GRAPH) ->
  HEPATHFINDER with type graph := Graph.t
