(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   GridHeuristics.ml                                  :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 17:10:40 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/19 17:04:48 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module Manhattan : Grid.HEURISTIC =
  struct
	let calc (mat, _) =
	  let s = Array.length mat in
	  let rec foreach_line y acc =
		let rec foreach_cell x acc =
		  if x == s
		  then acc
		  else (
			let v = mat.(y).(x) in
			let dstx = v mod s in
			let dsty = v / s in
			let dx = abs(x - dstx) in
			let dy = abs(y - dsty) in
			foreach_cell (x + 1) (acc + dx + dy))
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
