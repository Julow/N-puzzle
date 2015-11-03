(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   ManhattanDistanceHeuristic.ml                      :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/29 13:38:16 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/03 17:59:48 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

let calc (mat, piv) =
  let x0, y0 = Grid.pivxy piv in
  let s = Array.length mat in
  let rec foreach_line y acc =
	let rec foreach_cell x acc =
	  if x == s then
		acc
	  else if y = y0 && x = x0 then
		foreach_cell (x + 1) acc
	  else (
		let v = mat.(y).(x) in
		let dstx = v mod s in
		let dsty = v / s in
		let dx = abs(x - dstx) in
		let dy = abs(y - dsty) in
		foreach_cell (x + 1) (acc + dx + dy)
	  )
	in
	if y == s
	then acc
	else foreach_line (y + 1) (foreach_cell 0 acc)
  in
  foreach_line 0 0

(* ************************************************************************** *)

let make _ : Grid.Heuristic.fn =
  calc

(* ************************************************************************** *)
