(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   npuzzle.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/11/03 16:42:23 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/11/03 16:46:34 by jaguillo         ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t

external _get_size : t -> int = "solver_hook_get_size"

external _get : t -> int -> int -> int = "solver_hook_get"

(* TODO: get_algo (VARIANT) *)
(* TODO: get_heuristic (VARIANT) *)

external _put_progress : t -> float -> unit = "solver_hook_put_progress"

external _put_step : t -> int array array -> unit = "solver_hook_put_step"

let get_size = _get_size
let get = _get
let put_progress = _put_progress
let put_step = _put_step
