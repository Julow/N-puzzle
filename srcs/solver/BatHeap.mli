(*
 * Heap -- binomial heaps
 * Copyright (C) 2011  Batteries Included Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version,
 * with the special exception on linking described in file LICENSE.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *)

module type ORDEREDTYPE =
  sig
	type t
	val compare : t -> t -> int
  end

(** The result of {!Make} *)
module type H =
sig
  type elem
  (** Type of elements of the heap *)
  type t
  (** Type of the heap *)
  val empty     : t
  (** See {!BatHeap.empty}. *)
  val size      : t -> int
  (** See {!BatHeap.size}. *)
  val insert    : t -> elem -> t
  (** See {!BatHeap.add}. *)
  val add       : elem -> t -> t
  (** See {!BatHeap.insert}. *)
  val merge     : t -> t -> t
  (** See {!BatHeap.merge}. *)
  val find_min  : t -> elem
  (** See {!BatHeap.find_min}. *)
  val del_min   : t -> t
  (** See {!BatHeap.del_min}. *)
  val of_list   : elem list -> t
  (** See {!BatHeap.of_list}. *)
  val to_list   : t -> elem list
  (** See {!BatHeap.to_list}. *)
end

module Make (Ord : ORDEREDTYPE) : H with type elem = Ord.t
  (** Functorized heaps over arbitrary orderings. All the functions have
      the same complexity as the non-functorized versions. *)
