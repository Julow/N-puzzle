(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   DPatternDBCompute.ml                               :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/27 18:52:13 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/01 15:46:02 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

include DPatternDB

(**
 ** I: Computed index for a maximum of 8 tiles pattern (29bits required)
 ** 	ie : 28 < log2(16!/8!) < 29
 ** P: Pivot coords
 ** G: Number of moves
 ** 0: Unused (Zeroes)
 ** 543210 76543210  76543210 76543210  76543210 76543210 76543210 76543210
 ** ______ ________  ________ ________  ________ ________ ________ ________
 ** 000000 00000000  GGGGGGGG PPPPPPPP  IIIIIIII IIIIIIII IIIIIIII IIIIIIII
 *)

module Hash =
  struct
	type t = int
	(* TODO: HEAVY TESTS ON OPERATORS PRIORITY *)

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

module CurHashtbl = Hashtbl.Make(Hash)
module CurQueue = BatHeap.Make(Hash)

(* ************************************************************************** *)
(* DEBUG *)

let prev = ref (-1)
let sz_qelt = float ((1 + 2 + 1) * 8)
let sz_helt = float ((1 + 1) * 8)
let t = ref (Unix.gettimeofday ())
let loops = ref 0
let prevg = ref (-1)

let report (ncell, nbytes, count, q, h) =
  let lq = float (CurQueue.size !q) /. 1_000_000. in
  let lh = float (CurHashtbl.length h) /. 1_000_000. in
  let c = float !count /. 1_000_000. in
  let perc = (float !count) /. (float nbytes) *. 100. in
  let dt_c = float (!count - !prev) in
  let t' = Unix.gettimeofday () in
  let dt_t = t' -. !t in
  let eltps = dt_c /. dt_t in
  let eltph = eltps *. 3600. in
  let percph = eltph /. (float nbytes) *. 100. in
  Printf.eprintf "g(%2d) q(%9.6fm/%8.2fMB) h(%9.6fm/%8.2fMB)"
				 !prevg lq (lq *. sz_qelt) lh (lh *. sz_helt);
  Printf.eprintf " count(%10.6fm %5.2f%% %.1fpph)\n%!"
				 c perc percph;
  t := t';
  prev := !count

let warn dbid db ncell nbytes goalpattern =
  Printf.eprintf "********************************************************\n%!";
  Printf.eprintf "FILLING DB ** nb(%d) ** cells(%d/%d) ** nbytes(%9d) **\n%!"
				 dbid db.n_nbrs ncell nbytes;
  Grid.print goalpattern;
  print_one db;
  Printf.eprintf "********************************************************\n%!"

(* ************************************************************************** *)
(* LOOP-INIT TIME *)

let alloc_data w n =
  let n_cell = w * w in
  let bytes = fact_div n_cell (n_cell - n) in
  Bytes.make bytes (char_of_int 255)

let init_mem_fields mat db =
  Array.make db.n_nbrs 42,
  Grid.copy_mat mat,
  alloc_data db.grid_w db.n_nbrs

let init_containers (mat, piv) db ownerships dbid field =
  retreive_db_pos mat ownerships dbid field;
  let hash = Hash.make 0 piv (index_of_pos db field) in
  let q = ref (CurQueue.insert CurQueue.empty hash) in
  let h = CurHashtbl.create 150_000_000 in
  CurHashtbl.add h hash ();
  q, h

(* ************************************************************************** *)
(* LOOP TIME *)

let garbage_collect h g debug_dat =
  Printf.eprintf "old g was %d \n%!" !prevg;
  let oldhlen = CurHashtbl.length h in
  let g_kept = g - 1 in

  let collect k _ _ =
	let g, _, _ = Hash.disass k in
	if g < g_kept then
	  CurHashtbl.remove h k;
	()
  in
  CurHashtbl.fold collect h ();
  let gained = oldhlen - CurHashtbl.length h in
  Printf.eprintf "Removed %d nodes\n%!" gained;

  report debug_dat;
  prevg := g;
  if gained > 2_000_000 then (
	Printf.eprintf "Gc\n%!";
	Gc.full_major ();
	Printf.eprintf "Gc done\n%!";
  )

let build ownerships db ((goalmat, piv) as goalpattern) dbid =
  let ncell = db.grid_w * db.grid_w in
  let nbytes = fact_div ncell (ncell - db.n_nbrs) in
  let n_ignoredcells = ncell - db.n_nbrs in
  let nreachable = if n_ignoredcells = 1 then
					 nbytes / 2
				   else if n_ignoredcells = 2 then
					 nbytes - fact_div db.n_nbrs 1 * 10
				   else
					 nbytes
  in
  warn dbid db ncell nbytes goalpattern;

  let field, mat, data = init_mem_fields goalmat db in
  let count = ref 0 in
  let q, h = init_containers goalpattern db ownerships dbid field in

  let debug_dat = ncell, nbytes, count, q, h in

  let rec aux () =
	if !count < nreachable then (
	  if CurQueue.size !q = 0 then report debug_dat;
	  let g, piv, i = Hash.disass (CurQueue.find_min !q) in
	  let x0, y0 = Grid.pivxy piv in
	  let v = get data i in

	  q := CurQueue.del_min !q;

	  loops := !loops + 1;
	  if !loops mod 50000 = 0 then report debug_dat;
	  if g <> !prevg && g > 12 then garbage_collect h g debug_dat;
	  if v = 255 then (set data i g;
					   count := !count + 1;);

	  let rec aux' = function
		| (mat', piv')::tl
		  -> retreive_db_pos mat' ownerships dbid field;
			 let i' = index_of_pos db field in
			 let g' = if mat'.(y0).(x0) >= 0
					  then g + 1
					  else g
			 in
			 let hash = Hash.make g' piv' i' in
			 if not (CurHashtbl.mem h hash) then (
			   q := CurQueue.insert !q hash;
			   CurHashtbl.add h hash ();
			 );
			 aux' tl
		| _
		  -> ()
	  in
	  retreive_mat_of_indexpiv i piv ownerships db field mat;
	  aux' (Grid.successors (mat, piv));
	  aux ()
	)
  in
  aux ();
  data

	(* ************************************************************************** *)
