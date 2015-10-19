(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/10/19 18:26:23 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)

module GridAStar : (GenericInterfaces.HEPATHFINDER
					with type graph := Grid.t) = AStar.Make(Grid)
module GridIDAStar : (GenericInterfaces.HEPATHFINDER
					  with type graph := Grid.t) = IDAStar.Make(Grid)

(* Solve *)
let solve npuzzle =
  (* let (realmat, realpiv) as realgr = Grid.of_cgrid npuzzle in *)
  let realmat = [|
	  [|3 ;1 ;4|];
	  [|2; 0; 6|];
	  [|8; 7; 5|];
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

  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  GridIDAStar.solve abstgr goalgr GridHeuristics.Manhattan.calc;
  GridAStar.solve abstgr goalgr GridHeuristics.Manhattan.calc;
  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  ()

(* Init C api *)
let () =
  Callback.register "solve" solve
