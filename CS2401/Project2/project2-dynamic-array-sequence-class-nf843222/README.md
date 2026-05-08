CS 2401 – Spring 2024
# Project 2 – Sequence Classes and Dynamic Arrays
Due: 11:59 PM Wednesday, February 28th
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.
***  
The idea of a sequence class is that the application programmer can choose where an item is stored in the list, and that sequence, or order, of the items remains the same, even when things are deleted.  

In this project we are going to pass that capability on to the user allowing them to order the profiles they follow on Instagram in any way they choose. We are just maintaining a list here, not working with your actual Instagram account, so you don’t have to import the people you really follow (if you have an Instagram account). Of course, some people follow thousands of profiles, while others follow only a few, so we are going to implement this using a dynamic array.  

***  

Begin by adding Doxygen comments for each function in the header files once you figure out what they should do.  

profile.h is a header file for a class called Profile. This class has two private variables, one for the profile’s name and the other for their birthday. The birthday is of type Date which you also used for the last project. You are to write the implementation of this class (profile.cc), including overloaded insertion, extraction, ==, and != operators. Two profiles are “equal” only if they have the same name and the same birthday.  

You can test this class by writing a main of your own that declares two profiles, lets you put the information into both, outputs them to the screen and compares them for equality.  

***  

Now, in the main that I have given you, you will find that the application allows the user to:
1. Add a new profile to the beginning of the list
2. View all the profiles in the list
3. Walk through the list, viewing one profile at a time
4. Remove a profile from the list (unfollowing someone)
5. Insert a new profile at some spot in the middle of the list, which includes at the back end
6. Sort all the profiles by their birthdays
7. Find a profile using their name  

There is also a file backup mechanism that uses the person’s username for the name of the file.
 
I have given you the header file for the container class that makes all this possible, instafollows.h. You are to write the implementation of this (instafollows.cc). The private variables for this class consist of a pointer of type Profile as well as variables for capacity, used, and current_index. The constructor must allocate a dynamic array of type Profile with the capacity to hold five profiles. When a profile is added to the list, you should check if used == capacity, and if it does, resize the array to increase the size by five.  

You must also implement an internal iterator like the one I described in class. To do this you will need to implement the functions:
* start
* advance
* is_item
* current
* remove_current
* insert (increment the iterator so it remains pointing to the profile it was pointing at before inserting)
* attach  

After that, implement show_all, bday_sort, find_profile (to identify a profile by its name and return the whole Profile object), and is_profile (to determine if a Profile is in the array or not).  

Because this is a dynamic array you will need to write a resize function and the Big 3 (deconstructor, copy constructor, and assignment operator). Also, because we’re providing file backup, you need to have functions to load and save the array.  

Your submission should include a data file of at least six profiles, although they can be fictitious. The format of the data file should be:

name1
bday1
name2
bday2
etc...  

I recommend that you test your program with a list of at least six profiles to guarantee that resize is working correctly. If there is a function that you are unable to get working correctly, just comment out the inside of the function implementation so that your code will still compile.

**Your final GitHub repository should include:** Your commented profile.h and instafollows.h as well as completed profile.cc and instafollows.cc. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.