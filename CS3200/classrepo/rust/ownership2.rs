fn main() {
    let  message = String::from("Hello, World!");

    // Create a reference to the message
    let message_reference = &message;
    
    // Create a new String from the reference
    let  new_message = String::from(message_reference);
    

    // Modify the new String
    new_message.push_str("!");
    
    // Print the new String
    println!("The new message is: {}", new_message);
    
}
