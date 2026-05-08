CS 2401 Spring 2024
# Lab 4: Dynamic Arrays and the Big 3
Due: Friday 2/16 at 11:59 PM
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.
***  

Type your answers to the questions listed into the answers.txt document provided.  

This lab explores two important aspects of dynamic memory management:
1. The first part deals with the Big 3 (destructor, copy constructor and assignment operator) that need to be overloaded for any class that holds dynamic memory.  
2. The second part deals with the bad_alloc exception and how it can be handled.  


## Part 1  
Use the main that I have given you and finish the Numbers class, both the class declaration and the function implementations. (For this lab function implementations can be done under the class declaration, in the same file).  

The class, Numbers, that you declare will have these private variables:  
    unsigned long * data;  
    std::size_t used;  
    std::size_t capactity;  

The functions should be:  
1.	A default constructor that sets up an initial array of 5 unsigned longs, sets capacity to 5 and used to 0.  
2.	An add function that receives an unsigned long as a parameter and puts it into the next available spot.  
3.	A resize function that is only called when the add function discovers that used == capacity. It should increase the size of the array by five.   
4.	A remove_last function that takes out the last thing added to the array. All you need to do for this is to decrement the used counter. You do not need to change the capacity.  
5.	A display function that prints out all the numbers in the array, separated by spaces.  

Declare these functions in the class declaration and implement them immediately below that. (You do not have to use two files).  

***  

Read and understand the main. Compile and run the program.  

On your Answer sheet write the answers to the following:  
**Q1:** What do you see?  
**Q2:** Is this a problem and why?  
**Q3:** What caused this to happen?  

Now, reopen the file where you defined the class, and add to your class an overloaded assignment operator. Remember that an assignment operator has three parts:  
1.	Check for self-assignment.  
2.	Delete the existing array.  
3.	Create a new array the same size as the one you’re copying from, copy the values for used and capacity, and copy all the data from the other array into the new one.  

Compile and run the program again without changing anything in the main.  

On your Answer sheet write the answers to the following:  
**Q4:** What do you see?  
**Q5:** Is it different from what you saw before?  
**Q6:** What caused this to happen – why is it different?  

## Part Two
In the main, uncomment the part 2 code.  

Note that reveal_address is NOT something that we would normally do - the application programmer has no need to know the address of the dynamic array, but I have included it here to help you see what is going on.  

On your Answer sheet:  
**Q7:** Write down the five addresses that are output and the byte count output.  
**Q8:** Can you tell how many bytes they are apart? Write down your best estimate. (Remember that these addresses appear in hexadecimal).  

Eventually this array would eat up all the computer’s memory and a bad_alloc exception would be “thrown” (and caught). Because modern computers have so much memory, we might wait a very long time for this to happen.  

The solution is to write a destructor for the class. Add a destructor now including, in addition to the correct delete command:  
    <pre>
    byte_count = byte_count – (capacity * sizeof(unsigned long)); 
    </pre>

Compile and run the program again.  

On your Answer sheet:  
**Q9:** What addresses did you see this time and how much are they apart from each other?  
**Q10:** What is the byte_count?  
**Q11:** Explain why adding the destructor resulted in this different behavior.  

**Your final GitHub repository should include:** Your updated numbers.h, the main program, and completed answers.txt file. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.
