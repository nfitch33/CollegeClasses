(* Wordle Game Implementation in OCaml with Official Word Lists *)
(* This is an incomplete implementation - search for "failwith" to see what's left out. *)

(* Compile with command `ocamlfind ocamlc -linkpkg -package unix -o Wordle2 Wordle2.ml` *)

open Unix

(* Because try.ocamlpro.com runs in a browser, it cannot do anything in the Unix module. 
   To try the following code out, you can use `utop`. *)

(* Color type for letter feedback *)
type color = Green | Yellow | Gray

(* URLs for official Wordle word lists *)
let answers_url = "https://gist.githubusercontent.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b/raw/5d752e5f0702da315298a6bb5a771586d6ff445c/wordle-answers-alphabetical.txt"
let guesses_url = "https://gist.githubusercontent.com/cfreshman/cdcdf777450c5b5301e439061d29694c/raw/de1df631b45492e0974f7affe266ec36fed736eb/wordle-allowed-guesses.txt"

(* Download word list from URL using curl *)
(* https://ocaml.org/manual/5.3/api/Array.html *)
let download_word_list url =
  let cmd = Printf.sprintf "curl -s '%s'" url in
  let ic = Unix.open_process_in cmd in
  let rec read_lines acc =
    try
      let line = input_line ic in
      let word = String.lowercase_ascii (String.trim line) in
      if String.length word = 5 then
        read_lines (word :: acc)
      else
        read_lines acc
    with End_of_file -> acc
  in
  let words = read_lines [] in
  let _ = Unix.close_process_in ic in
  Array.of_list (List.rev words)

(* Load word lists *)
let load_word_lists () =
  print_endline "Loading Wordle word lists...";
  flush Stdlib.stdout;
  let answers = download_word_list answers_url in
  let guesses = download_word_list guesses_url in
  print_endline (Printf.sprintf "✓ Loaded %d possible answers and %d allowed guesses\n" 
    (Array.length answers) (Array.length guesses));
  (answers, guesses)

(* Create a hash set from array for fast lookup *)
(* https://ocaml.org/manual/5.3/api/Hashtbl.html *)
let make_word_set arr =
  let tbl = Hashtbl.create (Array.length arr) in
  Array.iter (fun word -> Hashtbl.add tbl word ()) arr;
  tbl

(* Get a random word from the answer list *)
let get_random_word answers =
  Random.self_init ();
  answers.(Random.int (Array.length answers))

(* Convert string to char list *)
let string_to_list s =
  List.init (String.length s) (String.get s)

(* Check if a word is valid (5 letters, all lowercase) *)
let is_valid_word word =
  String.length word = 5 &&
  String.for_all (fun c -> c >= 'a' && c <= 'z') word

(* Check if word is in allowed guesses *)
let is_allowed_guess word answers_set guesses_set =
  failwith "TO BE Implemented: is_allowed_guess"

(* Compare guess with target and return feedback *)
let check_guess target guess =
  let target_chars = string_to_list target in
  let guess_chars = string_to_list guess in
  
  (* Count remaining letters in target after marking greens *)
  let target_counts = Hashtbl.create 26 in
  List.iter2 (fun t g ->
    if t <> g then
      let count = try Hashtbl.find target_counts t with Not_found -> 0 in
      Hashtbl.replace target_counts t (count + 1)
  ) target_chars guess_chars;
  
  (* First pass: mark green (correct position) *)
  let feedback = Array.make 5 Gray in
  List.iteri (fun i (t, g) ->
    if t = g then feedback.(i) <- Green
  ) (List.combine target_chars guess_chars);
  
  (* Second pass: mark yellow (wrong position) *)
  List.iteri (fun i g ->
    if feedback.(i) = Gray then
      let count = try Hashtbl.find target_counts g with Not_found -> 0 in
      if count > 0 then begin
        feedback.(i) <- Yellow;
        Hashtbl.replace target_counts g (count - 1)
      end
  ) guess_chars;
  
  Array.to_list feedback

(* Print colored output *)
let print_feedback guess feedback =
  print_string "  ";
  List.iteri (fun i color ->
    let c = String.get guess i in
    match color with
    | Green -> Printf.printf "\027[42m\027[30m %c \027[0m " (Char.uppercase_ascii c)
    | Yellow -> Printf.printf "\027[43m\027[30m %c \027[0m " (Char.uppercase_ascii c)
    | Gray -> Printf.printf "\027[47m\027[30m %c \027[0m " (Char.uppercase_ascii c)
  ) feedback;
  print_endline ""

(* Print legend *)
let print_legend () =
  print_endline "\n  Legend:";
  print_endline "  \027[42mG\027[0m = Correct letter in correct position";
  print_endline "  \027[43mY\027[0m = Correct letter in wrong position";
  print_endline "  \027[47mX\027[0m = Letter not in word"

(* Main game loop *)
let rec play_game answers answers_set guesses_set =
  let target = get_random_word answers in
  let max_attempts = 6 in
  
  print_endline "\n=================================";
  print_endline "       WORDLE - OCaml Edition";
  print_endline "=================================";
  print_legend ();
  print_endline "\nGuess the 5-letter word!";
  print_endline "You have 6 attempts.\n";
  
  let rec game_loop attempt =
    if attempt > max_attempts then begin
      print_endline "\n❌ Game Over!";
      Printf.printf "The word was: %s\n" (String.uppercase_ascii target);
      false
    end else begin
      Printf.printf "Attempt %d/%d: " attempt max_attempts;
      flush Stdlib.stdout;
      let guess = String.lowercase_ascii (read_line ()) in
      
      if not (is_valid_word guess) then begin
        print_endline "⚠️  Please enter a valid 5-letter word (lowercase letters only).\n";
        game_loop attempt
      end else if not (is_allowed_guess guess answers_set guesses_set) then begin
        print_endline "⚠️  Not in word list. Try a different word.\n";
        game_loop attempt
      end else begin
        let feedback = check_guess target guess in
        print_feedback guess feedback;
        
        if guess = target then begin
          print_endline "\n🎉 Congratulations! You guessed the word!";
          Printf.printf "You won in %d attempt(s)!\n" attempt;
          true
        end else begin
          print_newline ();
          game_loop (attempt + 1)
        end
      end
    end
  in
  
  let _ = game_loop 1 in
  
  print_endline "\n=================================";
  print_string "Play again? (y/[n]): ";
  flush Stdlib.stdout;
  let answer = read_line () in
  if answer = "y" || answer = "Y" then
    play_game answers answers_set guesses_set

(* Entry point *)
let () =
  try
    let (answers, guesses) = load_word_lists () in
    let answers_set = make_word_set answers in
    let guesses_set = make_word_set guesses in
    play_game answers answers_set guesses_set
  with
  | Unix.Unix_error (err, fn, param) ->
      Printf.eprintf "Error: %s (%s: %s)\n" (Unix.error_message err) fn param;
      Printf.eprintf "Make sure you have curl installed and internet connection.\n";
      exit 1
  | e ->
      Printf.eprintf "Error: %s\n" (Printexc.to_string e);
      exit 1
