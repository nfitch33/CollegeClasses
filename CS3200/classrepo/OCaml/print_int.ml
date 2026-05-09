module type ToString = sig
  type t
  val to_string: t -> string
end

module Print (M : ToString) = struct
  (* effects: print a string representation of [M.t] *)
  let print v = print_string (M.to_string v)
end

module PrintEndline (M : ToString) = struct
  (* effects: print a string representation of [M.t] *)
  let print v = 
    print_string (M.to_string v);
    print_endline ""
end

module Int = struct
  type t = int
  let to_string = string_of_int
end

module PrintInt = Print(Int)

module PrintIntEndline = PrintEndline(Int)

let _ = PrintInt.print 2;;

let _ = PrintInt.print 5;;
let _ = PrintInt.print 100;;

print_endline "";;

let _ = PrintIntEndline.print 2;;

let _ = PrintIntEndline.print 5;;
let _ = PrintIntEndline.print 100;;




module MyString = struct
  type t = string
  let to_string s = s
end

module PrintString = Print(MyString)
let _ = PrintString.print "Harambe" ;;


print_endline "";;
