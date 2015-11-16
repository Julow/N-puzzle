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
module Hash :
  sig
    type t = int
    val equal : int -> int -> bool
    val compare : int -> int -> int
    val make : int -> int -> int -> int
    val disass : int -> int * int * int
    val hash : 'a -> 'a
  end
module CurHashtbl :
  sig
    type key = Hash.t
    type 'a t = 'a Hashtbl.Make(Hash).t
    val create : int -> 'a t
    val clear : 'a t -> unit
    val reset : 'a t -> unit
    val copy : 'a t -> 'a t
    val add : 'a t -> key -> 'a -> unit
    val remove : 'a t -> key -> unit
    val find : 'a t -> key -> 'a
    val find_all : 'a t -> key -> 'a list
    val replace : 'a t -> key -> 'a -> unit
    val mem : 'a t -> key -> bool
    val iter : (key -> 'a -> unit) -> 'a t -> unit
    val fold : (key -> 'a -> 'b -> 'b) -> 'a t -> 'b -> 'b
    val length : 'a t -> int
    val stats : 'a t -> Hashtbl.statistics
  end
module CurQueue :
  sig
    type elem = Hash.t
    type t = BatHeap.Make(Hash).t
    val empty : t
    val size : t -> int
    val insert : t -> elem -> t
    val add : elem -> t -> t
    val merge : t -> t -> t
    val find_min : t -> elem
    val del_min : t -> t
    val of_list : elem list -> t
    val to_list : t -> elem list
  end
val prev : int ref
val sz_qelt : float
val sz_helt : float
val t : float ref
val loops : int ref
val prevg : int ref
val report : 'a * int * int ref * CurQueue.t ref * 'b CurHashtbl.t -> unit
val warn : int -> db -> int -> int -> Grid.t -> unit
val alloc_data : int -> int -> bytes
val init_mem_fields : Grid.matrix -> db -> int array * Grid.matrix * bytes
val init_containers :
  Grid.matrix * int ->
  db ->
  ('a * int) array -> 'a -> int array -> CurQueue.t ref * unit CurHashtbl.t
val garbage_collect :
  'a CurHashtbl.t ->
  int -> 'b * int * int ref * CurQueue.t ref * 'c CurHashtbl.t -> unit
val build : (int * int) array -> db -> Grid.matrix * int -> int -> bytes
