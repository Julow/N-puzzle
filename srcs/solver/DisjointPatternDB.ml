(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDB.ml                               :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/22 09:56:27 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/22 16:44:18 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type db = {
	grid_w			: int;
	input_id		: int;
	nbrs			: int list;
	n_nbrs			: int;
	paddings		: int array;
	data			: bytes;
  }

type t = {
	dbs				: db array;
	(* grid_w			: int; *)
	cell_ownership	: (int * int) array;
  }

(* ************************************************************************** *)

let rec fact_div x y =
  if x <= y then 1 else x * fact_div (x - 1) y

let print_one (db:db) =
  let grid_size = db.grid_w * db.grid_w in
  let bytes = fact_div grid_size (grid_size - db.n_nbrs) in
  let bytes = (float bytes) /. 1000000. in
  Printf.eprintf "(was %d) (%10.6fMBytes) %2d nbrs: %!"
				 db.input_id bytes db.n_nbrs;
  let aux' nbr = Printf.eprintf "%-2d %!" nbr in
  List.iter aux' db.nbrs;
  Printf.eprintf "\n\t %d paddings: %!" (Array.length db.paddings);
  Array.iter aux' db.paddings;
  Printf.eprintf "\n%!"

let print dbs =
  Printf.eprintf "%d Databases\n%!" (Array.length dbs.dbs);
  Printf.eprintf "%6s: %!" "Cells";
  Array.iteri (fun i _ -> Printf.eprintf "%-3d %!" i) dbs.cell_ownership;
  Printf.eprintf "\n%!";
  Printf.eprintf "%6s: %!" "DBid";
  Array.iter (fun (i, _) -> Printf.eprintf "%-3d %!" i) dbs.cell_ownership;
  Printf.eprintf "\n%!";
  Printf.eprintf "%6s: %!" "NBid";
  Array.iter (fun (_, i) -> Printf.eprintf "%-3d %!" i) dbs.cell_ownership;
  Printf.eprintf "\n%!";
  Array.iter print_one dbs.dbs

(* ************************************************************************** *)

let refine_indices raw =
  let last = Array.length raw - 1 in
  let a = Array.copy raw in
  for i = 0 to last do
	let v = a.(i) in
	for j = i + 1 to last do
	  let v' = a.(j) in
	  (* Printf.eprintf "v'=%2d  max=%2d\n%!" v' (16 - 1 - j); *)
	  if v' > v
	  then (assert(v' > 0);
			a.(j) <- v' - 1)
	  else assert(v' <= 16 - 1 - j)
	done
  done;
  a

let index_of_rawindices db raw_indices =
  let rafined_indices = refine_indices raw_indices in
  (* Array.iter (fun v -> Printf.eprintf "%2d %!" v) raw_indices; *)
  (* Printf.eprintf "\n%!"; *)
  (* Array.iter (fun v -> Printf.eprintf "%2d %!" v) rafined_indices; *)
  (* Printf.eprintf "\n%!"; *)
  let s = Array.length raw_indices in
  (* Printf.eprintf "%d Array.length raw_indices \n%!" s; *)
  (* Printf.eprintf "%d Array.length db.paddings \n%!" (Array.length db.paddings); *)
  assert(s = (Array.length db.paddings));
  let rec aux i acc =
	if i < s
	then aux (i + 1) (acc + raw_indices.(i) * db.paddings.(i))
	else acc
  in
  aux 0 0

let allrawindices_of_matrix mat dbs =
  let aux dbid =
	Array.create dbs.dbs.(dbid).n_nbrs 42
  in
  let a = Array.init (Array.length dbs.dbs) aux in
  let ownership = dbs.cell_ownership in
  let aux i _ _ v =
	if v >= 0
	then (let (dbid, cid) = ownership.(v) in
		  a.(dbid).(cid) <- i)
  in
  Grid.iter_cells mat aux;
  a

let onerawindices_of_matrix mat dbs dbid =
  let a = Array.create dbs.dbs.(dbid).n_nbrs 42 in
  let ownership = dbs.cell_ownership in
  let aux i _ _ v =
	if v >= 0
	then (let (dbid', cid) = ownership.(v) in
		  if dbid' = dbid
		  then a.(cid) <- i)
  in
  Grid.iter_cells mat aux;
  a

(* let get dbs dbid raw_indices = *)
(*   let db = dbs.(dbid) in *)
(*   let i = index_of_rawindices db raw_indices in *)
(*   int_of_char (Bytes.get db.data i) *)

(* ************************************************************************** *)

let build_datas (dbs:t) =
  let build_data dbid (db:db) =
	let (mat, _) as grid = Grid.goal db.grid_w in
	(** 3.1 Build a grid with uninvolved cells at -1 *)
	let aux i x y v =
	  try
		ignore(List.find (fun v' -> v = v') db.nbrs)
	  with
	  | Not_found ->
		 mat.(y).(x) <- -1;
	in
	Grid.iter_cells mat aux;
	Grid.print grid;

	(* let allrawindices = allrawindices_of_matrix mat dbs in *)
	(* Array.iter (fun rawindices -> *)
	(* 			Printf.eprintf "SALUT %!"; *)
	(* 			Printf.eprintf "%d indices: %!" (Array.length rawindices); *)
	(* 			Array.iter (fun i -> *)
	(* 						Printf.eprintf "%3d %!" i; *)
	(* 					   ) rawindices; *)
	(* 			Printf.eprintf "\n%!"; *)
	(* 		   ) allrawindices; *)

	(* let rawindices = onerawindices_of_matrix mat dbs dbid in *)
	(* Printf.eprintf "BONJOUR %!"; *)
	(* Array.iter (fun i -> *)
	(* 			Printf.eprintf "%3d %!" i; *)
	(* 		   ) rawindices; *)
	(* Printf.eprintf "\n%!"; *)

	(* let i = index_of_rawindices db [|0; 1; 2; 3; 4; 5; 6; 7|] in *)
	(* let i = index_of_rawindices db [|15; 14; 13; 12; 11; 10; 9; 8|] in *)
	(* let i = index_of_rawindices db [|1; 5; 6; 7; 2; 10; 15; 14|] in *)
	(* Printf.eprintf "GOT i=%d\n%!" i; *)
	let ncell = db.grid_w * db.grid_w in
	let dat = db.data in
	let default = 255 in
	let tot = fact_div ncell (ncell - db.n_nbrs) in
	let q = Queue.create () in


	(* let rec aux inputed = *)
	(* 	if inputed < tot then ( *)
	(* 	  let state = Queue.pop q in *)

	(* 	) *)
	(* in *)
	(* Queue.push grid; *)
	(* aux 0; *)
	db
  in
  Array.mapi build_data dbs.dbs

(* let cell_in_pattern = Array.make (db.w * db.w) false in *)
(* List.iter (fun v -> cell_in_pattern.(v) <- true) cell_in_pattern; *)


(** 1.3.2 Build 'paddings' table inside bitfield *)
let build_paddings w ncell_pattern =
  let ncell = w * w in
  let bytes = fact_div ncell (ncell - ncell_pattern) in
  (* Printf.eprintf "ncell=%d  ncell_pattern=%d\n%!" ncell ncell_pattern; *)
  let a = Array.make ncell_pattern 42 in
  let rec aux i nelt pad =
	(* Printf.eprintf "i=%d  pad=%d\n%!" i pad; *)
	if i < ncell_pattern
	then (let nelt' = nelt - 1 in
		  a.(i) <- pad;
		  assert(pad > 0);
		  aux (i + 1) nelt' (pad / nelt'))
	else assert(pad = 0)
  in
  aux 0 ncell (bytes / ncell);
  a

(** 1.3.1 Alloc bitfield *)
let alloc_data w n =
  let n_cell = w * w in
  let bytes = fact_div n_cell (n_cell - n) in
  Bytes.make bytes (char_of_int 255)

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
			 data		= Bytes.empty;
			 paddings	= [||];} in
		 dbs := db::!dbs
  in
  Grid.iter_cells grid aux;
  assert(List.length !dbs > 0);
  (** 1.3 Finalize and reorder patterns *)
  let aux db =
	(* assert(db.n_nbrs > 0); *)
	{db with
	  nbrs = List.rev db.nbrs;
	  data = alloc_data w db.n_nbrs;
	  paddings = build_paddings w db.n_nbrs;}
  in
  List.rev_map aux !dbs


let build_ownerships empty_dbs =
  let w = empty_dbs.(0).grid_w in
  let ncell = w * w in
  let a = Array.make ncell (-1, -1) in
  let foreachdb i db =
	let foreachcell i' cell =
	  a.(cell) <- (i, i');
	in
	List.iteri foreachcell db.nbrs;
  in
  Array.iteri foreachdb empty_dbs;
  a

(** 1. Parse/alloc/fill all patterns meta-data *)
(** 2. Build patterns holder *)
(** 3. Fill patterns data *)
let build grid =
  let empty_dbs = Array.of_list (init_pattern_structure grid) in
  let holder = {
	  dbs				= empty_dbs;
	  cell_ownership	= build_ownerships empty_dbs;
	} in
  print holder;
  build_datas holder
