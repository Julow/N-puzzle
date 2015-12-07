(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/12/07 14:08:04 by ngoguey          ###   ########.fr       *)
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
  [|("A*", GridAStar.solve);
	("IDA*", GridIDAStar.solve);
	("Greedy Search", GridGreedySearch.solve);
  |]

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
  [|("Manhattan Distance", 0, ManhattanDistanceHeuristic.make);
	("Linear Conflict", 0, LinearConflictHeuristic.make);
	("Disjoint Pattern DB 8", 3, DPatternDBHeuristic.make pat8);
	("Disjoint Pattern DB 7", 3, DPatternDBHeuristic.make pat7);
	("Disjoint Pattern DB 6/6/3", 4, DPatternDBHeuristic.make pat663);
	("Disjoint Pattern DB 5/5/5", 4, DPatternDBHeuristic.make pat555);
	("Uniform Cost", 0, UniformCostHeuristic.make);
  |]

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

let launch (abstgr, goalgr, w, algo, heu_maker, cost) =
  (* TODO: Catch all errors and send to EventHandler *)
  let t = Unix.gettimeofday () in
  let heu = heu_maker w in
  center (Printf.sprintf "%f sec to generate heuristic"
						 (Unix.gettimeofday () -. t));
  let t = Unix.gettimeofday () in
  algo abstgr goalgr heu;
  center (Printf.sprintf "%f sec to solve" (Unix.gettimeofday () -. t));
  ()

(* TODO Grid.of_cgrid is the only safe entry point here *)
let solve' npuzzle (aid, hid, cost) =
  if aid >= Array.length algorithms
  then failwith "Wrong algorithm id";
  if hid >= Array.length heuristics
  then failwith "Wrong heuristic id";
  if cost > 1 || cost < (-1)
  then failwith "Wrong cost";

  (* let solvable = true in *)
  (* let size = 3 in *)
  (* let (abstmat, _) as abstgr = Grid.generate size solvable 10000 in *)

  (* let (realmat, realpiv) as realgr = grid_from_file "lol3.np" in *)
  (* let abstgr = Grid.to_abstract realgr in *)

  let (abstmat, abstpiv) as abstgr = Grid.of_cgrid npuzzle in
  let w = Array.length abstmat in
  Grid.init_transp_tables w;
  let goalgr = Grid.goal w in
  EventHandler.clearq ();

  Grid.print abstgr;
  Printf.eprintf "\n%!";

  let (aname, afun) = algorithms.(aid) in
  let (hname, hsize, hmaker) = heuristics.(hid) in

  if hsize <> 0 && hsize <> w
  then failwith "Cannot solve grid with heuristic";

  center "";
  center (Printf.sprintf "%s ** %s" aname hname);

  launch (abstgr, goalgr, w, afun, hmaker, cost);
  ()

(* ************************************************************************** *)
(* From C api *)
(* let solve : Npuzzle.t -> unit = fun npuzzle -> *)
let solve : Npuzzle.t -> int -> int -> int -> unit = fun npuzzle aid hid cost ->
  Printf.eprintf "solve ocaml\n%!";
  solve' npuzzle (aid, hid, cost);
  ()

let test npuzzle =
  let (abstmat, abstpiv) as abstgr = Grid.of_cgrid npuzzle in
  Grid.print abstgr;
  (* let res = Grid.is_solvable abstgr; *)
  ()


let poll_event _ =
  EventHandler.popq ()

let abort _ =
  (match !thread_handle with
   | None		-> ()
   | Some th		-> Thread.kill th);
  EventHandler.clearq ();
  ()

let generate_grid : int -> bool -> int -> Grid.t = fun w solvable nloops ->
  let gr = Grid.generate w solvable nloops in
  gr

let algorithm_list _ =
  Array.fold_right (fun (k, _) l -> k::l) algorithms []

let heuristic_list _ =
  Array.fold_right (fun (k, _, _) l -> k::l) heuristics []

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
  Callback.register "test" test;
  Callback.register "poll_event" poll_event;
  Callback.register "abort" abort;
  Callback.register "algorithm_list" algorithm_list;
  Callback.register "heuristic_list" heuristic_list;
  Callback.register "generate_grid" generate_grid;
  Callback.register "transposition_toreal" transposition_toreal;
  Callback.register "transposition_toabstract" transposition_toabstract;
  ()
