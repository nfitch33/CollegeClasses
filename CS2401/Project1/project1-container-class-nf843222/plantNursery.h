#include <iostream>
#include "plant.h"
#include <fstream>

int const SIZE = 200; // Array size allowed

class PlantNursery{
    public:
        PlantNursery();
        void load_from_file(std::istream& ifs); // Function for getting data from file
        void show_all(std::ostream& output);   // Outputs all plant information
        void add_plant(std::istream& input);    // Asks user for another plant to the data set
        void remove(std::string name, std::string color);   // gets name and color from user to delete specified plant
        void name_sort();   // Sorts data set alphabetically
        void change_stock_amt(std::string name, std::string color, int amount); // Grabs color and name from user and how much they want to change those stocks by
        void date_sort();   // Sorts data from earliest to latest
        void stock_sort();  // Sorts data from most stock to least stock
        void show_plants(std::string color) const;  // Prints all information of plants with same color in terminal 
        void show_before(Date date); // Grabs a date from the user, outputs all data that has a date before selected date
        void show_colors(std::string name) const; // Gets name from a user and outputs all information with specified name
        double average();   // Grabs all stock values in data and divides by the used amount to get average amount of stocks
        void save(std::ostream& ofs); // Saves all added and current information to the file
    private:
        size_t used;
        Plant array[SIZE];

};