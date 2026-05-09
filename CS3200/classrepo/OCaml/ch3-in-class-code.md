https://try.ocamlpro.com/

```
let rec tail lst =
  match lst with
  | [] -> 0
  | h :: t -> if t = [] then h else tail t
          
let rec tail2 lst =
  match lst with
  | [] -> 0
  | h :: [] -> h
  | h :: t -> tail2 t

let _= tail2 [1; 2; 3]
let _ = tail2 []
let _ = tail2 [2; 3]
let _ = tail2 [3]

```
-------

```
let third lst = 
  match lst with 
  | [] ->  0
  | _ :: [] -> 0
  | _ :: second_ele :: [] -> second_ele
  | 1 :: second_ele :: third_ele :: _ -> second_ele
  | 2 :: _ :: third_ele :: _ -> third_ele 

let _= third [1; 2; 3]
let _= third [2; 2; 3]
    


let head = function 
  | [] -> 0
  | h :: t -> h

let _ = head [1 ; 2]

(*
let head lst = 
  match lst with 
  | [] -> 0
  | h :: t -> h


let rec gen = function
  | 0 -> []
  | 1 -> [1]
  | 2 -> [1; 2]
  | n -> append (gen (n-1)) [n]


let rec gen = function
  | 0 -> []
  | 1 -> [1]
  | 2 -> [1; 2]
  | n -> n :: (gen (n-1)) 


let rec append lst1 lst2 =
  match lst1 with
  | [] -> lst2
  | h :: t -> h :: append t lst2

                
let rec aux acc n =
  match n with
  | 0 -> acc
  | n -> aux (append [n] acc) (n-1) 
  
  
let _ = aux [] 2
let _ = aux [2] 1
let _ = aux [2; 1] 0
    
let gen n = aux [] n
  
let _ = gen 5000000

```
-------

```
let rec append lst1 lst2 =
  match lst1 with
  | [] -> lst2
  | h :: t -> h :: append t lst2

let rec aux acc = function
  | 0 -> acc
  | n -> aux (append [n] acc) (n-1) 
           
let _ = aux [] 3
let _ = aux [3] 2
let _ = aux [2; 3] 1
let _ = aux [1; 2; 3] 0
    
let gen n = aux [] n
  
let _ = gen 5000000
```
-------
```
let head = function 
  | [] -> 0
  | h :: t when h mod 2 = 0->  h
  | h :: t -> - h
    
let _=                head [1; 2]
let _=                head [2; 3]


let _ = List.init 10 (fun x -> x)
let _ = List.init 10 (fun x -> x * x)
let _ = List.init 30 (fun x -> x * 5)
```

```
let print_list lst =
  List.iter (fun x -> print_int x; print_string " ") lst
```

```
% List.iter2 applies a given function to the corresponding elements of two lists in parallel until the end of the shorter list is reached. If the lists have different lengths, it raises the Invalid_argument exception.
let print_pair x y = Printf.printf "(%d, %s)\n" x y;;
List.iter2 print_pair [1; 2; 3] ["a"; "b"; "c"];;

let _ = List.iter (fun x-> print_int x; print_string " " )  [20; 30; 60; 100]
  
let _ = List.iter2 (fun x y -> print_int x; print_string " "; print_int y;  print_string "; ") 
    [20; 30; 60; 100] [200; 300; 600; 1000]
```
