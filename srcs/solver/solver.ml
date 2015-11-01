(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/11/01 16:39:02 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

let hashtbl_of_list l =
  let h = Hashtbl.create (List.length l) in
  let rec aux = function
	| (n, f)::tl	-> Hashtbl.add h n f;
					   aux tl
	| _				-> ()
  in
  aux l;
  h

(* ************************************************************************** *)
(* ALGORITHMS *)

module GridAStar : (GenericInterfaces.HEPATHFINDER
					with type graph := Grid.t) = AStar.Make(Grid)
module GridIDAStar : (GenericInterfaces.HEPATHFINDER
					  with type graph := Grid.t) = IDAStar.Make(Grid)
module GridGreedySearch : (GenericInterfaces.HEPATHFINDER
					  with type graph := Grid.t) = GreedySearch.Make(Grid)

let algorithms =
  hashtbl_of_list
	[("A*", GridAStar.solve);
	 ("IDA*", GridIDAStar.solve);
	 ("Greedy Search", GridGreedySearch.solve);
	]

(* ************************************************************************** *)
(* HEURISTICS *)

let pat8 = [|[| 1; 1; 1|];
			 [| 1;-9; 1|];
			 [| 1; 1; 1|];|]
let pat7 = [|[| 1; 1; 1|];
			 [| 1;-9;-1|];
			 [| 1; 1; 1|];|]
let pat663 = [|[| 1; 1; 1; 3|];
			   [| 1; 1; 3; 3|];
			   [| 1;-9; 3; 3|];
			   [| 2; 2; 2; 3|];|]
let pat555 = [|[| 1; 1; 2; 2|];
  			   [| 1; 1; 2; 2|];
  			   [| 1;-9; 3; 2|];
  			   [| 3; 3; 3; 3|];|]

let heuristics =
  hashtbl_of_list
	[("Manhattan Distance", ManhattanDistanceHeuristic.make);
	 ("Linear Conflict", LinearConflictHeuristic.make);
	 ("Disjoint Pattern DB 8", DPatternDBHeuristic.make pat8);
	 ("Disjoint Pattern DB 7", DPatternDBHeuristic.make pat7);
	 ("Disjoint Pattern DB 6/6/3", DPatternDBHeuristic.make pat663);
	 ("Disjoint Pattern DB 5/5/5", DPatternDBHeuristic.make pat555);
	 ("Uniform Cost", UniformCostHeuristic.make);
	]

(* ************************************************************************** *)
(* DOTO: REMOVE LATER *)

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

(* ************************************************************************** *)
(* SOLVE ENTRY POINT *)

let center str =
  let slen = String.length str + 2 in
  let llen = max ((80 - slen) / 2) 0 in
  let rlen = max (80 - slen - llen) 0 in
  Printf.eprintf "%s \027[31m%s\027[0m %s\n%!" (String.make llen '*')
				 str (String.make rlen '*')

let launch abstgr goalgr w algo heu_maker =
  let t = Unix.gettimeofday () in
  let heu = heu_maker w in
  center (Printf.sprintf "%f sec to generate heuristic"
						 (Unix.gettimeofday () -. t));
  let t = Unix.gettimeofday () in
  let stack = algo abstgr goalgr heu in
  center (Printf.sprintf "%f sec to solve (%d steps)" (Unix.gettimeofday () -. t)
  						 (List.length stack - 1));
  Printf.eprintf "\n%!";
  stack

let launch_str abstgr goalgr w algo_str heu_maker_str =
  let algo =
	try Hashtbl.find algorithms algo_str
	with
	| Not_found	->
	   failwith (Printf.sprintf "'%s' algorithm does not exist" algo_str)
  in
  let heu_maker =
	try Hashtbl.find heuristics heu_maker_str
	with
	| Not_found
	  -> failwith(Printf.sprintf "'%s' heuristic does not exist" heu_maker_str)
  in
  center "";
  center (Printf.sprintf "%s ** %s" algo_str heu_maker_str);
  launch abstgr goalgr w algo heu_maker

(* TODO Grid.of_cgrid is the only safe entry point here *)
let solve npuzzle =
  let (realmat, realpiv) as realgr = grid_from_file "lol3.np" in
  (* let (realmat, realpiv) as realgr = Grid.of_cgrid npuzzle in *)

  (* let realmat = [| *)
  (* 	  [|3 ;5 ;4|]; *)
  (* 	  [|2; 0; 6|]; *)
  (* 	  [|7; 8; 1|]; *)
  (* 	 |] in *)
  (* let realpiv = Grid.pivv (1, 1) in *)
  (* let realgr = realmat, realpiv in *)

  let w = Array.length realmat in
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

  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  (* launch_str abstgr goalgr w "Greedy Search" "Disjoint Pattern DB 6/6/3"; *)
  (* launch_str abstgr goalgr w "Greedy Search" "Disjoint Pattern DB 5/5/5"; *)
  launch_str abstgr goalgr w "Greedy Search" "Linear Conflict";
  launch_str abstgr goalgr w "Greedy Search" "Manhattan Distance";

  launch_str abstgr goalgr w "A*" "Disjoint Pattern DB 6/6/3";
  launch_str abstgr goalgr w "A*" "Disjoint Pattern DB 5/5/5";
  launch_str abstgr goalgr w "A*" "Linear Conflict";
  (* launch_str abstgr goalgr w "A*" "Manhattan Distance"; *)
  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  ()

(* ************************************************************************** *)
(* Init C api *)
let () =
  Callback.register "solve" solve
