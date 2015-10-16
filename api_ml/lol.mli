
(* A lol is a reference to an int value inside a table *)
type lol

(* Create a lol and assign it a value *)
external create : int -> lol = "hook_create_lol"

(* Assign a value to a lol *)
external set : lol -> int -> unit = "hook_set_lol"

(* Get a lol value *)
external get : lol -> int = "hook_get_lol"

(* Print a lol value *)
external print : lol -> unit = "hook_print_lol"

(* Return an invalid lol *)
external bad_lol : unit -> lol = "hook_bad_lol"
