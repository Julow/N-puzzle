(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDBHeuristic.ml                      :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 07:52:31 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/27 10:33:27 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

let mirror_pos fields fields' w =
  let last = w - 1 in
  let aux' dbid field =
	let aux i v =
	  let old = field.(i) in
	  let x = old mod w in
	  let y = old / w in
	  let i' = last - y + (last - x) * w in
	  fields'.(dbid).(i) <- i'
	in
	Array.iteri aux field;
  in
  Array.iteri aux' fields;
  ()

let calc dbs fields fields' (mat, _) =
  let ndb = Array.length dbs.DisjointPatternDB.dbs in
  let w = dbs.DisjointPatternDB.dbs.(0).DisjointPatternDB.grid_w in
  assert(ndb = Array.length fields);
  assert(ndb = Array.length fields');
  DisjointPatternDB.retreive_dbs_pos
	mat dbs.DisjointPatternDB.ownerships fields;
  mirror_pos fields fields' w;
  let rec aux i acc =
	if i < ndb then (
	  let db = dbs.DisjointPatternDB.dbs.(i) in
	  let field = fields.(i) in
	  let field' = fields'.(i) in
	  let h = DisjointPatternDB.get
				db.DisjointPatternDB.data
				(DisjointPatternDB.index_of_pos db field)
	  in
	  (* let h' = DisjointPatternDB.get *)
	  (* 			 db.DisjointPatternDB.data *)
	  (* 			 (DisjointPatternDB.index_of_pos db field') *)
	  (* in *)
	  aux (i + 1) (acc + h)
	  (* aux (i + 1) (acc + max h h') *)
	)
	else acc
  in
  aux 0 0
