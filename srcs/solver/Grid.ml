(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   Grid.ml                                            :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/17 14:20:58 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/12/07 11:52:51 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

type matrix = int array array
type t = matrix * int

module Heuristic : (GenericInterfaces.HEURISTIC
					with type elt := t) =
  struct
	type fn = t -> int
	type maker = int -> fn
  end

let bit_per_piv_component = 7
let piv_component_mask = (1 lsl bit_per_piv_component) - 1

(* ************************************************************************** *)
(* PERF CRITICAL *)

(* TODO: Protect versus x-overflow (IMPORTANT) and debug *)
let pivxy piv =
  piv land piv_component_mask, piv lsr bit_per_piv_component

let pivv (x, y) =
  x + y lsl bit_per_piv_component

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

(* ************************************************************************** *)
(* PERF CRITICAL - REQ BY PATHFINDER *)

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
(* MISC *)

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

let zero_coords w =
  let x = (w - 1) / 2 in
  let y = w / 2 in
  x, y

type parity = Odd | Even

let is_solvable (mat, piv) =
  let w = Array.length mat in
  let v0 = (fun (x, y) -> x + y * w) (zero_coords w) in
  let x0, y0 = pivxy piv in
  let dstx0, dsty0 = v0 mod w, v0 / w in
  let nbrs = ref [] in
  for y = w - 1 downto 0 do
	for x = w - 1 downto 0 do
	  if y <> y0 || x <> x0
	  then nbrs := mat.(y).(x)::!nbrs;
	done
  done;
  assert (List.length !nbrs = w * w - 1);
  let rec aux i l acc =
	if i < 0 then
	  acc
	else (
	  let rec aux' = function
		| hd::tl when hd = i	-> List.length tl
		| _::tl					-> aux' tl
		| _						-> assert (false)
	  in
	  let rec aux'' = function
		| hd::tl when hd = i	-> aux'' tl
		| hd::tl				-> hd :: aux'' tl
		| _						-> []
	  in
	  if i <> v0
	  then aux (i - 1) (aux'' l) (acc + aux' l)
	  else aux (i - 1) (aux'' l) acc
	)
  in
  let inversions = aux (w * w - 1) !nbrs 0 in
  let get_parity v = match v mod 2 with 0 -> Even | _ -> Odd in
  (* Printf.eprintf "\n\n\n%!"; *)
  (* let dumpparity name v = *)
  (* 	match get_parity v with *)
  (* 	| Odd	-> Printf.eprintf "'%15s': Odd  (%d)\n%!" name v *)
  (* 	| Even	-> Printf.eprintf "'%15s': Even (%d)\n%!" name v *)
  (* in *)
  (* dumpparity "w" w; *)
  (* dumpparity "(dstx0 - x0)" (dstx0 - x0); *)
  (* dumpparity "(dsty0 - y0)" (dsty0 - y0); *)
  (* dumpparity "inversions" inversions; *)
  match get_parity w
	  , get_parity (dstx0 - x0)
	  , get_parity (dsty0 - y0)
	  , get_parity inversions with
  | Even,	_,		Even,	Even	-> true
  | Even,	_,		Odd,	Odd		-> true
  | Even,	_,		_,		_		-> false
  | Odd,	_,		_,		Odd		-> false
  | Odd,	_,		_,		Even	-> true

(* ************************************************************************** *)
(* CONVERSIONS *)

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

(**
 **	Case 1	-> Grid size is not handled
 **	Case 2	-> Wrong numbers in grid
 **	Case 3	-> Grid is not solvable
 **	Case 4	-> OK
 *)
let of_cgrid cgrid =
  let w = Npuzzle.get_size cgrid in
  if w < 3 then
	failwith (Printf.sprintf "Invalid grid: with = %d" w);
  let mat = Array.make_matrix w w (-1) in
  let allnbrs = ref [] in
  let aux i x y v =
	let v = Npuzzle.get cgrid x y in
	allnbrs := v::!allnbrs;
	mat.(y).(x) <- v;
  in
  iter_cells mat aux;
  let check_nbrs cur expected =
	if cur <> expected then
	  failwith (Printf.sprintf
				  "Invalid grid: '%d' instead of '%d'" cur expected);
	cur + 1
  in
  let ret = List.fold_left
			  check_nbrs 0 (List.sort Pervasives.compare !allnbrs) in
  if ret <> w * w then
	failwith (Printf.sprintf
				"Invalid grid: '%d' instead of '%d'" ret (w * w));
  let i0 = (fun (x, y) -> x + y * w) (zero_coords w) in
  let gr = mat, pivv (find mat i0) in
  if not (is_solvable gr)
  then failwith "Invalid grid: not solvable"
  else gr

(* ************************************************************************** *)
(* MISC *)

let goal w =
  let mat = (Array.make_matrix w w 0) in
  let aux i x y v =
	mat.(y).(x) <- i;
  in
  iter_cells mat aux;
  mat, pivv (zero_coords w)

let generate w solvable nloops =

  let try_successor ((mat, piv) (* as gr *)) =
	let x0, y0 = pivxy piv in
	let dirs = [|(1, 0); (0, 1); (-1, 0); (0, -1)|] in

	let is_in_bounds x y =
	  if x < 0 || y < 0 || x >= w || y >= w
	  then false
	  else true
	in
	let (x, y) = (fun (dx, dy) -> dx + x0, dy + y0) dirs.(Random.int 4) in
	if is_in_bounds x y then (
	  let v0 = mat.(y0).(x0) in
	  mat.(y0).(x0) <- mat.(y).(x);
	  mat.(y).(x) <- v0;
	  pivv (x, y))
	else
	  piv
  in
  let mat, piv = goal w in
  let rec aux i piv =
	if i = nloops
	then piv
	else (
	  let piv = try_successor (mat, piv) in
	  aux (i + 1) piv)
  in
  let (mat, piv) as gr = mat, aux 0 piv in
  match solvable with
  | true	-> gr
  | false	-> match successors gr with
			   | (_, piv0)::(_, piv1)::_
				 -> let x0, y0 = pivxy piv0 in
					let x1, y1 = pivxy piv1 in
					let v0 = mat.(y0).(x0) in
					mat.(y0).(x0) <- mat.(y1).(x1);
					mat.(y1).(x1) <- v0;
					gr
			   | _
				 -> failwith "unreachable"

let to_filename mat =
  let str = ref "" in
  let rec aux i x y v =
	if v < 0
	then str := Printf.sprintf "%se" !str
	else str := Printf.sprintf "%s%02d" !str v
  in
  iter_cells mat aux;
  Printf.sprintf "%s.pdb" !str

(* ************************************************************************** *)
(* DEBUG *)

let print ((mat, piv) as gr) =
  let last = Array.length mat - 1 in
  let aux i x y v =
	if x = last
	then Printf.eprintf "%2d\n%!" v
	else Printf.eprintf "%2d " v
  in
  let x0, y0 = pivxy piv in
  Printf.eprintf "Pivot (%2d, %2d) solvable:%b\n%!" x0 y0 (is_solvable gr);
  iter_cells mat aux

let print_real_to_abst gr =
  Printf.printf "REAL TO ABST:\n%!";
  print (to_abstract gr)

let print_abst_to_real gr =
  Printf.printf "ABST TO REAL\n%!";
  print (to_real gr)

		(* ************************************************************************** *)
