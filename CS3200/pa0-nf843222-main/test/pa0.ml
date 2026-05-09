open Pa0__Lib

(* Run it *)
let () =
  Alcotest.run "PA0"
    [
      ( "PA0",
        [
          Alcotest.test_case "eucl_dist" `Quick test_eucl_dist;
          Alcotest.test_case "bool_and" `Quick test_bool_and;
          Alcotest.test_case "bool_or" `Quick test_bool_or;
          Alcotest.test_case "maj" `Quick test_maj;
          Alcotest.test_case "hello_world" `Quick test_hello_world;
          Alcotest.test_case "fib" `Quick test_fib;
      ] )
    ]
