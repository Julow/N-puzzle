(* ************************************************************************** *)
(*                                                                            *)
(*                                                        :::      ::::::::   *)
(*   solver.ml                                          :+:      :+:    :+:   *)
(*                                                    +:+ +:+         +:+     *)
(*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        *)
(*                                                +#+#+#+#+#+   +#+           *)
(*   Created: 2015/10/16 15:03:58 by jaguillo          #+#    #+#             *)
(*   Updated: 2015/10/19 17:29:35 by ngoguey          ###   ########.fr       *)
(*                                                                            *)
(* ************************************************************************** *)


(* Solve *)
let solve npuzzle =
  let (realmat, realpiv) as realgr = Grid.of_cgrid npuzzle in
  let w = Array.length realmat in
  Printf.eprintf "width %u\n%!" w;
  Grid.init_transp_tables w;
  let abstgr = Grid.to_abstract realgr in
  Printf.eprintf "\n%!";
  Grid.print realgr;
  Printf.eprintf "\n%!";
  Grid.print abstgr;
  Printf.eprintf "\n%!";

  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  (* ------------------------> SOLVING GOES HERE <------------------------ *)
  ()

(* Init C api *)
let () =
  Callback.register "solve" solve
