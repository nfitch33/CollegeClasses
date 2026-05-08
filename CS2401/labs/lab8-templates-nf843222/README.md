CS 2401 – Spring 2024  
# Lab8_Templates  
Due: 11:59 PM Friday, March 22nd  
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.
***  

## IMPORTANT!
Before you begin working on this week's lab assignment, you need to start your preparation for the next lab which you will work on with a group for two weeks (labs 9 and 10). You must create a group of 3-4 students from your lab section to complete the group assignment. Please create your group and accept the assignment.

You do not need to work on this assignment this week, just create your group and accept it.

***

The purpose of this lab is to get a feel for how template classes work. Provided are two files, ```tarray.h``` and a ```lab8main.cc```. Notice that at the bottom of tarray.h there is a line that says ```#include "tarray.template"```.
You are two write the ```tarray.template``` file which will implement the following functions, which are present in the ```tarray.h``` file, for the class:

```Tarray();```

```void add(T item);```

```void start();```

```bool is_item() const;```

```void advance();```

```T current()const;```

and in the private section:

```void resize();```

Once you have implemented all the functions, you may compile the program with the command ```make```. If you would like to know more about how make works, check the file ```Makefile```. If you are ready to test your code, please use the command ```make run_tests```

***  

**Your final GitHub repository should include:** Your tarray.template file. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.
