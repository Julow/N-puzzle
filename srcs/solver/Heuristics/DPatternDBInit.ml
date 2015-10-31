(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DPatternDBInit.ml                                  :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 17:05:57 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/31 12:41:05 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

include DPatternDB

(** 3.1.1 Build a grid with uninvolved cells at -1 *)
let goal_pattern db =
  let (mat, piv) as initgra = Grid.goal db.grid_w in
  let x0, y0 = Grid.pivxy piv in
  let aux _ x y v =
	try
	  ignore(List.find (fun v' -> v = v') db.nbrs)
	with
	| Not_found ->
	   if x = x0 && y = y0
	   then mat.(y).(x) <- -2
	   else mat.(y).(x) <- -1
  in
  Grid.iter_cells mat aux;
  initgra

let fill_datas (dbs:t) =
  (** 3.1 Foreach database *)
  (** 3.2 Try to load database from file *)
  (** 3.3 Else create database and export it to file *)
  let fill_data dbid (db:db) =
	let (mat, _) as goalpattern = goal_pattern db in
	let fname = Grid.to_filename mat in
	let data = (
	  try
		let ichan = open_in_bin fname in
		Printf.eprintf "File \"%s\" found\n%!" fname;
		let data = (Marshal.from_channel ichan : bytes) in

		close_in ichan;
		data
	  with
	  | _ ->
		 Printf.eprintf "File \"%s\" not found/loadable\n%!" fname;
		 let data = DPatternDBCompute.build dbs.ownerships db goalpattern dbid in
		 let ochan = open_out_bin fname in
		 Printf.eprintf "saving to file \"%s\"\n%!" fname;
		 Printf.eprintf "length = %d\n%!" (Bytes.length data);
		 Marshal.to_channel ochan data [];
		 close_out ochan;
		 data
	) in
	{db with data = data}
  in
  Array.mapi fill_data dbs.dbs

(** 1.3.2 Save 'paddings' inside bitfield *)
let build_paddings w ncell_pat =
  let ncell = w * w in
  let nbytes = fact_div ncell (ncell - ncell_pat) in
  let a = Array.make ncell_pat 42 in
  let rec aux i nelt pad =
	if i < ncell_pat
	then (let nelt' = nelt - 1 in
		  a.(i) <- pad;
		  assert(pad > 0);
		  aux (i + 1) nelt' (pad / nelt'))
  in
  aux 0 ncell (nbytes / ncell);
  a

let init_pattern_structure grid =
  let w = Array.length grid in
  let dbs = ref [] in
  (** 1.1 Init pattern structures *)
  (** 1.2 Fill .nbrs and increase .n_nbrs *)
  let aux i x y v =
	if v >= 0 then
	  try
		let db = List.find (fun db -> db.input_id = v) !dbs in
		let db' = {
			db with
			nbrs		= i::db.nbrs;
			n_nbrs		= db.n_nbrs + 1;
		  } in
		let f db'' = if db''.input_id = v then db' else db'' in
		dbs := List.map f !dbs

	  with
	  | Not_found	->
		 let db = {
			 grid_w		= w;
			 input_id	= v;
			 nbrs		= [i];
			 n_nbrs		= 1;
			 data		= "";
			 paddings	= [||];} in
		 dbs := db::!dbs
  in
  Grid.iter_cells grid aux;
  (** 1.3 Finalize and reorder patterns *)
  let aux db =
	let rev_nbrs = List.rev db.nbrs in
	{db with
	  nbrs				= rev_nbrs;
	  paddings			= build_paddings w db.n_nbrs;}
  in
  List.rev_map aux !dbs

(** 2.1 Builds ownerships table *)
let build_ownerships dbs_a =
  assert(Array.length dbs_a > 0);
  let w = dbs_a.(0).grid_w in
  let ncell = w * w in
  let a = Array.make ncell (-1, -1) in
  let foreachdb i db =
	let foreachcell i' cell =
	  a.(cell) <- (i, i');
	in
	List.iteri foreachcell db.nbrs;
  in
  Array.iteri foreachdb dbs_a;
  a

(** 2.2 Builds ownerships table *)
let build_mirror_ownerships dbs_a =
  assert(Array.length dbs_a > 0);
  let w = dbs_a.(0).grid_w in
  let last = w - 1 in
  let ncell = w * w in
  let a = Array.make ncell (-1, -1) in
  let foreachdb i db =
	let foreachcell i' cell =
	  let x = cell mod w in
	  let y = cell / w in
	  let cell' = last - y + (last - x) * w in
	  a.(cell') <- (i, i');
	in
	List.iteri foreachcell db.nbrs;
  in
  Array.iteri foreachdb dbs_a;
  a

(** 1. Parse/alloc/fill all patterns meta-data *)
(** 2. Build patterns holder *)
(** 3. Fill patterns data *)
let build grid =
  let empty_dbs = Array.of_list (init_pattern_structure grid) in
  let holder = {
	  dbs				= empty_dbs;
	  ownerships		= build_ownerships empty_dbs;
	  mirror_ownerships	= build_mirror_ownerships empty_dbs;
	} in
  let holder = {
	  holder with
	  dbs				= fill_datas holder; }
  in
  (* print holder; *)
  holder

(* ************************************************************************** *)
