(* Wordle + Fibble Game in OCaml *)

type color = Green | Yellow | Gray

let word_list = ref [||]

(* Load word list from file *)
let load_word_list filename =
  let ic = open_in filename in
  let rec read_words acc =
    try
      let word = String.lowercase_ascii (String.trim (input_line ic)) in
      if String.length word = 5 then read_words (word :: acc)
      else read_words acc
    with End_of_file ->
      close_in ic;
      Array.of_list acc
  in
  word_list := read_words []

let get_random_word () =
  Random.self_init ();
  !word_list.(Random.int (Array.length !word_list))

let string_to_list s =
  List.init (String.length s) (String.get s)

let is_valid_word word =
  String.length word = 5 &&
  String.for_all (fun c -> c >= 'a' && c <= 'z') word &&
  Array.exists ((=) word) !word_list

let check_guess target guess =
  let target_chars = string_to_list target in
  let guess_chars = string_to_list guess in
  let target_counts = Hashtbl.create 26 in

  List.iter2 (fun t g ->
    if t <> g then
      let count = try Hashtbl.find target_counts t with Not_found -> 0 in
      Hashtbl.replace target_counts t (count + 1)
  ) target_chars guess_chars;

  let feedback = Array.make 5 Gray in

  List.iteri (fun i (t, g) ->
    if t = g then feedback.(i) <- Green
  ) (List.combine target_chars guess_chars);

  List.iteri (fun i g ->
    if feedback.(i) = Gray then
      let count = try Hashtbl.find target_counts g with Not_found -> 0 in
      if count > 0 then begin
        feedback.(i) <- Yellow;
        Hashtbl.replace target_counts g (count - 1)
      end
  ) guess_chars;

  Array.to_list feedback

(* FIBBLE: randomly lie about one feedback color *)
let apply_fibble_lie feedback =
  let i = Random.int 5 in
  let lied = List.mapi (fun idx color ->
    if idx = i then
      match color with
      | Green -> if Random.bool () then Yellow else Gray
      | Yellow -> if Random.bool () then Green else Gray
      | Gray -> if Random.bool () then Green else Yellow
    else color
  ) feedback in
  lied

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

let print_legend () =
  print_endline "\n  Legend:";
  print_endline "  \027[42mG\027[0m = Correct letter in correct position";
  print_endline "  \027[43mY\027[0m = Correct letter in wrong position";
  print_endline "  \027[47mX\027[0m = Letter not in word"

let rec game_loop ~fibble target max_attempts attempt =
  if attempt > max_attempts then begin
    print_endline "\n❌ Game Over!";
    Printf.printf "The word was: %s\n" (String.uppercase_ascii target);
    false
  end else begin
    Printf.printf "Attempt %d/%d: " attempt max_attempts;
    flush stdout;
    let guess = String.lowercase_ascii (read_line ()) in

    if not (is_valid_word guess) then begin
      print_endline "⚠️  Invalid word. Must be 5 lowercase letters and in the word list.\n";
      game_loop ~fibble target max_attempts attempt
    end else begin
      let feedback = check_guess target guess in
      let feedback = if fibble then apply_fibble_lie feedback else feedback in
      print_feedback guess feedback;

      if guess = target then begin
        print_endline "\n🎉 Congratulations! You guessed the word!";
        Printf.printf "You won in %d attempt(s)!\n" attempt;
        true
      end else begin
        print_newline ();
        game_loop ~fibble target max_attempts (attempt + 1)
      end
    end
  end

let rec play_game () =
  print_endline "\nChoose mode: (1) Wordle, (2) Fibble";
  print_string "> ";
  flush stdout;
  let mode = read_line () in
  let fibble = mode = "2" in
  let max_attempts = if fibble then 9 else 6 in
  let target = get_random_word () in

  print_endline "\n=================================";
  Printf.printf "       %s - OCaml Edition\n"
    (if fibble then "FIBBLE" else "WORDLE");
  print_endline "=================================";
  print_legend ();
  Printf.printf "\nGuess the 5-letter word! You have %d attempts.\n\n" max_attempts;

  let _ = game_loop ~fibble target max_attempts 1 in

  print_endline "\n=================================";
  print_string "Play again? (y/n): ";
  flush stdout;
  let answer = read_line () in
  if answer = "y" || answer = "Y" then play_game ()

let () =
  load_word_list "words.txt";  (* must be a file with 5-letter words, lowercase, one per line *)
  play_game ()
