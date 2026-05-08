CS 2401 Spring 2024  
# Lab 13: Binary Trees  
Due: Friday 4/26 at 11:59 PM  
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.
***  

Given the struct Bnode in btreelab.cc, create a little program that can build a binary search tree from the names listed in the file, names.txt.  

You can use the in-order traversal that I have given you to see that the names are in there.  

***  

Now, write a function that searches for and counts the number of times that a particular name occurs (we looked at a search and a size function in class). Let the user input the name they want to search for from the keyboard. The output for the function should just say: “Your search name appears 5 times.” With the number being correct, of course. 

***  

Finally, write a function that counts the number of names (not unique names) that are in the tree and greater than (i.e. come after in the alphabet) the search name. This function should be written recursively. Think of it like this: 

* If the search name is less than or equal to the name in the current node
  * Add the size of the right subtree.  
  * Move to the left and repeat.  
* If the name in the current node is less than the search name
  * Move to the right without counting anything.  
* The base case is when you hit NULL, a condition that will return a 0.  

***  

**Your final GitHub repo should include** your completed source code. 
