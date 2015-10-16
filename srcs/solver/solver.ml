(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/10/16 18:55:11 by jaguillo         ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

(* TMP *)
(* TODO: move to Grid.to_absolute *)
let snail_to_absolute grid = grid

(* Init grid *)
(* TODO: move to Grid.init *)
let init_grid npuzzle =
	let size = Npuzzle.get_size npuzzle in
	let grid = Array.make_matrix size size 0 in

	let rec fill_grid x y =
		if x >= size then
			fill_grid 0 (y + 1)
		else if y < size then begin
			grid.(y).(x) <- (Npuzzle.get x y);
			fill_grid (x + 1) y
		end else
			()
	in

	fill_grid 0 0;
	snail_to_absolute grid

(* Solve *)
let solve npuzzle =
	let grid = init_grid npuzzle in
	(* ------------------------> SOLVING GOES HERE <------------------------ *)
	()

(* Init C api *)
let () =
	Callback.register "solve" solve
