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
val solve : Npuzzle.t -> int -> int -> int -> unit
val test : Npuzzle.t -> unit
val poll_event : 'a -> EventHandler.t
val abort : 'a -> unit
val generate_grid : int -> bool -> int -> Grid.t
val algorithm_list : 'a -> string list
val heuristic_list : 'a -> string list
val transposition_toreal : int -> int array
val transposition_toabstract : int -> int array
