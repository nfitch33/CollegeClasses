CS 2401 – Spring 2024
# Project 4 – Template Classes and Doubly Linked Lists
Due: 11:59 PM Sunday, March 24th  

***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.  
**You may not use any libraries or constructs that we have not covered in class for this project**
***  

This list will be like the sequence class that we created for Project 2, but it will be implemented using a linked list, and the iterator will be done as an external iterator. This list will also be implemented as a template, allowing it to hold any type of data.    

Remember that in a doubly linked list, each node has a pointer pointing to the next node and another one pointing to the previous node. The last node's next pointer and first node's previous pointer should both be set to nullptr. This will require the definition of a different node class from what you used in project 3. So, you should start your project by making a Dnode class for nodes appropriate for use in a doubly linked list. Make this class template so it can hold any kind of data. You will need functions to access next, previous, and data as well as functions to set_next, set_previous and set_data. You should provide a constructor that uses default arguments that will set the pointers to nullptr.  

***  

Now using this node class, develop a template list class. You will need pointers for head and tail, and these may be the only private variables that you need. Your list class needs to have the following functions:  

* size
* show
* reverse_show
* front_insert  
* rear_insert  
* front_remove  
* rear_remove  

Remember to program incrementally. To help you with this I have written a file called main1.cc. When you first open this file, you will see that everything has been commented out, except the default constructor for the Dlist class. Begin by writing just the Dnode class, and then a list class with just a default constructor. Compile and run. Then uncomment the next block of code and write the implementation for the functions that are called in that block. (Note that STL classes do not have “show all” functions, but I find it very useful to have one as you develop the class). Continue this process, compiling and running for each block as you uncomment it. If you get a crash, go back and fix it before going on. (Compile with g++ -g main1.cc)  

The list holds dynamic memory which means that the default forms of the “Big 3” do not work correctly so you will need to define the Big 3 for this class. The deconstructor is much the same as one for a singly linked list, but the other two are different because in copying the list you must remember to maintain all the pointers (head and tail, next and previous). Work carefully and use drawings. A minor misstep can lead to major seg faults down the road. There is code that does some testing of these in the main1 file as well.  

***  

The last thing that you will develop in this process is a bidirectional, external iterator. You will need to make an additional class for this, a class which will closely parallel the node_iterator class I presented in lecture (you should include both pre and post fix ++ and -- operators).  

You will then alter the list class to include:  

* begin (return an iterator pointing to the beginning of the list)  
* end (return an iterator pointing to nullptr - the "past the end" element)  
* r_begin (return an iterator pointing to the end of the list)  
* r_end (return an iterator pointing to nullptr - the "past the end" element)  
* insert_before  
* insert_after  
* remove  

insert_before and insert_after should take as arguments an iterator and an item to be added. The remove function takes just an iterator as its argument (assume it is pointing to the item you want to remove).  

**Remember to consider all the special cases we have discussed: empty list, single node list, first node, last node, middle node.**

***  

**The Application – Color Squares**  

Colors on a computer are frequently represented as a hexadecimal number, such as cc0099. Hexadecimal numbers are base 16 numbers and consist of the digits 0 – f. This number is actually three numbers, with the first two digits representing the intensity of red, the second two the amount of green and the third pair blue. There are 256 possible values for each color. (A total of 16,777,216 distinct colors can be represented in this way with 000000 being black and ffffff being white.)  

I have provided a small class to store color swatches much like something used in a paint store. Each “swatch” consists of a hexadecimal number representing the color, and two decimal numbers representing the dimensions of the swatch in millimeters. I have also provided a data file listing a whole collection of these swatches called swatches.txt. There are also a couple of executables that will convert these numbers into viewable html files, as well as the application for the program, main2.cc. (This part will compile with g++ -g swatch.cc main2.cc)  

This application reads swatch data from the data file and places the predominantly green colors at the start of the list, the predominantly red colors at the back of the list, and the predominantly blue colors at the spot immediately following the centermost spot in the list. It then:  

* Makes a copy of the list using either your copy constructor or your overloaded assignment operator 
* Removes the front, back and centermost swatch from the copy. 
* Outputs the original list frontwards 
* Outputs the copy frontwards. 
* Outputs the original list backwards. 
* Destroys the original list by alternating between removal of the first item and the last item, outputting each item as it is removed. 
* Outputs the copy backwards. 

Notice that there is no user interaction in this application. It simply runs the test and stops, outputting the results to the screen, one “swatch” per line with two or more blank lines between each of the outputs. Although it is not required you can see the colors by doing the following: 

* Redirect the output of your program to a file: ./a.out > result  
* Compile the makinghtml program provided with this assignment (g++ makinghtml.cc swatches.cc -o makinghtml)  
* Run: ./makinghtml result  
* This will create a .html file which you can open by double-clicking on it in your file explorer. 

***  

**Your final GitHub repository should include** your dnode.h, dlist.h, dlist.template, node_iterator.h, and node_iterator.template files. All code should be adequately documented and nicely formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.
