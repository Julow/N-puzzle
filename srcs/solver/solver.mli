val hashtbl_of_list : ('a * 'b) list -> ('a, 'b) Hashtbl.t
module EventHandler :
  sig
    type state = Grid.t
    type report = EventHandler.Make(Grid).report
    type t =
      EventHandler.Make(Grid).t =
        Success of report
      | Failed of string
      | Progress of float
      | Empty
    val dumpq : unit -> unit
    val pushq : t -> unit
    val popq : unit -> t
    val clearq : unit -> unit
    val new_report : int -> report
    val tick_report : report -> int -> int -> int -> report
    val finalize_report : report -> state list -> report
  end
module GridAStar :
  sig val solve : Grid.t -> Grid.t -> (Grid.t -> int) -> unit end
module GridIDAStar :
  sig val solve : Grid.t -> Grid.t -> (Grid.t -> int) -> unit end
module GridGreedySearch :
  sig val solve : Grid.t -> Grid.t -> (Grid.t -> int) -> unit end
val algorithms :
  (string, Grid.t -> Grid.t -> Grid.Heuristic.fn -> unit) Hashtbl.t
val pat8 : int array array
val pat7 : int array array
val pat663 : int array array
val pat555 : int array array
val heuristics : (string, int -> Grid.Heuristic.fn) Hashtbl.t
val scanGrid : in_channel -> int array array -> int -> unit
val mat_from_file : string -> int array array
val grid_from_file : string -> int array array * int
val center : string -> unit
val thread_handle : Thread.t option ref
val thread_done : bool
val launch : 'a * 'b * 'c * ('a -> 'b -> 'd -> 'e) * ('c -> 'd) -> unit
val launch_str : Grid.t -> Grid.t -> int -> string -> string -> unit
val solve' : Npuzzle.t -> unit
val solve : Npuzzle.t -> unit
val test : Npuzzle.t -> unit
val poll_event : 'a -> EventHandler.t
val abort : 'a -> unit
val generate_grid : int -> bool -> int -> Grid.t
val algorithm_list : 'a -> string list
val heuristic_list : 'a -> string list
val transposition_toreal : int -> int array
val transposition_toabstract : int -> int array
