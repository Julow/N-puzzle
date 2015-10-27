(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDBHeuristic.ml                      :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 07:52:31 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/27 16:05:32 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

let calc dbs fields mirror_fields (mat, piv) =
  let ndb = Array.length dbs.DisjointPatternDB.dbs in
  let w = dbs.DisjointPatternDB.dbs.(0).DisjointPatternDB.grid_w in
  assert(ndb = Array.length fields);
  assert(ndb = Array.length mirror_fields);
  DisjointPatternDB.retreive_dbs_pos
	mat dbs.DisjointPatternDB.ownerships fields
	dbs.DisjointPatternDB.mirror_ownerships mirror_fields;
  let rec aux flds i acc =
  	if i < ndb then (
  	  let db = dbs.DisjointPatternDB.dbs.(i) in
  	  let fld = flds.(i) in
	  let dati = DisjointPatternDB.index_of_pos db fld in
  	  let h = DisjointPatternDB.get db.DisjointPatternDB.data dati in
  	  aux flds (i + 1) (acc + h)
  	)
  	else acc
  in
  let h = aux fields 0 0 in
  let h' = aux mirror_fields 0 0 in
  max h h'
