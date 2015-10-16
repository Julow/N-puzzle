(* ************************************************************************** *)
(*																																						*)
(*																												:::			::::::::	 *)
(*	 npuzzle.ml																				 :+:			:+:		:+:	 *)
(*																										+:+ +:+				 +:+		 *)
(*	 By: ngoguey <ngoguey@student.42.fr>						+#+	+:+			 +#+				*)
(*																								+#+#+#+#+#+	 +#+					 *)
(*	 Created: 2015/10/14 13:06:34 by ngoguey					 #+#		#+#						 *)
(*   Updated: 2015/10/16 09:27:54 by ngoguey          ###   ########.fr       *)
(*																																						*)
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

	let print g =
	  let s = Array.length g in
	  let rec line y =
		let rec cell x =
		  if x < s
		  then (Printf.eprintf "%-2d %!" g.(y).(x);
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
				
	let zero g s =
	  let rec line y =
		assert (y < s);
		let rec cell x =
		  match g.(y).(x) with
		  | 0					-> (x, y)
		  | _ when x = s - 1	-> line (y + 1)
		  | _					-> cell (x + 1)
		in
		cell 0
	  in
	  line 0
		   
	let swap g (xa, ya) (xb, yb) =
	  let v = g.(ya).(xa) in
	  g.(ya).(xa) <- g.(yb).(xb);
	  g.(yb).(xb) <- v

	let build_transp_table w =
	  let a = Array.make (w * w) 0 in

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
		
	  and save x y v inset f =
		let i = x + y * w in
		if v == w * w
		then a.(i) <- 0
		else (a.(i) <- v;
			  f x y v inset)
	  in

	  save 0 0 1 0 inc_x;
	  a
  end

				
(* Heuristics *)
module type HEURISTIC =
  sig
	val calc      	: Grid.t	-> int
	val build_goal	: int		-> Grid.t
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
			(* if v = 0 *)
			(* then foreach_cell (x + 1) acc *)
			(* else ( *)
			let dstx = v mod s in
			let dsty = v / s in
			let dx = abs(x - dstx) in
			let dy = abs(y - dsty) in
			foreach_cell (x + 1) (acc + dx + dy)
		  (* ) *)
		  )
		in
		if y == s
		then acc
		else foreach_line (y + 1) (foreach_cell 0 acc)
	  in
	  foreach_line 0 0

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


  end

module Manhattan0lastHeuristic : HEURISTIC =
  struct
	let calc g =
	  let s = Array.length g in
	  let rec foreach_line y acc =
		let rec foreach_cell x acc =		  
		  if x == s
		  then acc
		  else (
			let v = match g.(y).(x) with
			  | 0		-> s * s - 1
			  | tmp		-> tmp - 1
			in
			let dstx = v mod s in
			let dsty = v / s in
			let dx = abs(x - dstx) in
			let dy = abs(y - dsty) in
			foreach_cell (x + 1) (acc + dx + dy)
		  )
		in
		if y == s
		then acc
		else foreach_line (y + 1) (foreach_cell 0 acc)
	  in
	  foreach_line 0 0

	let build_goal w =
	  let mat = (Array.make_matrix w w 0) in
	  let rec line y acc =
		let rec col x acc = 
		  if x < w then
			(mat.(y).(x) <- acc mod (w * w);
			 col (x + 1) (acc + 1))
		  else acc
		in
		if y < w then
		  line (y + 1) (col 0 acc);
	  in
	  line 0 1;
	  mat


  end

	
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
	  let x0, y0 = Grid.zero st.grid (Array.length st.grid) in
	  Printf.eprintf "State: g(%3d) h(%3d) zero(%d, %d)\n%!" st.g st.h x0 y0;
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


module MakeAStar (He : HEURISTIC) =
  struct
	type closedContainer = (Grid.t, unit) Hashtbl.t
	type openedContainer = StateBatHeap.t
	type data = {
		width 			: int;
		total 			: int;
		goal 			: Grid.t;
		mutable closed	: closedContainer;
		mutable opened	: openedContainer;
	  }
	type state = Solved | Unsolved

	(* let is_solved (s:State.t) (d:data) = *)
	let is_solved s (d:data) =
	  d.goal = s.State.grid
				 
				 
	let create_info (w:int) (i_gr:Grid.t) =
	  let total = w * w in
	  let goal = He.build_goal w in
	  let closed = Hashtbl.create 10000 in
	  let i_st = State.create i_gr 0 (He.calc i_gr) in
	  let opened = StateBatHeap.insert StateBatHeap.empty i_st in
	  {width = w ; total = total ; goal = goal ; closed = closed; opened = opened}


	let solve (i: data) =
	  (* Printf.eprintf "SOLVE START...\n%!"; *)
	  
	  let expand s =
		(* Printf.eprintf "Expanding START**************** \n%!"; *)
		let x0, y0 = Grid.zero s.State.grid i.width in
		
		let move x y = (* RENAME TRY-ADD *)
		  (* Printf.eprintf "Yes !\n%!"; *)
		  let grid = Grid.copy s.State.grid in
		  Grid.swap grid (x0, y0) (x, y);
		  try
			Hashtbl.find i.closed grid
		  with
		  | Not_found		->
			 let h = He.calc grid in
			 let st = State.create grid (s.State.g + 1) h in
			 if (st.State.h < 3)
			 then State.print st;
			 i.opened <- StateBatHeap.insert i.opened st;
			 (* State.print st; *)
			 (* st *)
			 ()
		in
		let move_valid x y =
		  (* Printf.eprintf "IS VALID ? x(%+d) y(%+d): " x y; *)
		  if x < 0 || y < 0 || x >= i.width || y >= i.width
		  then false
		  else true
		in
		let dirs = [(1, 0); (0, 1); (-1, 0); (0, -1)] in
		let rec foreach_dirs dirs =
		  (* Printf.eprintf "FOREACH_DIRS\n%!"; *)
		  match dirs with
		  | (dx, dy)::tl when move_valid (dx + x0) (dy + y0)	->
			 move (dx + x0) (dy + y0);
			 foreach_dirs tl
		  | _::tl												->
			 (* Printf.eprintf "no\n%!"; *)
			 foreach_dirs tl
		  | _													-> ()
		in
		(* let valid_moves = foreach_dirs dirs [] in *)
		foreach_dirs dirs;
		
		(* let rec foreach_valid_moves = function *)
		(* | ({State.grid = g} as mv)::tl	-> *)
		(* if (mv.State.h < 3) *)
		(* then State.print mv; *)
		
		(* i.opened <- StateBatHeap.insert i.opened mv; *)
		(* Printf.eprintf "Size: %d\n" (StateBatHeap.size i.opened); *)
		(* foreach_valid_moves tl *)
		(* | _								-> () *)
		(* in *)
		(* foreach_valid_moves valid_moves; *)
		(* Printf.eprintf "Expanding DONE*****************\n%!"; *)
		(* Printf.eprintf "Size: %d\n" (StateBatHeap.size i.opened); *)
		()
	  in
	  
	  let rec aux () =
		let cur = StateBatHeap.find_min i.opened in
		(* State.print cur; *)
		i.opened <- StateBatHeap.del_min i.opened;
		if is_solved cur i 
		then (Printf.printf "OVER ?!\n%!"; State.print cur)
		else (expand cur;
			  Hashtbl.add i.closed cur.State.grid ();
			  aux ()
			 )
	  in
	  aux ();
	  ()
  end

module ManhattanAStar = MakeAStar(Manhattan0lastHeuristic)
(* module ManhattanAStar = MakeAStar(ManhattanHeuristic) *)

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
  Printf.eprintf "size: %d\n" size;
  let grid = Array.make_matrix size size 42 in
  scanGrid chan grid size;
  close_in chan;
  let init = State.create grid 0 42 in
  let i = ManhattanAStar.create_info size grid in
  Grid.print init.State.grid;
  Printf.eprintf "%d\n" (ManhattanHeuristic.calc init.State.grid);
  ManhattanAStar.solve i;
  ()
