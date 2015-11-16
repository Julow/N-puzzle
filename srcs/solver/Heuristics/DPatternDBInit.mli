type db =
  DPatternDB.db = {
  grid_w : int;
  input_id : int;
  nbrs : int list;
  n_nbrs : int;
  paddings : int array;
  data : bytes;
}
type t =
  DPatternDB.t = {
  dbs : db array;
  ownerships : (int * int) array;
  mirror_ownerships : (int * int) array;
}
val fact_div : int -> int -> int
val mirror : int -> int -> int
val get : bytes -> int -> int
val set : bytes -> int -> int -> unit
val qprintf : ('a, out_channel, unit) format -> 'a
val print_one : db -> unit
val print : t -> unit
val retreive_indices_of_pos : int array -> unit
val index_of_pos : db -> int array -> int
val retreive_dbs_pos :
  Grid.matrix ->
  (int * int) array ->
  int array array -> (int * int) array -> int array array -> unit
val retreive_db_pos :
  Grid.matrix -> ('a * int) array -> 'a -> int array -> unit
val retreive_pos_of_indices : int array -> unit
val retreive_indices_of_index : int array -> int -> int array -> unit
val retreive_mat_of_indexpiv :
  int -> int -> 'a -> db -> int array -> int array array -> unit
val goal_pattern : db -> Grid.matrix * int
val fill_datas : t -> db array
val build_paddings : int -> int -> int array
val init_pattern_structure : Grid.matrix -> db list
val build_ownerships : db array -> (int * int) array
val build_mirror_ownerships : db array -> (int * int) array
val build : Grid.matrix -> t
