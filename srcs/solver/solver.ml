(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/11/05 11:24:37 by ngoguey          ###   ########.fr       *)
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
(* EVENTS HANDLER *)

module EventHandler = EventHandler.Make(Grid)

(* ************************************************************************** *)
(* ALGORITHMS *)

module GridAStar : (GenericInterfaces.HEPATHFINDER
					with type graph := Grid.t)
  = AStar.Make(Grid)(EventHandler)
module GridIDAStar : (GenericInterfaces.HEPATHFINDER
					  with type graph := Grid.t)
  = IDAStar.Make(Grid)(EventHandler)
module GridGreedySearch : (GenericInterfaces.HEPATHFINDER
						   with type graph := Grid.t)
  = GreedySearch.Make(Grid)(EventHandler)

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
  (* Printf.eprintf "opened: %s\n%!" fname; *)
  ignore (input_line chan);
  (* Printf.eprintf "%s\n%!" (input_line chan); *)
  let size = (Scanf.fscanf chan "%d\n" (fun x _ -> x))() in
  (* Printf.eprintf "size: %d\n%!" size; *)
  let grid = Array.make_matrix size size 42 in
  scanGrid chan grid size;
  close_in chan;
  grid

let grid_from_file fname =
  let mat = mat_from_file fname in
  mat, Grid.pivv (Grid.find mat 0)

(* ************************************************************************** *)
(* SOLVE *)

let center str =
  let slen = String.length str + 2 in
  let llen = max ((80 - slen) / 2) 0 in
  let rlen = max (80 - slen - llen) 0 in
  Printf.eprintf "%s \027[31m%s\027[0m %s\n%!" (String.make llen '*')
				 str (String.make rlen '*')

let thread_handle = ref None
let thread_done = false

let launch (abstgr, goalgr, w, algo, heu_maker) =
  (* let launch abstgr goalgr w algo heu_maker = *)
  let t = Unix.gettimeofday () in
  let heu = heu_maker w in
  center (Printf.sprintf "%f sec to generate heuristic"
						 (Unix.gettimeofday () -. t));
  let t = Unix.gettimeofday () in
  algo abstgr goalgr heu;
  center (Printf.sprintf "%f sec to solve (%d steps)" (Unix.gettimeofday () -. t)
  						 (-42));
  Printf.eprintf "\n%!";
  ()

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

  let packed = (abstgr, goalgr, w, algo, heu_maker) in
  let th = Thread.create launch packed in
  thread_handle := Some th;
  Thread.join th;
  (* () *)
  []
(* launch abstgr goalgr w algo heu_maker *)

(* TODO Grid.of_cgrid is the only safe entry point here *)
let solve' npuzzle =
  let solvable = true in
  let size = 4 in
  let (abstmat, _) as abstgr = Grid.generate size solvable in
  (* let (realmat, realpiv) as realgr = grid_from_file "lol3.np" in *)
  (* let (realmat, realpiv) as realgr = Grid.of_cgrid npuzzle in *)

  (* let abstgr = Grid.to_abstract realgr in *)
  let w = Array.length abstmat in
  Grid.init_transp_tables w;
  let goalgr = Grid.goal w in
  EventHandler.clearq ();

  (* Printf.eprintf "\n%!"; *)
  (* Grid.print realgr; *)
  (* Printf.eprintf "\n%!"; *)
  Grid.print abstgr;
  Printf.eprintf "\n%!";
  Grid.print goalgr;
  Printf.eprintf "\n%!";


  (* TODO: retreive algo/heuristic *)
  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  (* launch_str abstgr goalgr w "Greedy Search" "Disjoint Pattern DB 6/6/3"; *)
  (* launch_str abstgr goalgr w "Greedy Search" "Disjoint Pattern DB 5/5/5"; *)
  (* launch_str abstgr goalgr w "Greedy Search" "Linear Conflict"; *)
  (* launch_str abstgr goalgr w "Greedy Search" "Manhattan Distance"; *)

  launch_str abstgr goalgr w "A*" "Disjoint Pattern DB 6/6/3";
  (* launch_str abstgr goalgr w "A*" "Disjoint Pattern DB 8"; *)
  launch_str abstgr goalgr w "A*" "Disjoint Pattern DB 5/5/5";
  launch_str abstgr goalgr w "A*" "Linear Conflict";
  (* launch_str abstgr goalgr w "A*" "Manhattan Distance"; *)
  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  EventHandler.dumpq (); (* TODO: REMOVE *)
  ()

(* ************************************************************************** *)
(* From C api *)
let poll_event _ =
  EventHandler.popq ()

let solve npuzzle =
  solve' npuzzle;
  ()

let abort _ =
  (match !thread_handle with
  | None		-> ()
  | Some th		-> Thread.kill th);
  EventHandler.clearq ();
  ()

let algorithm_list _ =
  Hashtbl.fold (fun k _ l -> k::l) algorithms []

let heuristic_list _ =
  Hashtbl.fold (fun k _ l -> k::l) algorithms []

let generate_grid : int -> bool -> Grid.t = fun w solvable ->
  Grid.generate w solvable

let transposition_toreal : int -> int array = fun w ->
  Grid.init_transp_tables w;
  !Grid.transposition_toreal

let transposition_toabstract : int -> int array = fun w ->
  Grid.init_transp_tables w;
  !Grid.transposition_toabstract

(* ************************************************************************** *)
(* Init C api *)
let () =
  Random.self_init ();
  Callback.register "solve" solve;
  Callback.register "poll_event" poll_event;
  Callback.register "abort" abort;
  Callback.register "algorithm_list" algorithm_list;
  Callback.register "heuristic_list" heuristic_list;
  Callback.register "generate_grid" generate_grid;
  Callback.register "transposition_toreal" transposition_toreal;
  Callback.register "transposition_toabstract" transposition_toabstract;
  ()
