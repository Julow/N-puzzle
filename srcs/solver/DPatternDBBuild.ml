(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DPatternDBBuild.ml                                 :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 17:05:48 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/27 17:05:52 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

include DPatternDB

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


let build ownerships db ((goalmat, piv) as goalpattern) dbid =
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
