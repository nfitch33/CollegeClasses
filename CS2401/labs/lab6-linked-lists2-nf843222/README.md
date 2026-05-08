# Lab 6: Linked Lists 2
CS 2401 Spring 2024
Due: Friday 3/1 at 11:59 PM
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.
***  

In the main provided with this lab, you will see that I have created a linked list of random numbers. The numbers are in the range 1 to 500, but there are 2000 of them in the list, so there will be duplicates. You can also see that I am timing the code with time. (Although both of my functions are taking less than a second apiece.) Read through the code so that you see what it does.

## Assignment  
For this lab you are to implement two functions, and I have given you the prototypes for the
functions.

• The first function passes through the linked list and removes all duplicate items. You will
need at least two, most likely three, additional pointers to pull this off. Remember that
to remove an item you will need to hold onto the node before the one you are
removing. When you are done, the total size of the linked list should be <= 500. I have
given you a size function so you can check that. You should have the main call the
show_list function to print out this new smaller list.

• The second function takes the cleaned-up list, and a “split value,” which is a number
between 1 and 500 entered by the user. The function then creates two new lists, one
having only numbers greater than the split value and one having only numbers less than
the split value. The split value should not appear in either list. The sum of the size of
these two lists should be equal to or one less than the cleaned-up list you built with the
first function. (The first function alters the original list, and this function creates two
new lists.)

## Testing  
Please use the command 'make run_tests' to test your code before submitting. Any failed tests will give you hints as to why things failed. It is highly encouraged to test in a linux environment.

**Your final GitHub repository should include:** Your updated header_lab6.h and main_lab6.cc. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.