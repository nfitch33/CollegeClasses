(* Wordle Game Implementation in OCaml *)

(* Color type for letter feedback *)
type color = Green | Yellow | Gray

(* Word list - a small sample, extend as needed *)
let word_list = [|
  "about"; "after"; "again"; "angel"; "angry"; "apple"; "beach"; "bread";
  "bring"; "chair"; "cheap"; "chess"; "claim"; "clean"; "clear"; "close";
  "dance"; "dream"; "drink"; "early"; "earth"; "enter"; "first"; "fleet";
  "force"; "frame"; "fresh"; "front"; "fruit"; "grand"; "grass"; "great";
  "green"; "heart"; "heavy"; "horse"; "house"; "japan"; "knife"; "large";
  "learn"; "light"; "might"; "money"; "month"; "never"; "night"; "ocean";
  "other"; "paper"; "party"; "peace"; "phone"; "place"; "plant"; "point";
  "power"; "press"; "price"; "pride"; "print"; "quick"; "quiet"; "radio";
  "reach"; "right"; "round"; "scale"; "sense"; "shape"; "share"; "sharp";
  "sheep"; "sheet"; "shift"; "shine"; "short"; "sight"; "since"; "skill";
  "sleep"; "slide"; "small"; "smart"; "smile"; "snake"; "sound"; "space";
  "speak"; "speed"; "spend"; "spoke"; "sport"; "stand"; "start"; "state";
  "stone"; "store"; "storm"; "story"; "study"; "style"; "sweet"; "table";
  "their"; "there"; "these"; "thing"; "think"; "three"; "throw"; "touch";
  "tower"; "track"; "trade"; "train"; "treat"; "trial"; "trust"; "truth";
  "under"; "until"; "value"; "visit"; "voice"; "waste"; "watch"; "water";
  "where"; "which"; "while"; "white"; "whole"; "whose"; "woman"; "world";
  "would"; "write"; "wrong"; "young"; "ocaml"
|]

(* Get a random word from the list *)
let get_random_word () =
  Random.self_init ();
  word_list.(Random.int (Array.length word_list))

(* Convert string to char list *)
let string_to_list s =
  List.init (String.length s) (String.get s)

(* Check if a word is valid (5 letters, all lowercase) *)
let is_valid_word word =
  String.length word = 5 &&
  String.for_all (fun c -> c >= 'a' && c <= 'z') word

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
let rec play_game () =
  let target = get_random_word () in
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
      flush stdout;
      let guess = String.lowercase_ascii (read_line ()) in
      
      if not (is_valid_word guess) then begin
        print_endline "⚠️  Please enter a valid 5-letter word (lowercase letters only).\n";
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
  print_string "Play again? (y/n): ";
  flush stdout;
  let answer = read_line () in
  if answer = "y" || answer = "Y" then
    play_game ()

(* Entry point *)
let () =
  play_game ()