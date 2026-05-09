(* Wordle + Fibble in OCaml *)

(* Compile with:
   ocamlfind ocamlc -linkpkg -package unix,str -o wordle wordle.ml
*)

module StringSet = Set.Make(String)

(* Colors for feedback *)
type color = Green | Yellow | Gray

(* Convert color to string (with ANSI colors) *)
let color_to_ansi = function
  | Green -> "\027[42m\027[30m G \027[0m"
  | Yellow -> "\027[43m\027[30m Y \027[0m"
  | Gray -> "\027[47m\027[30m X \027[0m"

(* URLs for official Wordle word lists *)
let answers_url = "https://gist.githubusercontent.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b/raw/5d752e5f0702da315298a6bb5a771586d6ff445c/wordle-answers-alphabetical.txt"
let guesses_url = "https://gist.githubusercontent.com/cfreshman/cdcdf777450c5b5301e439061d29694c/raw/de1df631b45492e0974f7affe266ec36fed736eb/wordle-allowed-guesses.txt"

(* Download word list using curl *)
let download_word_list url =
  let cmd = Printf.sprintf "curl -s '%s'" url in
  let ic = Unix.open_process_in cmd in
  let rec loop acc =
    try
      let line = input_line ic |> String.trim |> String.lowercase_ascii in
      if String.length line = 5 then loop (line :: acc)
      else loop acc
    with End_of_file -> List.rev acc
  in
  let words = loop [] in
  ignore (Unix.close_process_in ic);
  words

(* Add "ocaml" as a valid word (answer + guess) *)
let add_ocaml lst =
  if List.mem "ocaml" lst then lst else "ocaml" :: lst

(* Build sets for quick lookup *)
let make_set lst =
  List.fold_left (fun acc w -> StringSet.add w acc) StringSet.empty lst

(* Convert string to char list *)
let string_to_char_list s =
  let rec aux i acc =
    if i < 0 then acc else aux (i - 1) (s.[i] :: acc)
  in
  aux (String.length s - 1) []

(* Check if a guess is allowed *)
let is_allowed_guess word answers_set guesses_set =
  StringSet.mem word answers_set || StringSet.mem word guesses_set

(* Check if a word is valid: length 5, lowercase letters *)
let is_valid_word w =
  String.length w = 5 &&
  String.for_all (fun c -> c >= 'a' && c <= 'z') w

(* Compare guess with target and generate feedback *)
let check_guess target guess =
  let t_chars = string_to_char_list target in
  let g_chars = string_to_char_list guess in

  (* Count occurrences of letters in target, ignoring greens *)
  let counts = Hashtbl.create 26 in
  List.iter2 (fun t g -> if t <> g then
      Hashtbl.replace counts t (1 + (try Hashtbl.find counts t with Not_found -> 0))
    ) t_chars g_chars;

  (* First pass: mark greens *)
  let feedback = Array.make 5 Gray in
  List.iteri (fun i (t, g) -> if t = g then feedback.(i) <- Green) (List.combine t_chars g_chars);

  (* Second pass: mark yellows *)
  List.iteri (fun i g ->
    if feedback.(i) = Gray then
      match (try Some (Hashtbl.find counts g) with Not_found -> None) with
      | Some c when c > 0 ->
          feedback.(i) <- Yellow;
          Hashtbl.replace counts g (c - 1)
      | _ -> ()
  ) g_chars;

  Array.to_list feedback

(* Print feedback for a guess *)
let print_feedback guess feedback =
  print_string "  ";
  List.iteri (fun i color ->
      let c = Char.uppercase_ascii guess.[i] in
      match color with
      | Green -> Printf.printf "\027[42m\027[30m %c \027[0m " c
      | Yellow -> Printf.printf "\027[43m\027[30m %c \027[0m " c
      | Gray -> Printf.printf "\027[47m\027[30m %c \027[0m " c
    ) feedback;
  print_endline ""

(* Print legend *)
let print_legend () =
  print_endline "\n  Legend:";
  print_endline "  \027[42mG\027[0m = Correct letter in correct position";
  print_endline "  \027[43mY\027[0m = Correct letter in wrong position";
  print_endline "  \027[47mX\027[0m = Letter not in word"

(* Flip one color in feedback to introduce a lie for Fibble mode *)
let fibble_lie feedback =
  let len = List.length feedback in
  if len = 0 then feedback else
  let idx = Random.int len in
  let flip_color = function
    | Green -> Yellow
    | Yellow -> Gray
    | Gray -> Yellow
  in
  List.mapi (fun i c -> if i = idx then flip_color c else c) feedback

(* Read a line with prompt *)
let read_line_prompt prompt =
  print_string prompt;
  flush stdout;
  read_line ()

(* Main game loop - must be recursive because it calls itself *)
let rec play_game answers answers_set guesses_set mode =
  let target = List.nth answers (Random.int (List.length answers)) in
  let max_attempts = if mode = "fibble" then 9 else 6 in
  Printf.printf "\n=== Welcome to %s mode! ===\n" (String.capitalize_ascii mode);
  print_legend ();
  print_endline "\nGuess the 5-letter word!";
  Printf.printf "You have %d attempts.\n\n" max_attempts;

  let rec loop attempt =
    if attempt > max_attempts then (
      Printf.printf "\n❌ Game Over! The word was: %s\n" (String.uppercase_ascii target);
      false
    ) else (
      let prompt = Printf.sprintf "Attempt %d/%d: " attempt max_attempts in
      let guess = String.lowercase_ascii (read_line_prompt prompt) in

      if not (is_valid_word guess) then (
        print_endline "⚠️  Please enter a valid 5-letter word (lowercase letters only).\n";
        loop attempt
      ) else if not (is_allowed_guess guess answers_set guesses_set) then (
        print_endline "⚠️  Not in word list. Try a different word.\n";
        loop attempt
      ) else (
        let feedback = check_guess target guess in
        (* For Fibble, add a random lie *)
        let final_feedback = if mode = "fibble" then fibble_lie feedback else feedback in

        print_feedback guess final_feedback;

        if guess = target then (
          Printf.printf "\n🎉 Congratulations! You guessed the word in %d attempt(s)!\n" attempt;
          true
        ) else (
          print_newline ();
          loop (attempt + 1)
        )
      )
    )
  in

  let _ = loop 1 in

  print_endline "\n=================================";
  let answer = read_line_prompt "Play again? (y/[n]): " in
  if answer = "y" || answer = "Y" then play_game answers answers_set guesses_set mode else ()

(* Entry point *)
let () =
  Random.self_init ();
  print_endline "Loading word lists, please wait...";

  (* Download lists *)
  let answers_raw = download_word_list answers_url in
  let guesses_raw = download_word_list guesses_url in

  (* Add "ocaml" to both lists *)
  let answers = add_ocaml answers_raw in
  let guesses = add_ocaml guesses_raw in

  (* Build sets *)
  let answers_set = make_set answers in
  let guesses_set = make_set guesses in

  (* Select mode *)
  print_endline "Choose mode:";
  print_endline "1) Wordle (6 guesses, honest feedback)";
  print_endline "2) Fibble (9 guesses, one lie per feedback)";
  print_string "Enter 1 or 2: ";
  flush stdout;
  let mode =
    match read_line () with
    | "1" -> "wordle"
    | "2" -> "fibble"
    | _ -> print_endline "Invalid choice, defaulting to Wordle."; "wordle"
  in

  play_game answers answers_set guesses_set mode
