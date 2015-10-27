(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDBHeuristic.ml                      :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 07:52:31 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/27 08:33:46 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

let mirror_pos field w =
  let last = w - 1 in
  for i = 0 to w * w - 1 do
	let old = field.(i) in
	let x = old mod w in
	let y = old / w in
	let i' = last - y + (last - x) * w in
	field.(i) <- i';
  done;
  ()

let calc dbs fields (mat, piv) =
  let ndb = Array.length dbs.DisjointPatternDB.dbs in
  let w = dbs.DisjointPatternDB.dbs.(0).DisjointPatternDB.grid_w in
  assert(ndb = Array.length fields);
  DisjointPatternDB.retreive_dbs_pos
	mat dbs.DisjointPatternDB.ownerships fields;
  let rec aux i acc =
	if i < ndb then (
	  let db = dbs.DisjointPatternDB.dbs.(i) in
	  let field = fields.(i) in
	  let h = DisjointPatternDB.get
				db.DisjointPatternDB.data
				(DisjointPatternDB.index_of_pos db field)
	  in
	  mirror_pos field w;
	  let h' = DisjointPatternDB.get
				 db.DisjointPatternDB.data
				 (DisjointPatternDB.index_of_pos db field)
	  in
	  aux (i + 1) (max h h')
	)
	else acc
  in
  aux 0 0
