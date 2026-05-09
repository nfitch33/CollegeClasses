let rec fibonacci n =
  if n < 2 then n else fibonacci (n - 1) + fibonacci (n - 2) in

let fib = fibonacci 10 in

let _ = print_int(fib) in
  print_string("\n")  