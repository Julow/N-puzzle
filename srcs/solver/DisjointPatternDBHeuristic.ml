(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDBHeuristic.ml                      :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 07:52:31 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/27 13:14:19 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

let mirrorf w i =
  let last = w - 1 in
  let x = last - i mod w in
  let y = last - i / w in
  y + x * w


let mirror_pos fields fields' w mat dbs =
  let last = w - 1 in
  let aux' dbid field =
	let mirror = dbs.DisjointPatternDB.dbs.(dbid).DisjointPatternDB.mirror in
	let aux i v =
	  let x = v mod w in
	  let y = v / w in
	  let i' = last - y + (last - x) * w in
	  (* let v' = mat.(y').(x') in *)
	  (* Printf.eprintf "%2d  %2d to %2d (%2d)\n%!" i v i' (x' + y' * 4); *)
	  Printf.eprintf "(%d%d)at ->(%d, %d) "
					 dbid i
					 (v mod w) (v / w);
	  let x', y' = Grid.find mat mirror.(i) in
	  Printf.eprintf "Mirrori(%2d)%! at (%d, %d) final(%d)"
					 mirror.(i)
					 x' y'
					 (mirrorf w (x' + y' * w))
	  ;
		(* Printf.eprintf "mirror(%d, %d)->\n%!" x' y'; *)

	  Printf.eprintf "\n%!";
	  fields'.(dbid).(i) <- mirrorf w (x' + y' * w)
	  (* fields'.(dbid).(i) <- i' *)
	in
	Array.iteri aux field;
  in
  Array.iteri aux' fields;
  ()

let calc dbs fields fields' (mat, piv) =
  let ndb = Array.length dbs.DisjointPatternDB.dbs in
  let w = dbs.DisjointPatternDB.dbs.(0).DisjointPatternDB.grid_w in
  Grid.print (mat, piv);
  assert(ndb = Array.length fields);
  assert(ndb = Array.length fields');
  DisjointPatternDB.retreive_dbs_pos
	mat dbs.DisjointPatternDB.ownerships fields;
  mirror_pos fields fields' w mat dbs;
  let rec aux flds i acc =
  	if i < ndb then (
  	  let db = dbs.DisjointPatternDB.dbs.(i) in
  	  let fld = flds.(i) in
  	  let h = DisjointPatternDB.get
  				db.DisjointPatternDB.data
  				(DisjointPatternDB.index_of_pos db fld)
  	  in
  	  aux fields (i + 1) (acc + h)
  	)
  	else acc
  in
  let h = aux fields 0 0 in
  let h' = aux fields' 0 0 in
  Printf.eprintf "%d vs %d\n%!" h h';
  Printf.eprintf "\n%!";
  (* max h h' *)
  h
