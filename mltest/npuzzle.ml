(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   npuzzle.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 09:40:19 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/18 13:46:25 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

(* State representation as grid, g so far, h current *)
module type STATE =
  sig
	type t = {
		grid : Grid.t;
		g : int;
		h : int;
	  }
	val create	: Grid.t -> int -> int -> t
	val print	: t -> unit
	val compare	: t -> t -> int
  end

module State : STATE =
  (* module State : (STATE with type t = t) = *)
  struct
	type t = {
		grid : Grid.t;
		g : int;
		h : int;
	  }
	let print st =
	  Printf.eprintf "State: g(%3d) h(%3d)\n%!" st.g st.h;
	  Grid.print st.grid;
	  ()
		
	let create grid g h =
	  {grid = grid; g = g; h = h}
	let compare (a:t) (b:t) =
	  (a.g + a.h) - (b.g + b.h)
  end

(* BatHeap of states *)
(* module StateBatHeap : (BATHEAP with type elem := State.t) = MakeBatHeap(State) *)
module StateBatHeap = MakeBatHeap(State)

module type SOLVER =
  sig
	val solve		: int -> Grid.t -> bool
  end

module MakeAStar (He: HEURISTIC) :SOLVER =
  struct

	type data = {
		width 			: int;
		total 			: int;
		goal 			: Grid.t;
		zero_abs_alias	: int; (* Pivot index *)
		mutable closed	: (Grid.t, unit) Hashtbl.t;
		mutable opened	: StateBatHeap.t;
	  }

	let is_goal s (d:data) =
	  d.goal = s.State.grid

	let create_info (w:int) (i_gr:Grid.t) =
	  let total = w * w in
	  let goal = Grid.build_goal w in
	  let zero_abs_alias = !Grid.transp_table_ptr_toabs.(0) in
	  Printf.printf "ALIAS: %d \n%!" zero_abs_alias;
	  
	  let closed = Hashtbl.create 10000 in
	  let i_st = State.create i_gr 0 (He.calc i_gr) in
	  let opened = StateBatHeap.insert StateBatHeap.empty i_st in
	  {width = w ; total = total ; goal = goal ; zero_abs_alias = zero_abs_alias
	   ; closed = closed; opened = opened}
		

	let solve (w:int) (i_gr:Grid.t) =
	  Printf.eprintf "SOLVE START...............................................\n%!";
	  let i = create_info w i_gr in

	  let expand cur =
		let x0, y0 = Grid.find cur.State.grid i.width i.zero_abs_alias in
		let try_add x y =
		  let grid = Grid.copy cur.State.grid in
		  Grid.swap grid (x0, y0) (x, y);
		  try
			Hashtbl.find i.closed grid
		  with
		  | Not_found		->
			 let h = He.calc grid in
			 let st = State.create grid (cur.State.g + 1) h in
			 if (st.State.h < 0)
			 then State.print st;
			 i.opened <- StateBatHeap.insert i.opened st;
			 ()
		in
		let is_in_bounds x y =
		  if x < 0 || y < 0 || x >= i.width || y >= i.width
		  then false
		  else true
		in
		let dirs = [(1, 0); (0, 1); (-1, 0); (0, -1)] in
		let rec foreach_dirs dirs =
		  match dirs with
		  | (dx, dy)::tl when is_in_bounds (dx + x0) (dy + y0)	->
			 try_add (dx + x0) (dy + y0);
			 foreach_dirs tl
		  | _::tl												->
			 foreach_dirs tl
		  | _													-> ()
		in
		foreach_dirs dirs;
		()
	  in

	  let rec aux () =
		let cur = StateBatHeap.find_min i.opened in
		i.opened <- StateBatHeap.del_min i.opened;
		Hashtbl.add i.closed cur.State.grid ();
		if is_goal cur i
		then (Printf.printf "SOLVED\n%!";
			  State.print cur;
			  Grid.print_abs_to_snail cur.State.grid;
			  true)
		else (expand cur;
			  aux ())
	  in
	  try
		aux ()
	  with
	  | Invalid_argument("find_min") -> false
  end

(* module ManhattanAStar = MakeAStar(DijkstraHeuristic) *)
module ManhattanAStar = MakeAStar(ManhattanHeuristic)

let scanGrid chan g s =
  let rec line y =
	let rec col x =
	  if x < s then
		(let v = (Scanf.fscanf chan " %u " (fun x _ -> x))() in
		 g.(y).(x) <- v;
		 col (x + 1))
	in
	if y < s then
	  (col 0;
	   line (y + 1))
  in
  line 0

let () =
  (* let fname = "lol3almost.np" in *)
  
  let fname = "lol3_2.np" in
  (* let fname = "lol3.np" in *)
  let chan = open_in fname in
  Printf.eprintf "opened: %s\n%!" fname;
  Printf.eprintf "%s\n%!" (input_line chan);
  let size = (Scanf.fscanf chan "%d\n" (fun x _ -> x))() in
  Printf.eprintf "size: %d\n%!" size;
  Grid.init_transp_tables size; (* EARLY *)
  let grid = Array.make_matrix size size 42 in
  scanGrid chan grid size;
  close_in chan;

  Printf.printf "PARSED MATRIX (PRINT RAW):\n%!";
  Grid.print grid;
  let grid = Grid.snail_to_absolute grid in
  Printf.printf "PARSED MATRIX TO ABS (PRINT RAW):\n%!";
  Grid.print grid;
  
  Printf.printf "Solved: %b\n%!" (ManhattanAStar.solve size grid); 
  ()
