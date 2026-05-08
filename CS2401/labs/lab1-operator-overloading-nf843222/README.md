CS 2401 – Spring 2024  
# Lab 1 - Operator Overloading  
Due: 11:59 PM Friday, January 26th  
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus. //
***  
Download the MyTime.h and MyTime.cc files provided with this assignment. In this example, you will see implementations for four arithmetic operators, three Boolean operators and the input and output operators. They have all been implemented as friends of the MyTime class. //

Requirements: 

* Implement all 9 operators without using friends. 
    * For the Boolean and arithmetic operators, you should do this by making the operators members of the MyTime class. Make sure you use const to protect the object which is being used as the left-hand operand as well as the object that is passed in (-½ point each time you miss a const). 
    * For the I/O operators you should do this by writing input and output functions in the class that do the job of the operator, and then have the operator call that member function. The prototypes for the input and output functions are included in the MyTime class. 

* Combine the two constructors into a single constructor by using default arguments. 

* Write an application that allows the user to enter two times and a scalar, and then see all the math and at least one of the Boolean operators performed on those objects. 
    * Clearly promt the user for the desired input.
    * Clearly output the results of the operators (it should be obvious which operation each output goes with).

**Your final GitHub repository should include:** Your updated MyTime.h and MyTime.cc and your main.cc. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment. //
