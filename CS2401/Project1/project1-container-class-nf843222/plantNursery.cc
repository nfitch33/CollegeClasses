#include "plantNursery.h"
#include "plant.h"
#include <iostream>
#include <fstream>
using namespace std;

/* Constructor */
PlantNursery::PlantNursery(){
    used = 0;
};

/* calls on the add plant function from */
void PlantNursery::load_from_file(istream& ifs){
    ifs >> ws;
	for (size_t i = 0; i < SIZE && !(ifs.eof()); i++){
		add_plant(ifs);
		ifs >> ws;
	}
};

/* outputs all of the plant information */
void PlantNursery::show_all(ostream& output){
	for (size_t i = 0; i < used; i++){
		output << array[i];
	}
};

/* Function that allows to add more plants to the data*/
void PlantNursery::add_plant(istream& ins){
	
	Plant temp;
	temp.input(ins);
	array[used] = temp;
	used++;
};

/* Looks for the name and color in the data then removes all data located there.*/
void PlantNursery::remove(string name, string color){
	for (size_t i = 0; i < SIZE; i++){
		if (array[i].get_name() == name && array[i].get_color() == color){
			array[i] = array[used - 1];
			used--;
		}
	}
};

/* Sorts all of the data by alphabetical order */
void PlantNursery::name_sort(){
	// selection sort
	size_t i, j , min;
	for (i = 0; i < used - 1; i++){
		min = i;
		for (j = i + 1; j < used; j++){
			if (array[j].get_name() < array[min].get_name()){
				min = j;
			}
		}
		swap(array[min], array[i]);

	}

};

/* Finds the name and color of plant you are looking to change, 
then changes the stock by how much your looking for */
void PlantNursery::change_stock_amt(string name, string color, int amount){
		for (size_t i = 0; i < used; ++i){
			if (array[i].get_name() == name && array[i].get_color() == color){
				array[i].change_stock(amount);
				break;
			}
		}
}

/* Gets the date of each array and sorts them from earliest to latest */
void PlantNursery::date_sort(){
	// bubble sort
	for(size_t i = 0; i < used - 1; ++i){
		for (size_t j = 0; j < used - i - 1; ++j){
			if (array[j].get_cameIn() > array[j+1].get_cameIn()){
				Plant plant = array[j];
				array[j] = array[j+1];
				array[j+1] = plant;
			}
		}
	}
}

/* Sorts the data by whichever has the highest stock first */
void PlantNursery::stock_sort(){
	// insertion sort
	size_t i, j;
	Plant key;
	for (i = 1; i < used; i++){
		key = array[i];
		j = i - 1;
		while (j >= 0 && array[j].get_stock() > key.get_stock()){
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = key;
	}
}

/* Outputs all information to the terminal for the character to read */
void PlantNursery::show_plants(string color) const{
	for (size_t i = 0; i < used; i++){
		if (array[i].get_color() == color){
		cout << "Name: " << array[i].get_name() << endl; 
		cout << "Color: " << array[i].get_color() << endl;
		cout << "Date: " << array[i].get_cameIn() << endl;
		cout << "Stock: " << array[i].get_stock() << endl;
		}
	}
}

/* Grabs a date from the user and outputs all data 
that has a date before it */
void PlantNursery::show_before(Date date){
	for (size_t i = 0; i < used; i++){
		if (array[i].get_cameIn() <= date){
			cout << "Name: " << array[i].get_name() << endl; 
		cout << "Color: " << array[i].get_color() << endl;
		cout << "Date: " << array[i].get_cameIn() << endl;
		cout << "Stock: " << array[i].get_stock() << endl;
		}
	}
}

/* Shows all plants of a certain name */
void PlantNursery::show_colors(string name) const{
	for (size_t i = 0; i < used; i++){
		if (array[i].get_name() == name){
			cout << "Name: " << array[i].get_name() << endl; 
		cout << "Color: " << array[i].get_color() << endl;
		cout << "Date: " << array[i].get_cameIn() << endl;
		cout << "Stock: " << array[i].get_stock() << endl;
		}
	}
}

/* Takes all stock, adds them up, and divides them by how much
data is used out of the capacity.*/
double PlantNursery::average(){
	double averageSet = 0.00;
	for(size_t i = 0; i < used; i++){
		averageSet += array[i].get_stock();
	}
	averageSet = averageSet / (used - 1);
	return averageSet;
}

/* Saves the data to the outstream file */
void PlantNursery::save(ostream& ofs){
    for (size_t i = 0; i < used; i++){
		ofs << array[i];
	}
}
