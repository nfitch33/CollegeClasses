(* Define a type for days of the week *)
type day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday

(* Create a list of all days *)
let days_of_week = [Monday; Tuesday; Wednesday; Thursday; Friday; Saturday; Sunday]

(* Function to convert day to string *)
let day_to_string = function
  | Monday -> "Monday"
  | Tuesday -> "Tuesday"
  | Wednesday -> "Wednesday"
  | Thursday -> "Thursday"
  | Friday -> "Friday"
  | Saturday -> "Saturday"
  | Sunday -> "Sunday"

(* Function to check if a day is a weekend *)
let is_weekend day =
  match day with
  | Saturday | Sunday -> true
  | _ -> false

(* Function to get next day *)
let next_day day =
  match day with
  | Monday -> Tuesday
  | Tuesday -> Wednesday
  | Wednesday -> Thursday
  | Thursday -> Friday
  | Friday -> Saturday
  | Saturday -> Sunday
  | Sunday -> Monday

(* Main function to demonstrate list operations *)
let main () =
  (* Print all days *)
  print_endline "All days of the week:";
  List.iter (fun day -> print_endline (day_to_string day)) days_of_week;
  
  (* Print weekend days *)
  print_endline "\nWeekend days:";
  List.filter is_weekend days_of_week
  |> List.iter (fun day -> print_endline (day_to_string day));
  
  (* Print next day after Wednesday *)
  print_endline "\nDay after Wednesday:";
  let wednesday = List.nth days_of_week 2 in
  print_endline (day_to_string (next_day wednesday))

(* Run the main function *)
let () = main ()