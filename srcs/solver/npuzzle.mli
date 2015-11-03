
type t

(* return initial grid size *)
val get_size : t -> int

(* retrieve a value from the initial grid *)
val get : t -> int -> int ->int

(* Update the progress bar *)
val put_progress : t -> float -> unit

(* Put a valid step *)
val put_step : t -> int array array -> unit
