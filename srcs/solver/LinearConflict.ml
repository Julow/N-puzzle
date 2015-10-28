(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   LinearConflict.ml                                  :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/28 14:51:33 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/28 16:10:57 by ngoguey          ###   ########.fr       *)
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
  aux true "" 0 db



let calc_and_input db nbrs =
  Printf.eprintf "Busy[%!";
  List.iter (fun v -> Printf.eprintf "%d %!" v) nbrs;
  Printf.eprintf "] %!";
  ()


let init w db =
  let rec aux i l = if i < 0 then l else aux (i - 1) (i::l) in
  let nbrs = aux (w - 1) [] in
  let rec aux busy free =
	calc_and_input db (List.rev busy);
	Printf.eprintf "Free[%!";
	List.iter (fun v -> Printf.eprintf "%d %!" v) free;
	Printf.eprintf "]%!";
	Printf.eprintf "\n%!";

	let rec aux' tested free' =
	  match free' with
	  | hd::tl	-> aux (hd::busy) (tested@tl);
				   aux' (hd::tested) tl
	  | _		-> ()
	in
	aux' [] free
  in
  aux [] nbrs;
  ()


let alloc w =
  let rec build_lvl i _ =
	if i = w
	then Full (42)
	else Partial (42, Array.init w (build_lvl (i + 1)))
  in
  Partial (42, Array.init w (build_lvl 1))

let gen w =
  let db = alloc w in
  init w db;
  print db;
  db
