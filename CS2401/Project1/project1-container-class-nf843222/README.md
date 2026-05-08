CS 2401 – Spring 2024
# Project 1 – Container Class
Due: 11:59 PM Friday, February 9th
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.
***  

You have been asked by a plant nursery to create an inventory system for their business. To do so, you will need to write a container class that holds records describing each plant and how many are in stock.
The files I have provided are:  
* date.h - Header file for a class that stores dates and reads / writes them in the format mm/dd/yyyy
* date.cc - Implementation file for the date class
* plant.h - Header file for a class that stores information about a plant
* plant.cc - Partially completed implementation file for the Plant class
* commented_main.cc - An application you can use to incrementally implement the PlantNursery class. All the PlantNursery functions are commented out so you can work on them one at a time and the program will still compile.
* testing_main.cc - An application you can use to make sure you have written all PlantNurery functions that are required (in case you missed one in the commented_main.cc).
* inventory.txt - A sample data file for you to use

The plant.h and plant.cc files define a class called Plant, which holds the information for a single plant, including the name, the color, the date these plants came in stock, and how many are in stock. This class is dependent on the Date class which I have provided.  
**Do not change anything about the Date class or the plant.h file, but you will need to complete plant.cc.**  

The Date class already has defined the >> and << operators for Date objects as well as a full set of comparison operators. Users can type in dates like "1/1/2024" (without the double quotes) and the insertion operator will output the date for you in that same format. You should use these. Do not try to re-invent or circumvent these operators, it will cost you unnecessary time and frustration.  

In the plant.cc file, you will need to write the implementations for the input and output functions.  

Next, create plantNursery.h and plantNursery.cc. Your PlantNursery objects must consist of an array (**NOT** a vector) capable of holding 200 plants and a number to keep track of how full that array is. By looking at the main, you can see the names of the functions that you are to write for the PlantNursery class. (The main that I gave you is also a file you should not change except to uncomment the PlantNursery class calls.)   

These will give the user the ability to:
1.	Have their inventory list reloaded from the backup file – so they do not have to manually re-enter their plants every time they start the program.
2.	See a list of all the plants in stock
3.	Add a new plant that just came in stock.
4.	Remove a plant.
5.	Change the amount of a plant that is currently in stock.
6.	Sort the plants alphabetically by name.
7.	Sort the plants by the date they came in stock.
8.	Sort the plants by the quantity in stock.
9.	Find and view all the plants of a certain color (with the total).
10.	Find and view all the plants that came in stock before a certain date.
11.	Find and view all the colors of a certain plant type (i.e. plants with the same name).
12.	Find the average number of plants that you keep in stock (i.e. the average of the “stock” attributes).
13.	Have the PlantNursery data backed up to the same file that it was read from at the beginning of the program, upon exiting the program (the main calls the save function – you write the save function)  

***  

Notes:
1.	Items 2 – 12 above are menu options that are done in a loop in the main. The back-up file is done without the user’s knowledge or interaction.
2.	Options 6 – 8 must each use a different sorting algorithm.
3.	Remember to declare the size of the array as a static constant in the public section.
4.	Each file that you create should have a header block with your name, an approximate date, and a description of what is done in the file.
5.	Any header files should include Doxygen style comments for each function and you should add descriptive comments throughout your code.
6.	Your container class should exhibit the correct use of const and static const.
7.	You can read in and output dates like this:

    Date d;  
    cin >> d;  
    cout << d;  

    **Don’t waste time rewriting that code!**  
8.	When you read in a string, it is best to use getline so you make sure to get the entire string (including spaces). Also remember to ignore any leftover newline characters when using getline after the >> operator.  
9.	You must pass streams by reference.  
10.	For each plant in stock, the format of the data file is:  
    plant_name  
    plant_color  
    came_in_date  
    stock_amount  

***  

**Your final GitHub repository should include:** Your updated plant.cc, plantNursery.h, and plantNursery.cc. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.
