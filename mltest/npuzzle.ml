(* ************************************************************************** *)
(*																																						*)
(*																												:::			::::::::	 *)
(*	 npuzzle.ml																				 :+:			:+:		:+:	 *)
(*																										+:+ +:+				 +:+		 *)
(*	 By: ngoguey <ngoguey@student.42.fr>						+#+	+:+			 +#+				*)
(*																								+#+#+#+#+#+	 +#+					 *)
(*	 Created: 2015/10/14 13:06:34 by ngoguey					 #+#		#+#						 *)
(*	 Updated: 2015/10/14 13:45:02 by ngoguey					###	 ########.fr			 *)
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

module MakeBatHeap (Ord : ORDEREDTYPE) = struct
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
		Printf.printf "%s %u(%d)\n" (String.make(lvl * 4) '*') bt.rank bt.root
	in
	let rec foreach_t btl lvl = 
		match btl with
		| []		-> ()
		| hd::tl	->
			print_one hd lvl;
			foreach_t hd.kids (lvl + 1);
			foreach_t tl lvl
	in
	Printf.printf "Size: %u\n" bh.size;
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
				then (Printf.printf "%2d " g.(y).(x);
					  cell (x + 1))
			in
			if y < s
			then (cell 0;
				  Printf.printf "\n%!";
				  line (y + 1))
		in
		line 0
	
	let equal a b =
		a = b
end


module type GRIDEVALUATOR =
	sig
		val calc      : Grid.t -> int
	end

module MakeHeuristic (Ev : GRIDEVALUATOR) =
	struct
		let calc = Ev.calc
	end

module ManhattanEval : GRIDEVALUATOR =
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
						foreach_cell (x + 1) (acc + dx + dy)
					)
				in
				if y == s
				then acc
				else foreach_line (y + 1) (foreach_cell 0 acc)
			in
			foreach_line 0 0
	end
	
module ManhattanH = MakeHeuristic(ManhattanEval)

(* State representation as grid, g so far, h current *)
type state = {
	grid : Grid.t;
	g : int;
	h : int;
}

(* module StateOrderedType : (ORDEREDTYPE with type t = state) = *)
module StateOrderedType =
	struct
		type t = state
		let compare = fun a b -> a.g - b.g
	end

(* BatHeap of states *)
(* module StateBatHeap : (BATHEAP with type elem := StateOrderedType.t) = MakeBatHeap(StateOrderedType) *)
module StateBatHeap = MakeBatHeap(StateOrderedType)

(* Solve infos *)
type info = {
	width : int;
	total : int;
	goal : Grid.t;
	closed : (Grid.t, unit) Hashtbl.t;
	opened : StateBatHeap.t;
}

let is_solved (s:state) (i:info) =
	i.goal = s.grid

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

(* w : width, is : Initial State *)
let make_info (w:int) (is:state) =
	let total = w * w in
	let goal = build_goal w in
	let closed = Hashtbl.create 10000 in
	let opened = StateBatHeap.insert StateBatHeap.empty is in
	{width = w ; total = total ; goal = goal ; closed = closed; opened = opened}
(* 
let printGrid g =
	let s = Array.length g in
	let rec helper y =
	if y >= s
	then ()
	else (
		let rec helper2 x =
		if x < s
		then (Printf.printf "%2d " g.(y).(x);
				helper2 (x + 1))
		in
		helper2 0;
		Printf.printf "\n%!";
		helper (y + 1)
	)
	in
	helper 0
 *)

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

(* let ins bh v =
	let bh = insert bh v in
	print bh;
	Printf.printf "\n";
	bh

let del bh v =
	let bh = del_min bh in
	print bh;
	Printf.printf "\n";
	bh *)

let () =
	(* let chan = open_in Sys.argv.(1) in *)
	(* let chan = open_in "lol3solved.np" in *)
	let chan = open_in "lol3.np" in
	(* let chan = open_in "lol3solved.np" in *)
	(* Printf.printf "%s\n%!" Sys.argv.(1); *)
	Printf.printf "%s\n%!" (input_line chan);
	let size = (Scanf.fscanf chan "%d\n" (fun x _ -> x))() in
	Printf.printf "%d\n" size;
	let grid = Array.make_matrix size size 42 in
	scanGrid chan grid size;
	close_in chan;
	
	let init = {grid = grid; g = 0; h = 42} in
	let i = make_info size init in
	
	Printf.printf "%b\n" (is_solved init i);
	
	(* Printf.printf "salut: %b\n" (min init init); *)
	
	Grid.print i.goal;
	Printf.printf "%d\n" (ManhattanH.calc i.goal);
	Grid.print init.grid;
	Printf.printf "%d\n" (ManhattanH.calc init.grid);
	
(*	 
	let bh = ref (ins empty 42) in
	for i = 41 downto 25 do
	bh := ins !bh i
	done;
	for i = 41 downto 25 do
	bh := del !bh i
	done; *)
	
	(* 
	let bh = ins bh 40 in
	let bh = ins bh 39 in
	let bh = ins bh 38 in
	let bh = ins bh 37 in
	let bh = ins bh 36 in *)
	()