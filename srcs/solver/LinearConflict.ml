(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   LinearConflict.ml                                  :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/28 14:51:33 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/28 17:26:31 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t = Full of int | Partial of int * t array

let print db =
  let rec aux first str i lvl =
	let str = match first with
	  | false	-> Printf.sprintf "%s%d " str i
	  | true	-> str
	in
	match lvl with
	| Full v			-> Printf.eprintf "%s(%d)Full\n%!" str v;
	| Partial (v, a)	-> Printf.eprintf "%s(%d)Partial\n%!" str v;
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

let calc w nbrs =
  let rec aux l max =
	match l with
	| hd::tl	-> let cur_streak = streak hd tl 1 in
				   let max' = Pervasives.max max cur_streak in
				   aux tl max'
	| _			-> max
  in
  aux nbrs 0

let input db nbrs v =
  let rec aux l lvl =
  	match l, lvl with
  	| hd::tl, Partial (v', a)	-> a.(hd) <- aux tl a.(hd);
								   Partial (v', a)
  	| _::_, Full _				-> assert(false)
  	| _, Full _					-> Full v
	| _, Partial (_, a)			-> Partial (v, a)
  in
  (* Printf.eprintf "Busy[%!"; *)
  Printf.eprintf "**%!";
  List.iter (fun v -> Printf.eprintf "%d %!" v) nbrs;
  Printf.eprintf "(%d)%! REAL" v;
  (* Printf.eprintf "] %!"; *)
  Printf.eprintf "\n%!";
  aux nbrs db

let init w db =
  let rec aux i l = if i < 0 then l else aux (i - 1) (i::l) in
  let nbrs = aux (w - 1) [] in
  let rec aux busy free db =
	let ord_nrbs = List.rev busy in
	let db = input db ord_nrbs (calc w ord_nrbs) in
	(* Printf.eprintf "Free[%!"; *)
	(* List.iter (fun v -> Printf.eprintf "%d %!" v) free; *)
	(* Printf.eprintf "]%!"; *)
	(* Printf.eprintf "\n%!"; *)

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
  let rec build_lvl i _ =
	if i = w
	then Full (42)
	else Partial (42, Array.init w (build_lvl (i + 1)))
  in
  Partial (42, Array.init w (build_lvl 1))

let gen w =
  let db = init w (alloc w) in
  print db;
  db
