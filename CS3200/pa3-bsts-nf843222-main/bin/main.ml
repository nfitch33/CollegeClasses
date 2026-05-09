open Pa3__Lib

let () =
  print_endline (String.concat ", " (List.map (string_of_int) (dedup [6; 6])))
