(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DisjointPatternDB.ml                               :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/22 09:56:27 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/27 15:51:06 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type db = {
	grid_w				: int;
	input_id			: int;
	nbrs				: int list;
	n_nbrs				: int;
	paddings			: int array;
	mirror				: int array;
	data				: bytes;
  }

type t = {
	dbs					: db array;
	ownerships			: (int * int) array;
	mirror_ownerships	: (int * int) array;
  }

(* ************************************************************************** *)

let rec fact_div x y =
  if x <= y then 1 else x * fact_div (x - 1) y

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

let mirror w i =
  let last = w - 1 in
  let x = last - i mod w in
  let y = last - i / w in
  y + x * w

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

(* ********************************** *)
(* Modulation *)
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
  done;
  ()

(* Demodulation *)
let retreive_pos_of_indices field =
  let last = Array.length field - 1 in
  for i = last downto 1 do
	for j = i - 1 downto 0 do
	  let v = field.(i) in
	  let v' = field.(j) in
	  if v' <= v
	  then (field.(i) <- field.(i) + 1)
	done;
	assert(field.(i) >= 0);
	assert(field.(i) < 16);
  done

(* ********************************** *)
(* Modulation *)
let index_of_pos db field =
  let s = Array.length field in
  (* Array.iter (fun v->Printf.eprintf "%2d %!" v) field; Printf.eprintf "\n%!"; *)
  retreive_indices_of_pos field;
  (* Array.iter (fun v->Printf.eprintf "%2d " v) field; *)
  (* Printf.eprintf "\n"; Printf.eprintf "\n%!"; *)
  assert(s = (Array.length db.paddings));
  let rec aux i acc =
	(* Printf.eprintf "Hello i(%d) s()\n%!" i; *)
	if i < s
	then aux (i + 1) (acc + field.(i) * db.paddings.(i))
	else acc
  in
  aux 0 0

(* Demodulation *)
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

(* ********************************** *)
(* Modulation *)
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

let retreive_db_pos mat ownerships dbid field =
  let aux i _ _ v =
	if v >= 0
	then (let (dbid', cid) = ownerships.(v) in
		  if dbid' = dbid
		  then field.(cid) <- i)
  in
  Grid.iter_cells mat aux;
  ()

(* Demodulation *)
let retreive_mat_of_indexpiv i piv ownerships db field mat =
  retreive_indices_of_index field i db.paddings;
  (*  Array.iter (fun v->Printf.eprintf "%2d %!" v) field; Printf.eprintf "\n%!"; *)
  retreive_pos_of_indices field;
  (*  Array.iter (fun v->Printf.eprintf "%2d %!" v) field; Printf.eprintf "\n%!"; *)
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

let get data i =
  int_of_char (Bytes.get data i)

let set data i v =
  Bytes.set data i (char_of_int v);
  ()

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

let warn dbid db ncell nbytes goalpattern =
  Printf.eprintf "********************************************************\n%!";
  Printf.eprintf "FILLING DB ** nb(%d) ** cells(%d/%d) ** nbytes(%9d) **\n%!"
				 dbid db.n_nbrs ncell nbytes;
  Grid.print goalpattern;
  print_one db;
  Printf.eprintf "********************************************************\n%!"

module Hash =
  struct
	type t = int
	(* TODO, HEAVY TESTS ON OPERATORS PRIORITY *)

	(** Required by hmap functor *)
	let equal a b =
	  a land 0x00FF_FFFF_FFFF = b land 0x00FF_FFFF_FFFF

	(** Required by batheap functor *)
	let compare a b =
	  a lsr (32 + 8) - b lsr (32 + 8)

	let make g piv i =
	  g lsl (32 + 8) + piv lsl 32 + i

	let disass s =
	  s lsr (32 + 8), s lsr 32 land 0xFF, s land 0xFFFFFFFF

	let hash i =
	  i

  end

module HHashtbl = Hashtbl.Make(Hash)
module HBatHeap = BatHeap.Make(Hash)

let report g q h count nbytes prev t sz_qelt sz_helt =
  let lq = float (HBatHeap.size !q) /. 1_000_000. in
  let lh = float (HHashtbl.length h) /. 1_000_000. in
  let c = float !count /. 1_000_000. in
  let perc = (float !count) /. (float nbytes) *. 100. in
  let dt_c = float (!count - !prev) in
  let t' = Unix.gettimeofday () in
  let dt_t = t' -. !t in
  let eltps = dt_c /. dt_t in
  let eltph = eltps *. 3600. in
  let percph = eltph /. (float nbytes) *. 100. in
  Printf.eprintf "g(%2d) q(%9.6fm/%8.2fMB) h(%9.6fm/%8.2fMB)"
				 g lq (lq *. sz_qelt) lh (lh *. sz_helt);
  Printf.eprintf " count(%10.6fm %5.2f%% %.1fpph)\n%!"
				 c perc percph;
  t := t';
  prev := !count


(**
 ** I: Computed index for a maximum of 8 tiles pattern (29bits required)
 ** 	ie : 28 < log2(16!/8!) < 29
 ** P: Pivot coords
 ** G: Number of moves
 ** 0: Unused (Zero)
 ** 543210 76543210  76543210 76543210  76543210 76543210 76543210 76543210
 ** ______ ________  ________ ________  ________ ________ ________ ________
 ** 000000 00000000  GGGGGGGG PPPPPPPP  IIIIIIII IIIIIIII IIIIIIII IIIIIIII
 *)


(** 3.2.1 Fill pattern database with retrograde BFS search *)
let build_pdb ownerships db ((goalmat, piv) as goalpattern) dbid =
  let ncell = db.grid_w * db.grid_w in
  let nbytes = fact_div ncell (ncell - db.n_nbrs) in
  warn dbid db ncell nbytes goalpattern;
  let field = Array.make db.n_nbrs 42 in

  let mat = Grid.copy_mat goalmat in
  let data = alloc_data db.grid_w db.n_nbrs in
  let count = ref 0 in
  (* <Debug> *)
  let prev = ref (-1) in
  let sz_qelt = float ((1 + 2 + 1) * 8) in
  let sz_helt = float ((1 + 1) * 8) in
  let t = ref (Unix.gettimeofday ()) in
  let loops = ref 0 in
  let prevg = ref (-1) in
  (* </Debug> *)

  retreive_db_pos mat ownerships dbid field;
  let hash = Hash.make 0 piv (index_of_pos db field) in


  let q = ref (HBatHeap.insert HBatHeap.empty hash) in
  let h = HHashtbl.create 150_000_000 in
  HHashtbl.add h hash ();

  let rec aux () =
	if !count < nbytes then (
	  let g, piv, i = Hash.disass (HBatHeap.find_min !q) in
	  let x0, y0 = Grid.pivxy piv in
	  let v = get data i in

	  q := HBatHeap.del_min !q;
	  retreive_mat_of_indexpiv i piv ownerships db field mat;


	  loops := !loops + 1;
	  if !loops mod 50000 = 0 then (
		report g q h count nbytes prev t sz_qelt sz_helt;
	  );
	  if g != !prevg && g > 12 then (
		Printf.eprintf "old g was %d \n%!" !prevg;
		let oldhlen = HHashtbl.length h in
		let g_kept = g - 1 in

		let collect k _ _ =
		  let g, _, _ = Hash.disass k in
		  if g < g_kept then
			HHashtbl.remove h k;
		  ()
		in
		HHashtbl.fold collect h ();
		let gained = oldhlen - HHashtbl.length h in
		Printf.eprintf "Removed %d nodes\n%!" gained;

		report g q h count nbytes prev t sz_qelt sz_helt;
		prevg := g;
		if gained > 2_000_000 then (
		  Printf.eprintf "Gc\n%!";
		  Gc.compact ();
		  Printf.eprintf "Gc done\n%!";
		)
	  );
	  if v = 255 then (
		set data i g;
		count := !count + 1;
	  );

	  let rec aux' = function
		| (mat', piv')::tl
		  -> retreive_db_pos mat' ownerships dbid field;
			 let i' = index_of_pos db field in
			 let g' = if mat'.(y0).(x0) >= 0
					  then g + 1
					  else g
			 in
			 let hash = Hash.make g' piv' i' in
			 if not (HHashtbl.mem h hash) then (
			   q := HBatHeap.insert !q hash;
			   HHashtbl.add h hash ();
			 );
			 aux' tl
		| _
		  -> ()
	  in
	  aux' (Grid.successors (mat, piv));
	  aux ()
	)
  in
  aux ();
  data


let fill_datas (dbs:t) =
  (** 3.0 Foreach database *)
  (** 3.1 Try to load database from file *)
  (** 3.2 Else create database and export it to file *)
  let fill_data dbid (db:db) =
	let (mat, _) as goalpattern = goal_pattern db in
	let fname = Grid.to_filename mat in
	let data = (
	  try
		let ichan = open_in_bin fname in
		Printf.eprintf "File \"%s\" found\n%!" fname;
		let data = (Marshal.from_channel ichan : bytes) in
		Printf.eprintf "data read: %d\n%!" (Bytes.length data);

		close_in ichan;
		data
	  with
	  | _ ->
		 Printf.eprintf "File \"%s\" not found/loadable\n%!" fname;
		 let data = build_pdb dbs.ownerships db goalpattern dbid in
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
			 data		= "";
			 mirror		= [||];
			 paddings	= [||];} in
		 dbs := db::!dbs
  in
  Grid.iter_cells grid aux;
  (** 1.3 Finalize and reorder patterns *)
  let aux db =
	let rev_nbrs = List.rev db.nbrs in
	{db with
	  nbrs				= rev_nbrs;
	  mirror			= Array.map (mirror w) (Array.of_list rev_nbrs);
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
  print holder;
  holder
