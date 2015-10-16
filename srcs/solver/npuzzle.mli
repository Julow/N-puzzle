
type t

(* return initial grid size *)
external get_size : t -> int = "solver_hook_get_size"

(* retrieve a value from the initial grid *)
external get : t -> int -> int -> int = "solver_hook_get"

(* TODO: get_algo (VARIANT) *)
(* TODO: get_heuristic (VARIANT) *)

(* Update the progress bar *)
external put_progress : t -> float -> unit = "solver_hook_put_progress"

(* Put a valid step *)
external put_step : t -> int array array -> unit = "solver_hook_put_step"
