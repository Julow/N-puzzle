module type HEURISTIC =
  sig type elt type fn = elt -> int type maker = int -> fn end
module type ORDEREDTYPE = sig type t val compare : t -> t -> int end
module type HEPATHFINDER =
  sig type graph val solve : graph -> graph -> (graph -> int) -> unit end
module type PATHFINDER_GRAPH =
  sig
    type t
    val cost : t -> t -> int
    val equal : t -> t -> bool
    val successors : t -> t list
    val print : t -> unit
  end
module type EVENT_HANDLER_STATE = sig type t end
module type EVENT_HANDLER =
  sig
    type state
    type report
    type t = Success of report | Failed of string | Progress of float | Empty
    val dumpq : unit -> unit
    val pushq : t -> unit
    val popq : unit -> t
    val clearq : unit -> unit
    val new_report : int -> report
    val tick_report : report -> int -> int -> int -> report
    val finalize_report : report -> state list -> report
  end
module type MAKE_EVENT_HANDLER =
  functor (State : EVENT_HANDLER_STATE) ->
    sig
      type state = State.t
      type report
      type t =
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
module type MAKE_HEPATHFINDER =
  functor
    (Graph : PATHFINDER_GRAPH) (EventHandler : sig
                                                 type state = Graph.t
                                                 type report
                                                 type t =
                                                     Success of report
                                                   | Failed of string
                                                   | Progress of float
                                                   | Empty
                                                 val dumpq : unit -> unit
                                                 val pushq : t -> unit
                                                 val popq : unit -> t
                                                 val clearq : unit -> unit
                                                 val new_report :
                                                   int -> report
                                                 val tick_report :
                                                   report ->
                                                   int ->
                                                   int -> int -> report
                                                 val finalize_report :
                                                   report ->
                                                   state list -> report
                                               end) ->
    sig
      type graph = Graph.t
      val solve : graph -> graph -> (graph -> int) -> unit
    end
