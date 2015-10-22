(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDB.ml                               :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/22 09:56:27 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/22 13:27:58 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type bd = {
	grid_w			: int;
	input_id		: int;
	nbrs			: int list;
	n_nbrs			: int;
	data			: bytes;
	paddings		: int array;
  }

(* ************************************************************************** *)

let rec fact_div x y =
  if x <= y then 1 else x * fact_div (x - 1) y

let print dbs =
  Printf.eprintf "%d Databases\n%!" (Array.length dbs);
  let aux i db =
	let grid_size = db.grid_w * db.grid_w in
	let bytes = fact_div grid_size (grid_size - db.n_nbrs) in
	let bytes = (float bytes) /. 1000000. in
	Printf.eprintf "%d (was %d) (%6.2fBytes) %2d nbrs: %!"
				   i db.input_id bytes db.n_nbrs;
	let aux' nbr = Printf.eprintf "%-2d %!" nbr in
	List.iter aux' db.nbrs;
	Printf.eprintf "\n%!"
  in
  Array.iteri aux dbs

let rafine_indices raw =
  let last = Array.length raw - 1 in
  let a = Array.copy raw in
  for i = 0 to last do
	let v = a.(i) in
	for j = i + 1 to last do
	  let v' = a.(j) in
	  if v' > v
	  then (assert(v' > 0);
			a.(j) <- v' - 1)
	done
  done;
  a

let access raw_indices =
  let rafined_indices = rafine_indices raw_indices in

  Array.iter (fun v -> Printf.eprintf "%2d %!" v) raw_indices;
  Printf.eprintf "\n%!";
  Array.iter (fun v -> Printf.eprintf "%2d %!" v) rafined_indices;
  Printf.eprintf "\n%!";
  int_of_char '0'

(* ************************************************************************** *)

let build_data db =
  let (mat, _) as grid = Grid.goal db.grid_w in
  (** 2.1 Build a grid with uninvolved cells at -1 *)
  let aux i x y v =
	try
	  List.find (fun v' -> v = v') db.nbrs;
	  ()
	with
	| Not_found ->
	   mat.(y).(x) <- -1;
  in
  Grid.iter_cells mat aux;
  Grid.print grid;
  (* access [|1; 5; 6; 7; 2; 10; 54|]; *)
  db
(* let cell_in_pattern = Array.make (db.w * db.w) false in *)
(* List.iter (fun v -> cell_in_pattern.(v) <- true) cell_in_pattern; *)




(** 1.3.2 Build 'paddings' table inside bitfield *)
let build_paddings w n =
  let n_cell = w * w in
  let bytes = fact_div n_cell (n_cell - n) in
  let a = Array.make (n_cell - n) 0 in
  let rec aux i nelt pad =
	if i < n
	then (let nelt' = nelt - 1 in
		  a.(i) <- pad;
		  assert(pad > 0);
		  aux (i + 1) nelt' (pad / nelt'))
	else assert(pad = 0)
  in
  aux 0 n_cell (bytes / n_cell);
  a

(** 1.3.1 Alloc bitfield *)
let alloc_data w n =
  let n_cell = w * w in
  let bytes = fact_div n_cell (n_cell - n) in
  Bytes.make bytes '0'

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
  (** 1.3 Finalize and reorder patterns *)
  let aux db =
	assert(db.n_nbrs > 2);
	{db with
	  nbrs = List.rev db.nbrs;
	  data = alloc_data w db.n_nbrs;
	  paddings = build_paddings w db.n_nbrs;}
  in
  List.rev_map aux !dbs

(** 1. Parse/alloc/fill all patterns meta-data *)
(** 2. Fill patterns data *)
let build grid =
  let empty_dbs = Array.of_list (init_pattern_structure grid) in
  print empty_dbs;
  Array.map build_data empty_dbs
