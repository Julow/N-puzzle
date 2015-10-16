(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/10/16 19:49:46 by jaguillo         ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

(* TMP *)
(* TODO: move to Grid.to_absolute *)
let snail_to_absolute grid = grid

(* Init grid *)
(* TODO: move to Grid.init *)
let init_grid npuzzle =
	let size = Npuzzle.get_size npuzzle in
	let grid = Array.make_matrix size size (-1) in

	let rec fill_grid x y =
		if x >= size then
			fill_grid 0 (y + 1)
		else if y < size then begin
			let value = Npuzzle.get npuzzle x y in
			grid.(y).(x) <- value;
			fill_grid (x + 1) y
		end else
			()
	in

	if size <= 0 then
		failwith "Invalid size"
	else
		fill_grid 0 0;
	snail_to_absolute grid

let rec print_grid grid x y size =
	if x >= size then begin
		print_newline () ; print_grid grid 0 (y + 1) size
	end else if y < size then begin
		print_int grid.(y).(x); print_string " ";
		print_grid grid (x + 1) y size
	end else
		()

(* Solve *)
let solve npuzzle =
	let grid = init_grid npuzzle in
	(* ------------------------> SOLVING GOES HERE <------------------------ *)
	print_grid grid 0 0 (Npuzzle.get_size npuzzle)

(* Init C api *)
let () =
	Callback.register "solve" solve
