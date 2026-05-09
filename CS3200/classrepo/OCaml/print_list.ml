open Printf
let a = [1;2;3;4;5;6;7;8]
let () = List.iter (printf "%d ") a
let b = ["One"; "Two"; "Three"; "Four"]
let () = List.iter (printf "%s ") b