open OUnit2 

(* To compile and run, use: 
  % dune build
  % dune exec ./recursive_function.exe
or 
  % ocamlfind ocamlc -o recursive_function -package oUnit,num -linkpkg -g recursive_function.ml
  % ./recursive_function

Before you submit, make sure that your code can be compiled with both ways and produces no warnings.
*)

(* Fill in your name and PID on the lines below. *)

let name = "Nathaniel Fitch";;
let id = "P101093645";;
let _ = Printf.printf "\n========= NAME: %s  ID: %s ========= \n" name id;;
let _ = Printf.printf "\n+++++++++++++++++++++++++++++ Recursive function Problem +++++++++++++++++++++++++++++ \n";;

let ____todo____ (type t) (x : t) : 'a =
  let module M = struct exception Todo of t end in
  raise @@ M.Todo x
;;

(* Problem Description: 

Function f(n) is a recursively defined sequence where the value of f(n) 
depends on the values of three preceding terms: f(n-1), f(n-2), and f(n-3).
The sequence is initialized with the following base cases:
  f(0)=1
  f(1)=2
  f(2)=3
For n≥3, the sequence is defined by the following recursive formula: 
  f(n)= f (n-1) - 2 * f(n-2) + 3 * f (n-3)
The recursive nature of the function means that each value is calculated based on the preceding three values.
Implement f(n) below so that it can compute up to f(400_000) efficiently. 
To ensure whether one uses OCaml int or big numbers, the same test cases would work, the parameter type must be integer and the return type must be string.

CHECK IN a file named "recursive_function_results.txt" or ".png" with the result of your test execution to show how many test cases you manage to pass. 

BONUS: Check in a file named "recursive_function_largest.txt" with the largest f(n) you can compute. State both n and how long it takes for you to compute it. 
Note that n must be 1 million. If your n is so large that you require a big number to store n, you will get a bonus credit of 25% of the final exam.
Otherwise, the largest n produced by the class gets the 25% bonus.
*)


(* The following functions are auxilliary functions for your convenience. *)

(* let digit_count i = String.length (string_of_int i) *)
let stable_hash s = Digest.to_hex (Digest.string s);; (* generates MD5-based digests *)

(*
let stable_hash_num n = let s = string_of_num n in Digest.to_hex (Digest.string s);; (* generates MD5-based digests *)
*)

(* naive implementation of f(n) 
You can use this naive function to verify if your result is correct. Note that this naive function will not be able to compute any big f(n) within a reasonable amount of time.
*)
let rec fnaive = function
      | 0 -> "1"  (* Base case: f(0) = 1 *)
      | 1 -> "2"  (* Base case: f(1) = 2 *)
      | 2 -> "3"  (* Base case: f(2) = 3 *)
      | n -> string_of_int ((int_of_string (fnaive (n - 1))) - ( 2 * (int_of_string (fnaive (n - 2)))) + (3 * (int_of_string (fnaive (n - 3))) ))
;;

let f10 = fnaive 10;;
let f10_digit = String.length f10;;
let f10_md5 = stable_hash f10;;

Printf.printf "Example: f(%d) is: %s, has %d digits, md5:%s\n" 10 f10 f10_digit f10_md5;;



(* Replace the following TODO and fnaive with your efficient implementation of f(n) *)
let f (n : int) : string = 
  (*
    ____todo____ (f, n, digit_count, digit_count_num, stable_hash, stable_hash_num, memo_table)    (*2*)
  *)
  
    fnaive n
  ;;
  


let testing n expected _ =
  let result = f n in
    (* Print expected and actual results for debugging *)
      Printf.printf "\nTest case: n = %d, Expected = %s, Actual = %s" n expected result;
      assert_equal (String.trim expected) (String.trim result) ~printer:(fun x -> x)
;;

let testing_md5 n expected_digits expected_md5 _ =
  let result = f n in
    (* Print expected and actual results for debugging *)
      Printf.printf "\nTest case: n = %d, Expected = %d digits, Actual = %d digits, Expected MD5=%s, Actual MD5=%s" n expected_digits (String.length result) expected_md5 (stable_hash result);
      assert_equal expected_digits (String.length result) ~printer:string_of_int;
      assert_equal expected_md5 (stable_hash result)
;;

let _suite1 = 
  "Suite 1" >:::
    [
      "n = 0" >:: testing 0 "1";
      "n = 1" >:: testing 1 "2";
      "n = 2" >:: testing 2 "3";
      "n = 3" >:: testing 3 "2";
      "n = 4" >:: testing 4 "2";
      "n = 5" >:: testing 5 "7";
      "n = 6" >:: testing 6 "9";
      "n = 10" >:: testing 10 "24";
      "n = 10 md5" >:: testing_md5 10 2 "1ff1de774005f8da13f42943881c655f";
      "n = 11" >:: testing 11 "-22";
      "n = 20" >:: testing 20 "1301";
      "n = 20 md5" >:: testing_md5 20 4 "2df45244f09369e16ea3f9117ca45157";
    ]
;;

(* suite2 contains large test cases. Your program will hang if your algorithm is not efficient. *) 
let suite2 = 
  "Suite 2" >:::
    [
      "n = 0" >:: testing 0 "1";
      "n = 1" >:: testing 1 "2";
      "n = 2" >:: testing 2 "3";
      "n = 3" >:: testing 3 "2";
      "n = 4" >:: testing 4 "2";
      "n = 5" >:: testing 5 "7";
      "n = 6" >:: testing 6 "9";
      "n = 10" >:: testing 10 "24";
      "n = 10 md5" >:: testing_md5 10 2 "1ff1de774005f8da13f42943881c655f";
      "n = 11" >:: testing 11 "-22";
      "n = 15" >:: testing 15 "-182";
      "n = 19" >:: testing 19 "-1009";
      "n = 20" >:: testing 20 "1301";
      "n = 20 md5" >:: testing_md5 20 4 "2df45244f09369e16ea3f9117ca45157";
      "n = 21 md5" >:: testing_md5 21 4 "75e33da9b103b7b91dcd8da0abe1354b";
      "n = 22 md5" >:: testing_md5 22 5 "7eb41fc3b83e029850c01395eb637514";
      "n = 30" >:: testing 30 "-142101";
      "n = 100" >:: testing 100 "1437218441793916751";
      "n = 100 md5" >:: testing_md5 100 19 "39cf9251fb3bbdabd0680673e89c42d9";
      "n = 1000" >:: testing 1000 "140887725299220562350139379193289151984871105869103605530133315544694603209171489036876426625324642294645325574003969491470704938532884234000265027114431223832106199271295072658190867501";
      "n = 10000" >:: testing 10000 "109069389382265754043753554965417443183882459533774940223213648441148388168633475182710944086812038973423837398158164376005920168093024417700536153727855355745379766753844091157309315088472932104752951442034579659500842717181899261529109572286232632685117077895032965532356166772959770815687900578352516521838987050772390308910191061586908255338009121741153433191172303533392626396715441104806520871862213476836318354044612511838945072931722731741819200578771997809777490820620537239439190838954939048142046250814499205403118899042807339996691392952820423771276774239920718838138401799876858341100701735981037177302906284654063193990699763674008253854371971423731771670752490930470862576830075338767454547767696734737974636917292981907266300826227991159476667837079783027761541481002738261903581654206381190268260541068651443648414926604820136586090990733513742369076805968440584283523982114585210741191528157354573738441988296963756608199229394600683358017768482859982045165211031993602657066439938739165863656761858206257586483537105911595480542944090558579733164667343230402147326823564217234952265709240723340063542493109218861012041989303826380812375816676708235480607609187804080236130344666419073765866636481945534375255079796484943111110290863285060191167175163609190668837051669531883059144517135940839076094817626145209353320199100071501067904123997704691402049611805877801803139539833376715581710077118962004702615532662788201106272938802675705311602661468372194869161271078091803715539779506385929655286313012407776820899373975238081850365903509816688399268256814558623553728354715186331885095279502748579302268522253389145896557269728779874032601394014226967952481215084991701791551307000319176115769741974581737656063222809490103005413678668289904773999025934449235844738149519696284915625470514146679602755777383756912428041620553992322815626";
      "n = 100000 md5" >:: testing_md5 100000 18569 "4ab1424beadae88a074c3d0f39bc5345";
      "n = 200000 md5" >:: testing_md5 200000 37139 "3ca460b8d642f458cb0964bf85e0f7b9";
      "n = 300000 md5" >:: testing_md5 300000 55707 "b74d7ee8f827a025720b318f02958d72";
      "n = 400000 md5" >:: testing_md5 400000 74277 "f3dbaa6e5e88a65add6427835d59e690";
      "n = 500000 md5" >:: testing_md5 500000 92845 "3e357e38e2750a5a4f0e279b67024143";
      "n = 600000 md5" >:: testing_md5 600000 111415 "82f72877963dfd721f22ae0e46dec478";
      "n = 1000000 md5" >:: testing_md5 1000000 185690 "aac2225d8e8980291062a20972feaf75";
    ]

(* Run the test suite - replace suite1 with suite2*)
let () = 
   run_test_tt_main suite2
;;

(* Comment out or delete the rest of the reminder code once you start to use suite2 for testing *)

(* Function to count the number of test cases in a test *)
let rec count_test_cases (test : OUnit2.test) : int =
  match test with
  | TestCase _ -> 1  (* A single test case *)
  | TestList tests -> List.fold_left (fun acc t -> acc + count_test_cases t) 0 tests
  | TestLabel (_, t) -> count_test_cases t  (* Ignore label, just count the inner test *)
;;

let rec collect_labels (test : OUnit2.test) : string list =
  match test with
  | TestCase _ -> []  (* No label associated directly with a TestCase *)
  | TestList tests -> List.flatten (List.map collect_labels tests)  (* Collect labels from all tests in the list *)
  | TestLabel (label, t) -> label :: collect_labels t  (* Add the label and continue collecting from the inner test *)
;;

Printf.printf "Make sure you test with the following %d test cases in suite2. \n" (count_test_cases suite2) ;
let labels = collect_labels suite2 in
  List.iter print_endline labels

