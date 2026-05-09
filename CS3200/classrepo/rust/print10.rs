fn main() {
    let mut list = Vec::new();

    // Push 10 elements onto the list
    for i in 0..10 {
        list.push(i);
    }

    // Print the list
    for i in &list {
        println!("{}", i);
    }
}