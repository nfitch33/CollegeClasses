fn main() {
    let mut message = String::from("Hello, World!");

    // Create a reference to the message
    let message_reference = &mut message;

    // Print the message using the reference
    println!("The message is: {}", message_reference);

    // Try to modify the message through the reference
    // This will cause an error because the reference does not own the message

    message_reference.push_str("!");
    println!("The message is: {}", message_reference);
}
