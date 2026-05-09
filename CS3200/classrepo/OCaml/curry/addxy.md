OCaml
```ocaml
let add x y = x + y;;

let curry_add x = fun y -> x + y;;
                     
let add_five = curry_add 5;;

let add x y = (curry_add x) y;;

add 3 4;;
```

JavaScript
```javascript
function add(x, y) {
    return x + y;
}

function curryAdd(x) {
    return function(y) {
        return x + y;
    };
}

print('Two ways of adding two numbers', add(4, 5), curryAdd(4)(5));
```
