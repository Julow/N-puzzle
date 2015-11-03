(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   LinearConflictHeuristic.ml                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/29 13:39:56 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/11/03 17:59:38 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t = Full of int | Partial of int * t array | Redundant

let print db =
  let rec aux first str i lvl =
	let str = match first with
	  | false	-> Printf.sprintf "%s%d " str i
	  | true	-> str
	in
	match lvl with
	| Redundant			-> ();
	| Full v			-> Printf.eprintf "%-10scor(%d) Full\n%!" str v;
	| Partial (v, a)	-> Printf.eprintf "%-10scor(%d) Partial\n%!" str v;
						   Array.iteri (aux false str) a
  in
  aux true "**" 0 db

(*
 **	[0;3;1;2] streak calculation:
 ** Handling[LIST_HEAD] ret(FUN_RET):	PREV [LIST] ACC
 ** *
 **	Handling[3] ret(3):	0 [3;1;2] 1				Start
 **	Handling[1] ret(2):		3 [1;2] 2			(bad)picked 3
 **	Handling[2] ret(2):			3 [2] 2			(bad)
 **	Handling[ ] ret(2):				3 [] 2		(bad)
 **	Handling[1] ret(3):		0 [1;2] 1			(good)did not pick 3
 **								(...)			(bad)did not pick 1
 **	Handling[2] ret(3):			1 [2] 2			(good)picked 1
 **									(...)		(bad)did not pick 2
 **	Handling[ ] ret(3):				2 [] 3		(good)picked 2
 *)

let rec streak prev l acc =
  match l with
  | hd::tl when hd > prev	-> let acc' = streak hd tl (acc + 1) in
							   let acc'' = streak prev tl acc in
							   max acc' acc''
  | _::tl					-> streak prev tl acc
  | _						-> acc

let precalc w nbrs =
  let rec aux l max =
	match l with
	| hd::tl	-> let cur_streak = streak hd tl 1 in
				   let max' = Pervasives.max max cur_streak in
				   aux tl max'
	| _			-> max
  in
  let nnbrs = List.length nbrs in
  let streak = aux nbrs 0 in
  (nnbrs - streak) * 2

let input db nbrs v =
  let rec aux l lvl =
  	match l, lvl with
  	| hd::tl, Partial (v', a)	-> a.(hd) <- aux tl a.(hd);
								   Partial (v', a)
  	| _::_, Full _				-> assert(false)
  	| _, Full _					-> Full v
	| _, Partial (_, a)			-> Partial (v, a)
  	| _, Redundant				-> assert(false)
  in
  aux nbrs db

let init w db =
  let rec aux i l = if i < 0 then l else aux (i - 1) (i::l) in
  let nbrs = aux (w - 1) [] in
  let rec aux busy free db =
	let ord_nrbs = List.rev busy in
	let db = input db ord_nrbs (precalc w ord_nrbs) in
	let rec aux' tested free' db =
	  match free' with
	  | hd::tl	-> let db = aux (hd::busy) (tested@tl) db in
				   aux' (hd::tested) tl db
	  | _		-> db
	in
	aux' [] free db
  in
  aux [] nbrs db

let alloc w =
  let busy = ref [] in
  let rec build_lvl lvl i =
	if List.mem i !busy then
	  Redundant
  	else if lvl = w then
	  Full (42)
  	else (
	  let prevbusy = !busy in
	  busy := i::!busy;
	  let node = Partial (42, Array.init w (build_lvl (lvl + 1))) in
	  busy := prevbusy;
	  node
	)
  in
  Partial (42, Array.init w (build_lvl 1))

let gen w =
  let db = init w (alloc w) in
  (* print db; *)
  db

let calc db md_calc (mat, piv) =
  let x0, y0 = Grid.pivxy piv in
  let w = Array.length mat in
  let rec foreachline y acc =
	if y = w then
	  acc
	else (
	  let rec foreachcell x lvl =
		if x = w then
		  match lvl with
		  | Partial (v, _) | Full v	-> v
		  | _						-> assert(false)
		else if x = x0 && y = y0 then
		  foreachcell (x + 1) lvl
		else (
		  let v = mat.(y).(x) in
		  if v / w <> y  then
			foreachcell (x + 1) lvl
		  else (
			let lvl' = match lvl with
			  | Partial (_, a)	-> a.(v mod w)
			  | _				-> assert(false)
			in
			foreachcell (x + 1) lvl'
		  )
		)
	  in
	  let acc' = foreachcell 0 db in
	  foreachline (y + 1) (acc + acc')
	)
  in
  let rec foreachcol x acc =
	if x = w then
	  acc
	else (
	  let rec foreachcell y lvl =
		if y = w then
		  match lvl with
		  | Partial (v, _) | Full v	-> v
		  | _						-> assert(false)
		else if y = y0 && x = x0 then
		  foreachcell (y + 1) lvl
		else (
		  let v = mat.(y).(x) in
		  if v mod w <> x  then
			foreachcell (y + 1) lvl
		  else (
			let lvl' = match lvl with
			  | Partial (_, a)	-> a.(v / w)
			  | _				-> assert(false)
			in
			foreachcell (y + 1) lvl'
		  )
		)
	  in
	  let acc' = foreachcell 0 db in
	  foreachcol (x + 1) (acc + acc')
	)
  in
  let md = md_calc (mat, piv) in
  let lc_line = foreachline 0 0 in
  let lc_col = foreachcol 0 0 in
  (* TODO: Is lc_line + lc_col still admissible ?! *)
  md + lc_line + lc_col

(* ************************************************************************** *)

let make w : Grid.Heuristic.fn =
  let db = gen w in
  let md = ManhattanDistanceHeuristic.make w in
  calc db md

(* ************************************************************************** *)
