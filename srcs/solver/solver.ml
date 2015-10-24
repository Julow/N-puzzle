(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/10/24 15:59:15 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module GridAStar : (GenericInterfaces.HEPATHFINDER
					with type graph := Grid.t) = AStar.Make(Grid)
module GridIDAStar : (GenericInterfaces.HEPATHFINDER
					  with type graph := Grid.t) = IDAStar.Make(Grid)


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


let mat_from_file fname =
  let chan = open_in fname in
  Printf.eprintf "opened: %s\n%!" fname;
  Printf.eprintf "%s\n%!" (input_line chan);
  let size = (Scanf.fscanf chan "%d\n" (fun x _ -> x))() in
  Printf.eprintf "size: %d\n%!" size;
  let grid = Array.make_matrix size size 42 in
  scanGrid chan grid size;
  close_in chan;
  grid


let grid_from_file fname =
  let mat = mat_from_file fname in
  mat, Grid.pivv (Grid.find mat 0)


(* Solve *)
let solve npuzzle =
  (* let (realmat, realpiv) as realgr = grid_from_file "lol3.np" in *)
  (* let (realmat, realpiv) as realgr = Grid.of_cgrid npuzzle in *)
  let realmat = [|
  	  [|3 ;5 ;4|];
  	  [|2; 0; 6|];
  	  [|7; 8; 1|];
  	 |] in

  let realpiv = Grid.pivv (1, 1) in
  let realgr = realmat, realpiv in
  let w = Array.length realmat in
  Printf.eprintf "width %u\n%!" w;
  Grid.init_transp_tables w;
  let abstgr = Grid.to_abstract realgr in
  let goalgr = Grid.goal w in
  Printf.eprintf "\n%!";
  Grid.print realgr;
  Printf.eprintf "\n%!";
  Grid.print abstgr;
  Printf.eprintf "\n%!";
  Grid.print goalgr;
  Printf.eprintf "\n%!";
  (* let dps = [|[|-1;-1;-1;-1|]; *)
  (* 			  [|-1;-1;-1;-1|]; *)
  (* 			  [|-1;-1;-1;-1|]; *)
  (* 			  [| 1; 1; 1; 1|];|] in *)
  let dps = [|[| 5;-1;-5;-1|];
  			  [| 5;-1;-5;-1|];
  			  [| 5;-1;-5;-1|];
  			  [| 5; 5;-1;-1|];|] in
  (* let dps = [|[|5 ;5;-1; 1|]; *)
  (* 			  [|5; 5;-1;-1|]; *)
  (* 			  [|5;-1;-1; 1|]; *)
  (* 			  [|1; 1; 1; 1|];|] in *)
  let t = Unix.gettimeofday () in
  let dpdb = DisjointPatternDB.build dps in
  ignore(dpdb);
  Printf.eprintf "%f sec to build!!!\n%!" (Unix.gettimeofday () -. t);

  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  (* let t = Unix.gettimeofday () in *)
  (* let stack = GridAStar.solve abstgr goalgr GridHeuristics.Manhattan.calc in *)
  (* ignore(stack); *)
  (* Printf.eprintf "%f sec to solve (%d steps)\n%!" *)
  (* 				 (Unix.gettimeofday () -. t) *)
  (* 				 (List.length stack - 1); *)

  (* let t = Unix.gettimeofday () in *)
  (* let stack = GridIDAStar.solve abstgr goalgr GridHeuristics.Manhattan.calc in *)
  (* ignore(stack); *)
  (* Printf.eprintf "%f sec to solve (%d steps)\n%!" *)
  (* 				 (Unix.gettimeofday () -. t) *)
  (* 				 (List.length stack - 1); *)

  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  ()

(* Init C api *)
let () =
  Callback.register "solve" solve
