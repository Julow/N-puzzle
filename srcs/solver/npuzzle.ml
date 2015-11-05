(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   npuzzle.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/11/03 16:42:23 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/11/05 11:38:10 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t

external _get_size : t -> int = "solver_hook_get_size"

external _get : t -> int -> int -> int = "solver_hook_get"

(* TODO: get_algo (VARIANT) *)
(* TODO: get_heuristic (VARIANT) *)

let get_size = _get_size
let get = _get
