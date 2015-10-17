(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   Grid.ml                                            :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 14:20:58 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/17 16:19:34 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type t = (int array) array

(* ************************************************************************** *)

let equal gra grb =
  gra = grb

let copy gr =
  Array.map (fun line -> Array.copy line) gr

let swap g (xa, ya) (xb, yb) =
  let va = g.(ya).(xa) in
  g.(ya).(xa) <- g.(yb).(xb);
  g.(yb).(xb) <- va

let find gr v =
  let w = Array.length gr in
  let rec line y =
	assert (y < w);
	let rec cell x =
	  if gr.(y).(x) = v then
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
	   
let iter_cells gr f =
  let w = Array.length gr in
  let rec line y i =
	let rec cell x i =
	  if x < w
	  then (f i x y gr.(y).(x);
			cell (x + 1) (i + 1))
	  else i
	in
	if y < w
	then line (y + 1) (cell 0 i)
  in
  line 0 0

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

let to_real abstgr =
  let transp_a = !transposition_toreal in
  let realgr = copy abstgr in
  let aux i x y v =
	realgr.(y).(x) <- transp_a.(v);
  in
  iter_cells abstgr aux;
  realgr

let to_abstract realgr =
  let transp_a = !transposition_toabstract in
  let abstgr = copy realgr in
  let aux i x y v =
	abstgr.(y).(x) <- transp_a.(v);
  in
  iter_cells realgr aux;
  abstgr

let of_cgrid cgrid =
  let w = Npuzzle.get_size cgrid in
  let gr = Array.make_matrix w w (-1) in
  let aux i x y v =
	let v = Npuzzle.get cgrid x y in
	gr.(y).(x) <- v;
  in
  if w <= 0 then
	failwith "Invalid size"
  else
	iter_cells gr aux;
  gr

(* ************************************************************************** *)
	
let print gr =
  let last = Array.length gr - 1 in
  let aux i x y v =
	if x = last
	then Printf.eprintf "%2d\n%!" v
	else Printf.eprintf "%2d " v
  in
  iter_cells gr aux

let print_real_to_abst gr =
  Printf.printf "REAL TO ABST:\n%!";
  print (to_abstract gr)

let print_abst_to_real gr =
  Printf.printf "ABST TO REAL\n%!";
  print (to_real gr)

(* ************************************************************************** *)
		
let goal w =
  let gr = (Array.make_matrix w w 0) in
  let aux i x y v =
	gr.(y).(x) <- i;
  in
  iter_cells gr aux;
  gr
