(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   GridHeuristics.ml                                  :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 17:10:40 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/28 14:51:14 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Manhattan : Grid.HEURISTIC =
  struct
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

  end

module Dijkstra : Grid.HEURISTIC =
  struct
	let calc _ =
	  42

  end


	(*
module LinearConflict : Grid.HEURISTIC =
  struct
	let calc (mat, piv) =
	  let w = Array.length mat in

	  let perline y acc =
		if y >= w then
		  acc
		else (
		  let percell x acc =
			let v = mat.(y).(x) in
			if v / w = y
			then percell (x + 1) v::acc
			else percell (x + 1) acc
		  in
		  let rev_rightline = percell 0 0 in
		  perline (y + 1) acc
		)
	  in

  end
 *)
