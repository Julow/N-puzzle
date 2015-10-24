(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   Grid.ml                                            :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 14:20:58 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/24 14:55:00 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type matrix = int array array
type t = matrix * int

module type HEURISTIC =
  sig
	include GenericInterfaces.HEURISTIC with type elt := t
  end

(* ************************************************************************** *)

(* TODO: Protect versus x-overflow at 16383=2^(15-1)-1*)
let pivxy piv =
  piv land 0x7FFF, piv lsr 15

let pivv (x, y) =
  x + y lsl 15

let copy_mat mat =
  Array.map (fun line -> Array.copy line) mat

let copy (mat, piv) =
  copy_mat mat, piv

let copy_swap (mat, piv) (dx, dy) =
  let mat' = copy_mat mat in
  let x0, y0 = pivxy piv in
  let v0 = mat.(y0).(x0) in
  let (x, y) as pos = x0 + dx, y0 + dy in
  mat'.(y0).(x0) <- mat.(y).(x);
  mat'.(y).(x) <- v0;
  mat', pivv pos

(* ************************************************************************** *)

let cost _ _ =
  1

let equal (gra, piva) (grb, pivb) =
  piva = pivb && gra = grb

let successors ((mat, piv) as gr) =
  let w = Array.length mat in
  let x0, y0 = pivxy piv in
  let dirs = [(1, 0); (0, 1); (-1, 0); (0, -1)] in

  let is_in_bounds x y =
	if x < 0 || y < 0 || x >= w || y >= w
	then false
	else true
  in
  let rec foreach_dirs dirs acc =
	match dirs with
	| (dx, dy) as dt::tl when is_in_bounds (dx + x0) (dy + y0)  ->
	   foreach_dirs tl (copy_swap gr dt::acc)
	| _::tl                                                     ->
	   foreach_dirs tl acc
	| _                                                         ->
	   acc
  in
  foreach_dirs dirs []

(* ************************************************************************** *)

let iter_cells mat f =
  let w = Array.length mat in
  let rec line y i =
	let rec cell x i =
	  if x < w
	  then (f i x y mat.(y).(x);
			cell (x + 1) (i + 1))
	  else i
	in
	if y < w
	then line (y + 1) (cell 0 i)
  in
  line 0 0

let find mat v =
  let w = Array.length mat in
  let rec line y =
	assert (y < w);
	let rec cell x =
	  if mat.(y).(x) = v then
		(x, y)
	  else if x = w - 1 then
		line (y + 1)
	  else
		cell (x + 1)
	in
	cell 0
  in
  line 0

(* ************************************************************************** *)

let transposition_toreal = ref [|42|]
let transposition_toabstract = ref [|42|]

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
  transposition_toreal := a;
  transposition_toabstract := Array.mapi (fun k _ -> k_of_v a k) a;
  ()

let to_real ((mat, _) as abstgr) =
  let transp_a = !transposition_toreal in
  let (mat', _) as realgr = copy abstgr in
  let aux i x y v =
	mat'.(y).(x) <- transp_a.(v);
  in
  iter_cells mat aux;
  realgr

let to_abstract ((mat, _) as realgr) =
  let transp_a = !transposition_toabstract in
  let (mat', _) as abstgr = copy realgr in
  let aux i x y v =
	mat'.(y).(x) <- transp_a.(v);
  in
  iter_cells mat aux;
  abstgr

let of_cgrid cgrid =
  let w = Npuzzle.get_size cgrid in
  let mat = Array.make_matrix w w (-1) in
  let aux i x y v =
	let v = Npuzzle.get cgrid x y in
	mat.(y).(x) <- v;
  in
  if w <= 0 then
	failwith "Invalid size"
  else
	iter_cells mat aux;
  mat, pivv (find mat 0)

(* ************************************************************************** *)

let print (mat, piv) =
  let last = Array.length mat - 1 in
  let aux i x y v =
	if x = last
	then Printf.eprintf "%2d\n%!" v
	else Printf.eprintf "%2d " v
  in
  let x0, y0 = pivxy piv in
  Printf.eprintf "Pivot (%2d, %2d)\n%!" x0 y0;
  iter_cells mat aux

let print_real_to_abst gr =
  Printf.printf "REAL TO ABST:\n%!";
  print (to_abstract gr)

let print_abst_to_real gr =
  Printf.printf "ABST TO REAL\n%!";
  print (to_real gr)

(* ************************************************************************** *)

let goal w =
  let mat = (Array.make_matrix w w 0) in
  let aux i x y v =
	mat.(y).(x) <- i;
  in
  iter_cells mat aux;
  mat, pivv (find mat (!transposition_toabstract).(0))


let to_filename mat =
  let str = ref "" in
  let rec aux i x y v =
	if v < 0
	then str := Printf.sprintf "%se" !str
	else str := Printf.sprintf "%s%02d" !str v
  in
  iter_cells mat aux;
  (* Printf.eprintf "found '%s'\n%!" !str; *)
  Printf.sprintf "%s.pdb" !str
