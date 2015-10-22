(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDB.ml                               :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/22 09:56:27 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/22 11:56:59 by ngoguey          ###   ########.fr       *)
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

let build_data db =
  db

let alloc_data w n =
  let n_cell = w * w in
  let bytes = fact_div n_cell (n_cell - n) in
  Printf.eprintf "%d bytes!\n%!" bytes;
  Bytes.make bytes '0'

let build_paddings w n =
  let n_cell = w * w in
  let bytes = fact_div n_cell (n_cell - n) in
  let a = Array.make (n_cell - n) 0 in
  let rec aux i nelt pad =
	let nelt' = nelt - 1 in
	Printf.eprintf "%d = pad%d\n%!" i pad;
	a.(i) <- pad;
	aux (i + 1) nelt' (pad / nelt')
  in
  aux 0 n_cell (bytes / n_cell)


let parse_grid grid =
  let w = Array.length grid in
  let dbs = ref [] in

  let aux i x y v =
	Printf.eprintf "aux %d   %d\n%!" i v;
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
  List.rev_map (fun db -> assert(db.n_nbrs > 2);
						  {db with nbrs = List.rev db.nbrs;
								   data = alloc_data w db.n_nbrs;
								   paddings = build_paddings w db.n_nbrs;}) !dbs

let build grid =
  let empty_dbs = Array.of_list (parse_grid grid) in
  print empty_dbs;
  Array.map build_data empty_dbs
