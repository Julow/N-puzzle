(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDB.ml                               :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/22 09:56:27 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/24 16:03:41 by ngoguey          ###   ########.fr       *)
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
	ownerships		: (int * int) array;
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

let retreive_indices_of_pos field =
  let last = Array.length field - 1 in
  for i = last downto 1 do
	let v = field.(i) in
	for j = i - 1 downto 0 do
	  let v' = field.(j) in
	  if v' < v
	  then (field.(i) <- field.(i) - 1)
	done;
	assert(field.(i) >= 0);
	assert(field.(i) < 16 - i);
  done

let index_of_pos db field =
  let s = Array.length field in
  (* Array.iter (fun v->Printf.eprintf "%2d %!" v) field; Printf.eprintf "\n%!"; *)
  retreive_indices_of_pos field;
  (* Array.iter (fun v->Printf.eprintf "%2d " v) field; Printf.eprintf "\n"; Printf.eprintf "\n"; *)
  assert(s = (Array.length db.paddings));
  let rec aux i acc =
	if i < s
	then aux (i + 1) (acc + field.(i) * db.paddings.(i))
	else acc
  in
  aux 0 0

let retreive_dbs_pos mat ownerships fields =
  let aux i _ _ v =
	if v >= 0
	then (let (dbid, cid) = ownerships.(v) in
		  fields.(dbid).(cid) <- i)
  in
  Grid.iter_cells mat aux


let retreive_db_pos mat ownerships dbid field =
  let aux i _ _ v =
	if v >= 0
	then (let (dbid', cid) = ownerships.(v) in
		  if dbid' = dbid
		  then field.(cid) <- i)
  in
  Grid.iter_cells mat aux

let get data i =
  int_of_char (Bytes.get data i)

let set data i v =
  Bytes.set data i (char_of_int v)

(* ************************************************************************** *)

(** 3.0.0 Build a grid with uninvolved cells at -1 *)
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

(** 3.2.0 Alloc bytes for data *)
let alloc_data w n =
  let n_cell = w * w in
  let bytes = fact_div n_cell (n_cell - n) in
  Bytes.make bytes (char_of_int 255)

(** 3.2.1 Fill pattern database with retrograde BFS search*)
let build_pdb ownerships db goalpattern dbid =
  Printf.eprintf "FILLING DATABASE %d:********************************\n%!" dbid;
  Grid.print goalpattern;
  print_one db;
  Printf.eprintf "***************************************************\n%!";

  let ncell = db.grid_w * db.grid_w in
  let default = 255 in
  let tot = fact_div ncell (ncell - db.n_nbrs) in
  Printf.eprintf "Looking for %d nodes with bfs :(\n%!" tot;
  let indices_field = Array.make db.n_nbrs 42 in

  let data = alloc_data db.grid_w db.n_nbrs in

  let count = ref 0 in
  (* <Debug> *)
  let prev = ref (-1) in
  let sz_qelt = float ((16 + 1 + 1) * 8) in
  let sz_helt = float ((16 + 1) * 8) in
  let t = ref (Unix.gettimeofday ()) in
  (* </Debug> *)

  let q = Queue.create () in
  let h = Hashtbl.create 30_000_000 in
  Queue.push (goalpattern, 0) q;
  Hashtbl.add h goalpattern ();

  let rec aux () =
	if !count < tot then (
	  let (((mat, _) as state), g) = Queue.pop q in

	  (* <Debug> *)
	  let report () =
		let lq = float (Queue.length q) /. 1_000_000. in
		let lh = float (Hashtbl.length h) /. 1_000_000. in
		let c = float !count /. 1_000_000. in
		let perc = (float !count) /. (float tot) *. 100. in
		let dt_c = float (!count - !prev) in
		let t' = Unix.gettimeofday () in
		let dt_t = t' -. !t in
		let eltps = dt_c /. dt_t in
		let eltph = eltps *. 3600. in
		let percph = eltph /. (float tot) *. 100. in
		Printf.eprintf "g(%2d) q(%9.6fm/%8.2fMB) h(%9.6fm/%8.2fMB)"
					   g lq (lq *. sz_qelt) lh (lh *. sz_helt);
		Printf.eprintf " count(%10.6fm %5.2f%% %.1fpph)\n%!"
					   c perc percph;
		t := t';
		prev := !count
	  in
	  if (!count mod 5000 = 0) && (not (!count = !prev)) then report ();
	  (* </Debug> *)

	  retreive_db_pos mat ownerships dbid indices_field;
	  let i = index_of_pos db indices_field in
	  let v = get data i in
	  if v = default then (set data i g;
						   count := !count + 1;
						   if !count > tot - 5 then report ();
						  );
	  let rec aux' = function
		| ((mat', _) as state')::tl	->
		   if not (Hashtbl.mem h state') then (
			 Queue.push (state', g + 1) q;
			 Hashtbl.add h state' ()
		   );
		   aux' tl
		| _							-> ()
	  in
	  aux' (Grid.successors state);
	  aux ()
	)
  in
  aux ();
  Printf.eprintf "DONE for database %d*************************************\n%!" dbid;
  data


let fill_datas (dbs:t) =
  (** 3.0 Foreach database *)
  (** 3.1 Try to load database from file *)
  (** 3.2 Create database and export it to file *)
  let fill_data dbid (db:db) =
	let (mat, _) as goalpattern = goal_pattern db in
	let fname = Grid.to_filename mat in
	let data = (
	  try
		let ichan = open_in fname in
		Printf.eprintf "File \"%s\" found\n%!" fname;
		let data = (Marshal.from_channel ichan : bytes) in
		close_in ichan;
		data
	  with
	  | _ ->
		 Printf.eprintf "File \"%s\" not found\n%!" fname;
		 let data = build_pdb dbs.ownerships db goalpattern dbid in
		 let ochan = open_out fname in
		 Printf.eprintf "saving to file \"%s\"\n%!" fname;
		 Printf.eprintf "length = %d\n%!" (Bytes.length data);
		 Marshal.to_channel ochan db.data [];
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
	else assert(pad = 0)
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
			 data		= Bytes.empty;
			 paddings	= [||];} in
		 dbs := db::!dbs
  in
  Grid.iter_cells grid aux;
  (** 1.3 Finalize and reorder patterns *)
  let aux db =
	{db with
	  nbrs				= List.rev db.nbrs;
	  paddings			= build_paddings w db.n_nbrs;}
  in
  List.rev_map aux !dbs

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

(** 1. Parse/alloc/fill all patterns meta-data *)
(** 2. Build patterns holder *)
(** 3. Fill patterns data *)
let build grid =
  let empty_dbs = Array.of_list (init_pattern_structure grid) in
  let holder = {
	  dbs				= empty_dbs;
	  ownerships		= build_ownerships empty_dbs;
	} in
  print holder;
  fill_datas holder
