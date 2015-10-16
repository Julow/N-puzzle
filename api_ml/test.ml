
let do_lol a =
	let lol = Lol.create a in
	let lol_val = Lol.get lol in
	Lol.print lol;
	print_string " -> ";
	print_int lol_val;
	print_newline ();
	Lol.set lol 42

let () =
	Callback.register "do_lol" do_lol
