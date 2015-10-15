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


let min x y = if Pervasives.compare x y <= 0 then x else y

(** binomial trees *)
type 'a bt = {
  rank : int ;
  root : 'a ;
  kids : 'a bt list ;
}

type 'a t = {
  size : int ;
  data : 'a bt list ;
  mind : 'a option ; (** cached minimal element *)
}

let empty = { size = 0 ; data = [] ; mind = None }

let size bh = bh.size

let link bt1 bt2 =
  assert (bt1.rank = bt2.rank) ;
  let rank = bt1.rank + 1 in
  let leq = Pervasives.compare bt1.root bt2.root <= 0 in
  let root = if leq then bt1.root else bt2.root in
  let kids = if leq then bt2 :: bt1.kids else bt1 :: bt2.kids in
  { rank = rank ; root = root ; kids = kids }

let rec add_tree t = function
  | [] -> [t]
  | (ut :: uts) as ts ->
    assert (t.rank <= ut.rank) ;
    if t.rank < ut.rank then t :: ts
    else add_tree (link t ut) uts

let insert bh x =
  let size = bh.size + 1 in
  let data = add_tree { rank = 0 ; root = x ; kids = [] } bh.data in
  let mind = match bh.mind with
    | None -> Some x
    | Some mind -> Some (min x mind)
  in {
    size = size ; data = data ; mind = mind
  }

(*$T size ; empty
  size (insert empty 3) = 1
  size empty = 0
*)

let add x bh = insert bh x

(*$T
  find_min (add 3 (add 2 (add 1 empty))) = 1
*)

let rec merge_data ts1 ts2 = match ts1, ts2 with
  | _, [] -> ts1
  | [], _ -> ts2
  | t1 :: tss1, t2 :: tss2 ->
    if t1.rank < t2.rank then
      t1 :: merge_data tss1 ts2
    else if t1.rank > t2.rank then
      t2 :: merge_data ts1 tss2
    else
      add_tree (link t1 t2) (merge_data tss1 tss2)

let merge bh1 bh2 =
  let size = bh1.size + bh2.size in
  let data = merge_data bh1.data bh2.data in
  let mind = match bh1.mind, bh2.mind with
    | Some m1, Some m2 -> Some (min m1 m2)
    | m, None | None, m -> m
  in
  { size = size ; data = data ; mind = mind }

(*$T
  merge (of_list [3;2]) (of_list [4;1]) |> to_list = [1;2;3;4]
*)

let find_min bh = match bh.mind with
  | None -> invalid_arg "find_min"
  | Some d -> d

(*$T find_min ; insert ; empty
   find_min (insert (insert empty 3) 5) = 3
   find_min (insert (insert empty 5) 3) = 3
*)


let rec find_min_tree ts k = match ts with
  | [] -> failwith "find_min_tree"
  | [t] -> k t
  | t :: ts ->
    find_min_tree ts begin
      fun u ->
        if Pervasives.compare t.root u.root <= 0
        then k t else k u
    end

let rec del_min_tree bts k = match bts with
  | [] -> invalid_arg "del_min"
  | [t] -> k t []
  | t :: ts ->
    del_min_tree ts begin
      fun u uts ->
        if Pervasives.compare t.root u.root <= 0
        then k t ts
        else k u (t :: uts)
    end

let del_min bh =
  del_min_tree bh.data begin
    fun bt data ->
      let size = bh.size - 1 in
      let data = merge_data (List.rev bt.kids) data in
      let mind = if size = 0 then None else Some (find_min_tree data (fun t -> t)).root in
      { size = size ; data = data ; mind = mind }
  end

let of_list l = List.fold_left insert empty l

let to_list bh =
  let rec aux acc bh =
    if size bh = 0 then acc else
      let m = find_min bh in
      let bh = del_min bh in
      aux (m :: acc) bh
  in
  List.rev (aux [] bh)

let printGrid g =
  let s = Array.length g in
  let rec helper y =
	if y >= s
	then ()
	else (

	  let rec helper2 x =
		if x < s
		then (Printf.printf "%2d " g.(y).(x);
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
		let v = (Scanf.fscanf chan " %u " (fun x _ -> x))() in
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
  (* let chan = open_in Sys.argv.(1) in *)
  let chan = open_in "lol.np" in
  (* Printf.printf "%s\n%!" Sys.argv.(1); *)

  Printf.printf "%s\n%!" (input_line chan);

  let size = (Scanf.fscanf chan "%d\n" (fun x _ -> x))() in
  Printf.printf "%d\n" size;

  let grid = Array.make_matrix size size 42 in
  (* let grid = Array.make size (Array.make size 42) in *)

  scanGrid chan grid size;
  printGrid grid;
  

  
  (* Scanf.scanf chan "%d" (fun d -> Printf.printf "%d\n%!" d; d); *)
  
  close_in chan;
