(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   npuzzle.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 09:40:19 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/16 18:06:30 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module type ORDEREDTYPE =
  sig
	type t
	val compare : t -> t -> int
  end

module type BATHEAP = sig
	type elem
	type t
	val empty     : t
	val size      : t -> int
	val insert    : t -> elem -> t
	val add       : elem -> t -> t
	val merge     : t -> t -> t
	val find_min  : t -> elem
	val del_min   : t -> t
	val of_list   : elem list -> t
	val to_list   : t -> elem list
	val elems     : t -> elem list
  end
(* 
module type MAKEBATHEAP =
  functor (Ord: ORDEREDTYPE) ->
  BATHEAP with type elem := Ord.t
 *)
module MakeBatHeap (Ord : ORDEREDTYPE) =
  (* module MakeBatHeap : MAKEBATHEAP =
functor (Ord: ORDEREDTYPE) -> *)
  struct
	type elem = Ord.t

	let ord_min x y =
      if Ord.compare x y <= 0 then x else y

	type bt = {
		rank : int ;
		root : Ord.t ;
		kids : bt list ;
	  }

	type t = {
		size : int ;
		data : bt list ;
		mind : Ord.t option ;
	  }

	let empty = { size = 0 ; data = [] ; mind = None }

	let size bh = bh.size

	let link bt1 bt2 =
      assert (bt1.rank = bt2.rank) ;
      let rank = bt1.rank + 1 in
      let leq = Ord.compare bt1.root bt2.root <= 0 in
      let root = if leq then bt1.root else bt2.root in
      let kids = if leq then bt2 :: bt1.kids else bt1 :: bt2.kids in
      { rank = rank ; root = root ; kids = kids }

	let rec add_tree t = function
      | [] -> [t]
      | (ut :: uts) as ts ->
		 assert (t.rank <= ut.rank) ;
		 if t.rank < ut.rank then t :: ts
		 else add_tree (link t ut) uts

	let insert bh x =
      let data = add_tree { rank = 0 ; root = x ; kids = [] } bh.data in
      let mind = match bh.mind with
		| None -> Some x
		| Some mind -> Some (ord_min x mind)
      in {
		  size = bh.size + 1 ; data = data ; mind = mind
		}

	let add x bh = insert bh x

	let rec merge_data ts1 ts2 = match ts1, ts2 with
      | _, [] -> ts1
      | [], _ -> ts2
      | t1 :: tss1, t2 :: tss2 ->
		 if t1.rank < t2.rank then
           t1 :: merge_data tss1 ts2
		 else if t1.rank > t2.rank then
           t2 :: merge_data ts1 tss2
		 else
           add_tree (link t1 t2) (merge_data tss1 tss2)

	let merge bh1 bh2 =
      let size = bh1.size + bh2.size in
      let data = merge_data bh1.data bh2.data in
      let mind = match bh1.mind, bh2.mind with
		| Some m1, Some m2 -> Some (ord_min m1 m2)
		| m, None | None, m -> m
      in
      { size = size ; data = data ; mind = mind }

	let find_min bh = match bh.mind with
      | None -> invalid_arg "find_min"
      | Some d -> d

	let rec find_min_tree ts k = match ts with
      | [] -> failwith "find_min_tree"
      | [t] -> k t
      | t :: ts ->
		 find_min_tree ts begin
						 fun u ->
						 if Ord.compare t.root u.root <= 0
						 then k t else k u
					   end

	let rec del_min_tree bts k = match bts with
      | [] -> invalid_arg "del_min"
      | [t] -> k t []
      | t :: ts ->
		 del_min_tree ts begin
						fun u uts ->
						if Ord.compare t.root u.root <= 0
						then k t ts
						else k u (t :: uts)
					  end

	let del_min bh =
      del_min_tree bh.data begin
					 fun bt data ->
					 let size = bh.size - 1 in
					 let data = merge_data (List.rev bt.kids) data in
					 let mind = if size = 0 then None else Some (find_min_tree data (fun t -> t)).root in
					 { size = size ; data = data ; mind = mind }
				   end

	let to_list bh =
      let rec aux acc bh =
		if size bh = 0 then acc else
          let m = find_min bh in
          let bh = del_min bh in
          aux (m :: acc) bh
      in
      List.rev (aux [] bh)

	let elems = to_list

	let of_list l = List.fold_left insert empty l

  end

	
(* let print bh =	
	let print_one bt lvl =
		Printf.eprintf "%s %u(%d)\n" (String.make(lvl * 4) '*') bt.rank bt.root
	in
	let rec foreach_t btl lvl = 
		match btl with
		| []		-> ()
		| hd::tl	->
			print_one hd lvl;
			foreach_t hd.kids (lvl + 1);
			foreach_t tl lvl
	in
	Printf.eprintf "Size: %u\n" bh.size;
	foreach_t bh.data 0
 *)

(* Grid representation as 2d array *)
module Grid = struct
	type t = (int array) array

	let transp_table_ptr_tosnail = ref [|42|]
	let transp_table_ptr_toabs = ref [|42|]

	let print g =
	  let s = Array.length g in
	  let print v =
		Printf.eprintf "%-2d %!" v
	  in
	  let rec line y =
		let rec cell x =
		  if x < s
		  then (print g.(y).(x);
				cell (x + 1))
		in
		if y < s
		then (cell 0;
			  Printf.eprintf "\n%!";
			  line (y + 1))
	  in
	  line 0

	let equal a b =
	  a = b

	let copy src =
	  Array.map (fun line -> Array.copy line) src

	let build_goal w =
	  let mat = (Array.make_matrix w w 0) in
	  let rec line y acc =
		let rec col x acc = 
		  if x < w then
			(mat.(y).(x) <- acc;
			 col (x + 1) (acc + 1))
		  else acc
		in
		if y < w then
		  line (y + 1) (col 0 acc);
	  in
	  line 0 0;
	  mat

	let find gr s v =
	  let rec line y =
		assert (y < s);
		let rec cell x =
		  if gr.(y).(x) = v then
			(x, y)
		  else if x = s - 1 then
			line (y + 1)
		  else
			cell (x + 1)
		in
		cell 0
	  in
	  line 0

	let swap g (xa, ya) (xb, yb) =
	  let va = g.(ya).(xa) in
	  g.(ya).(xa) <- g.(yb).(xb);
	  g.(yb).(xb) <- va

	let init_transp_tables w =
	  let a = Array.make (w * w) 42 in

	  let save x y v inset f =
		let i = x + y * w in
		if v == w * w
		then a.(i) <- 0
		else (a.(i) <- v;
			  f x y v inset)
	  in
	  
	  let rec inc_x x y v inset =
		let x = x + 1 in
		let maxx = w - 1 - inset in
		assert (x <= maxx);
		if x = maxx
		then save x y (v + 1) inset inc_y
		else save x y (v + 1) inset inc_x

	  and inc_y x y v inset =
		let y = y + 1 in
		let maxy = w - 1 - inset in
		assert (y <= maxy);
		if y = maxy
		then save x y (v + 1) inset dec_x
		else save x y (v + 1) inset inc_y

	  and dec_x x y v inset =
		let x = x - 1 in
		let minx = 0 + inset in
		assert (x >= minx);
		if x = minx
		then save x y (v + 1) inset dec_y
		else save x y (v + 1) inset dec_x

	  and dec_y x y v inset =
		let y = y - 1 in
		let miny = 1 + inset in
		assert (y >= miny);
		if y = miny
		then save x y (v + 1) (inset + 1) inc_x
		else save x y (v + 1) inset dec_y

	  in

	  let k_of_v a v =
	  	let k = ref 42 in
	  	Array.iteri (fun k' v' -> if v' = v then k := k') a;
	  	!k
	  in

	  save 0 0 1 0 inc_x;
	  transp_table_ptr_tosnail := a;
	  transp_table_ptr_toabs := Array.mapi (fun k _ -> k_of_v a k) a;
	  ()

		
	(* Absolute-coords matrix to Snail-coords matrix *)
	let absolute_to_snail abs_m =
	  let transp_a = !transp_table_ptr_tosnail in
	  let w = Array.length abs_m in
	  let snail_m = Array.make_matrix w w 0 in

	  let rec is_valid i =
		let x = i mod w in
		let y = i / w in

		if i = w * w
		then ()
		else save i x y
	  and save i x y =
		let cell_v = abs_m.(y).(x) in
		snail_m.(y).(x) <- transp_a.(cell_v);
		is_valid (i + 1)
	  in
	  save 0 0 0;
	  snail_m

	(* Snail-coords matrix to Absolute-coords matrix *)
	let snail_to_absolute snail_m =
	  let transp_a = !transp_table_ptr_toabs in
	  let w = Array.length snail_m in
	  let abs_m = Array.make_matrix w w 0 in

	  let rec is_valid i =
		let x = i mod w in
		let y = i / w in

		if i = w * w
		then ()
		else save i x y
	  and save i x y =
		let cell_v = snail_m.(y).(x) in
		abs_m.(y).(x) <- transp_a.(cell_v);
		is_valid (i + 1)
	  in
	  save 0 0 0;
	  abs_m

	let print_snail_to_abs g =
	  Printf.printf "SNAIL TO ABS:\n%!";
	  print (snail_to_absolute g)

	let print_abs_to_snail g =
	  Printf.printf "ABS TO SNAIL\n%!";
	  print (absolute_to_snail g)
  end

				
(* Heuristics *)
module type HEURISTIC =
  sig
	val calc      	: Grid.t	-> int
  end

module ManhattanHeuristic : HEURISTIC =
  struct
	let calc g =
	  let s = Array.length g in
	  let rec foreach_line y acc =
		let rec foreach_cell x acc =
		  if x == s
		  then acc
		  else (
			let v = g.(y).(x) in
			let dstx = v mod s in
			let dsty = v / s in
			let dx = abs(x - dstx) in
			let dy = abs(y - dsty) in
			foreach_cell (x + 1) (acc + dx + dy))
		in
		if y == s
		then acc
		else foreach_line (y + 1) (foreach_cell 0 acc)
	  in
	  foreach_line 0 0


  end

module DijkstraHeuristic : HEURISTIC =
  struct
	let calc g =
	  ignore(g);
	  0
  end

(* let tab = [|DijkstraHeuristic|] *)
	
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
		zero_abs_alias	: int;
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