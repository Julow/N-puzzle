(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   npuzzle.ml                                         :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/14 13:06:34 by ngoguey           #+#    #+#             *)
(*   Updated: 2015/10/14 13:45:02 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)


let printGrid g =
  let s = Array.length g in
  let rec helper y =
	if y >= s
	then ()
	else (

	  let rec helper2 x =
		if x < s
		then (Printf.printf "%d " g.(y).(x);
			  helper2 (x + 1))
	  in

	  helper2 0;
	  Printf.printf "\n%!";
	  helper (y + 1)
	)
  in
  helper 0


let scanGrid chan g s =

  let rec line y =
	let rec col x = 
	if x < s then
	  (
		let v = (Scanf.fscanf chan "%u " (fun x _ -> x))() in
		(* Printf.printf "%d " v; *)
		(* Printf.printf "%d-%d " x y; *)
		g.(y).(x) <- v;
		col (x + 1)
	  )
	  
	in

	if y < s then
	  (
		col 0;
		(* Printf.printf "\n%!"; *)
		line (y + 1)
	  )
	
  in
  line 0
  

let () =
  let chan = open_in Sys.argv.(1) in
  Printf.printf "%s\n%!" Sys.argv.(1);

  Printf.printf "%s\n%!" (input_line chan);

  let size = (Scanf.fscanf chan "%d\n" (fun x _ -> x))() in
  Printf.printf "%d\n%!" size;

  let grid = Array.make_matrix size size 42 in
  (* let grid = Array.make size (Array.make size 42) in *)

  scanGrid chan grid size;
  printGrid grid;
  

  
  (* Scanf.scanf chan "%d" (fun d -> Printf.printf "%d\n%!" d; d); *)
  
  close_in chan;
