(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DPatternDBHeuristic.ml                             :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 17:05:46 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/31 12:40:44 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

let calc dbs fields mirror_fields (mat, piv) =
  let ndb = Array.length dbs.DPatternDB.dbs in
  DPatternDB.retreive_dbs_pos
	mat dbs.DPatternDB.ownerships fields
	dbs.DPatternDB.mirror_ownerships mirror_fields;
  let rec aux flds i acc =
  	if i < ndb then (
  	  let db = dbs.DPatternDB.dbs.(i) in
  	  let fld = flds.(i) in
	  let dati = DPatternDB.index_of_pos db fld in
  	  let h = DPatternDB.get db.DPatternDB.data dati in
  	  aux flds (i + 1) (acc + h)
  	)
  	else acc
  in
  let h = aux fields 0 0 in
  let h' = aux mirror_fields 0 0 in
  max h h'

(* ************************************************************************** *)

let make pat w =
  let t = Unix.gettimeofday () in
  let dbs = DPatternDBInit.build pat in
  let fields =
	Array.map (fun db ->Array.make db.DPatternDB.n_nbrs 42)
			  dbs.DPatternDB.dbs
  in
  let fields' =
	Array.map (fun db ->Array.make db.DPatternDB.n_nbrs 42)
			  dbs.DPatternDB.dbs
  in
  calc dbs fields fields'

(* ************************************************************************** *)
