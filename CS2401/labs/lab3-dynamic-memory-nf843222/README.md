CS 2401 Spring 2024
# Lab 3: Dynamic Memory
Due: Friday 2/9 at 11:59 PM  
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.
***  

Type your answers to the questions listed into the answers.txt document provided.

**Part One: (Static and automatic variables)**
1.	Open a new file, type #include <iostream> and put in your using statement.
2.	Type in this function:
    <pre>
    void pretty( ){  
        int x = 0;  
        x++;  
        for(int i = 0; i < x; ++i){  
            cout << ’*’;  
        }  
        cout << endl;  
    }  
    </pre>
3.	Write a main function with a loop that calls the function six times.  
4.	**Q1:** What output do you get from running this program?
5.	Now change the first line in the function pretty so it looks like this:  
    <pre>
    static int x = 0;
    </pre>
6.	Recompile and run the program.  
7.	**Q2:** What is the output from this function?  
8.	**Q3:** What was the effect of using static?   
9.  **Q4:** If you remove static what is the effect?   

***  

**Part Two: (Dynamic Variables)**  
1. Start a new program – again starting out with the #include <iostream> and 
using namespace std;  
2.	Create a main function.  
3. Declare a pointer to an int.  
4.	Make the pointer point to a new integer.  
5.	Print out the address of the new integer. (**Q5:** Write how you did this as well as the address that showed up.)  
6.	Print out the address of the pointer. (**Q6:** Write how you did this as well as the address that showed up)  
7.	Use the * operator to set the value of your integer to 2401.  
8.	Write a loop with an integer counter that counts to 10. In the body of the loop do this:  
    <pre>
    ++(*ptr);
    cout << *ptr << "is stored at " << ptr << endl;
    </pre>
9.	**Q7:** Write down the first and last lines that appeared.  
10.	Now change the body of your loop to this:
    <pre>
    ++(ptr); // notice the * is missing
    cout << *ptr <<  "is stored at " << ptr << endl; 
    </pre>
    The difference here is that you were moving the pointer instead of changing the value being pointed at.  
11.	**Q8:** What do the last two lines of your output look like?  

***  

**Part Three (A dynamic array)**
1.	Now let’s make a dynamic array with the pointer that you have been using.
2.	Begin by declaring a couple of size_t variables for capacity and used.
3.	Initialize capacity to five and used to zero.
4.	Declare an extra int* tmpptr, which we will use in resizing.
5.	Type this code:
    <pre>
    ptr = new int[capacity];
    for(size_t i = 0; i < 25; ++i){
        ptr[used] = rand(); // you will need #include<cstdlib>
        // at the top for this to work
        cout << ptr[used] << endl;
        used++;
        if(used == capacity){
            cout << ”Sorry no room left.\n”;
            break;
        }
    }
    </pre>
6.	**Q9:** How many numbers you see in the output?
7.	Now replace the cout and the break for a full array with a resizing which will do this:  
    a.	Set the tmpptr to a new integer array of capacity +5 size  
    b.	Copy the data from the original array to the new one using a loop or the copy function  
    c.	Adjust the capacity variable so it accurately reflects the size of the new array  
    d.	Delete the original array, remembering to use the []'s  
    e.	Assign ptr to tmpptr, so these pointers will both point at the newer array  
    f.	Do a cout << "Resized\n"; to report that this was done.  
8.	Now run your program – **Q10:** what do you see?
9.	Comment out "cout << ptr[used];" from step 27, and then at the end of this loop, add:  
    a.	tmpptr[2] = 0;  
    b.	A loop that outputs all the numbers in the ptr array.  
10.	**Q11:** What do you see? 

**Your final GitHub repository should include:** Your two main programs and completed answers.txt file. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.
