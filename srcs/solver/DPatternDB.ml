(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DPatternDB.ml                                      :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 17:05:59 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/29 16:46:05 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type db = {
	grid_w				: int;
	input_id			: int;
	nbrs				: int list;
	n_nbrs				: int;
	paddings			: int array;
	data				: bytes;
  }

type t = {
	dbs					: db array;
	ownerships			: (int * int) array;
	mirror_ownerships	: (int * int) array;
  }

(* ************************************************************************** *)
(* MISC *)

let rec fact_div x y =
  if x <= y then 1 else x * fact_div (x - 1) y

let mirror w i =
  let last = w - 1 in
  let x = last - i mod w in
  let y = last - i / w in
  y + x * w

let get data i =
  int_of_char (Bytes.get data i)

let set data i v =
  Bytes.set data i (char_of_int v);
  ()

(* ************************************************************************** *)
(* DEBUG *)

let print_one (db:db) =
  let grid_size = db.grid_w * db.grid_w in
  let bytes = fact_div grid_size (grid_size - db.n_nbrs) in
  let bytes = (float bytes) /. 1000000. in
  let bytes' = Bytes.length db.data in
  let bytes' = (float bytes') /. 1000000. in
  Printf.eprintf "(was %d) (%10.6fMBytes/%10.6fM) %2d nbrs: %!"
				 db.input_id bytes bytes' db.n_nbrs;
  let aux' nbr = Printf.eprintf "%-2d %!" nbr in
  List.iter aux' db.nbrs;
  Printf.eprintf "\n\t %d paddings: %!" (Array.length db.paddings);
  Array.iter aux' db.paddings;
  Printf.eprintf "\n%!"

let print dbs =
  Printf.eprintf "%d Databases\n%!" (Array.length dbs.dbs);
  Printf.eprintf "%6s: %!" "Cells";
  Array.iteri (fun i _ -> Printf.eprintf "%-3d %!" i) dbs.ownerships;
  Printf.eprintf "\n%!";
  Printf.eprintf "%6s: %!" "DBid";
  Array.iter (fun (i, _) -> Printf.eprintf "%-3d %!" i) dbs.ownerships;
  Printf.eprintf "\n%!";
  Printf.eprintf "%6s: %!" "NBid";
  Array.iter (fun (_, i) -> Printf.eprintf "%-3d %!" i) dbs.ownerships;
  Printf.eprintf "\n%!";
  Array.iter print_one dbs.dbs

(* ************************************************************************** *)
(* CONVERSIONS *)

(** e.g. For a given pattern with 6 random cells in a 4*4 grid
 **		 0  1  2 -1
 **		 4  5 -1 -1
 **		 8 -1 -1 -1
 **		-1 -1 -1 -1
 **		Num cells:		6
 **		Database size:	16!/(16-6)! = 5765760B = 5.76MB
 **		**
 ** 	Cell index:				0		1		2		3		4		5
 **		Target-position: 		0		1		2		4		5		8
 **		Data offset:			360360	24024	1716	132		11		1
 **		Max index:				15		14		13		12		11		10
 ** With 6 current random positions
 **		-1 -1 -1  2
 **		-1  0  8 -1
 **		 1  4 -1 -1
 **		-1 -1  5 -1
 **		**
 ** 	Current position:		5		8		3		9		14		6
 **		Correction:				0		-1		0		-3		-4		-2
 **		Data index:				5		7		3		6		10		4
 **		Data offset:			1801800	168168	5148	792		110		4
 **		**
 **		Which gives:	db.data.(1976022) = HEURISTIC
 *)

(* ************************************************************************** *)
(* SOLVE-TIME CONVERSIONS *)
(* Matrix -> Positions [[-> Indices]] -> Index *)
let retreive_indices_of_pos field =
  let last = Array.length field - 1 in
  for i = last downto 1 do
	let v = field.(i) in
	let rec aux j acc =
	  if j < 0 then
		acc
	  else (
		let v' = field.(j) in
		if v' < v
		then aux (j - 1) (acc + 1)
		else aux (j - 1) acc
	  )
	in
	field.(i) <- field.(i) - aux (i - 1) 0;
	assert(field.(i) >= 0);
	assert(field.(i) < Array.length field * (Array.length field) - i);
  done;
  ()

(* Matrix -> Positions [[-> Indices -> Index]] *)
let index_of_pos db field =
  let s = Array.length field in
  (* Array.iter (fun v->Printf.eprintf "%2d" v) field; Printf.eprintf "\n%!"; *)
  retreive_indices_of_pos field;
  (* Array.iter (fun v->Printf.eprintf "%2d " v) field; *)
  assert(s = (Array.length db.paddings));
  let rec aux i acc =
	if i < s
	then aux (i + 1) (acc + field.(i) * db.paddings.(i))
	else acc
  in
  aux 0 0

(* Matrix [[-> Positions]] -> Indices -> Index *)
let retreive_dbs_pos mat ownerships fields mirror_ownerships mirror_fields =
  let w = Array.length mat in
  let aux i _ _ v =
	if v >= 0
	then (let (dbid, cid) = ownerships.(v) in
		  if dbid >= 0 && cid >= 0;
		  then fields.(dbid).(cid) <- i;
		  let (dbid, cid) = mirror_ownerships.(v) in
		  if dbid >= 0 && cid >= 0;
		  then mirror_fields.(dbid).(cid) <- mirror w i;
		  ()
		 )
  in
  Grid.iter_cells mat aux;
  ()

(* ************************************************************************** *)
(* DB_COMPUTE-TIME CONVERSIONS *)

(* Matrix [[-> Positions]] -> Indices -> Index *)
let retreive_db_pos mat ownerships dbid field =
  let aux i _ _ v =
	if v >= 0
	then (let (dbid', cid) = ownerships.(v) in
		  if dbid' = dbid
		  then field.(cid) <- i)
  in
  Grid.iter_cells mat aux;
  ()

(* ********************************** *)
(* Matrix <- [[Positions <-]] Indices <- Index *)
let retreive_pos_of_indices field =
  let last = Array.length field - 1 in
  for i = last downto 1 do
	let rec aux j v =
	  if j < 0 then
		v
	  else (
		let v' = field.(j) in
		if v' <= v
		then aux (j - 1) (v + 1)
		else aux (j - 1) v
	  )
	in
	field.(i) <- aux (i - 1) field.(i);
	assert(field.(i) >= 0);
	assert(field.(i) < Array.length field * (Array.length field));
  done;
  ()

(* Matrix <- Positions <- [[Indices <-]] Index *)
let retreive_indices_of_index field i paddings =
  let n = Array.length paddings in
  let rec aux j decr =
	if j < n then (
	  let pad = paddings.(j) in
	  field.(j) <- decr / pad;
	  aux (j + 1) (decr mod pad)
	)
	else assert(decr = 0)
  in
  aux 0 i;
  ()

(* [[Matrix <- Positions <- Indices <-]] Index *)
let retreive_mat_of_indexpiv i piv ownerships db field mat =
  retreive_indices_of_index field i db.paddings;
  retreive_pos_of_indices field;
  let w = Array.length mat in
  let last = w - 1 in
  for y = 0 to last do
	for x = 0 to last do
	  mat.(y).(x) <- -1;
	done;
  done;
  let x0, y0 = Grid.pivxy piv in
  mat.(y0).(x0) <- -2;
  let rec aux i l =
	match l with
	| hd::tl		-> let posi = field.(i) in
					   mat.(posi / w).(posi mod w) <- hd;
					   aux (i + 1) tl
	| _				-> ()
  in
  aux 0 db.nbrs;
  ()

(* ************************************************************************** *)
