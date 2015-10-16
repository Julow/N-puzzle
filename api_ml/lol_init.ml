
exception LolError of string

let () =
	Callback.register_exception "lol_error" (LolError "lol")
