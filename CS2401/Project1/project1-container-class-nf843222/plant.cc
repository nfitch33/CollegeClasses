/*************************************************************************
    This is the implementation file for the Plant class. For more 
		information about the class see plant.h.
    Students are expected to implement the input and output functions
		below.

	Patricia Lindner	Ohio University EECS	January 2023
*************************************************************************/
#include "plant.h"
using namespace std;

Plant::Plant(string n, string c, Date i, int s){
	name = n;
	color = c;
	cameIn = i;
	stock = s;
}

// Input and output functions
void Plant::input(std::istream& ins){
	/* You are to write the implementation of this function to read 
	from the keyboard or a file. Remember to use getline to read the 
	name and color.  */

	getline(ins, name);
	getline(ins, color);
	ins >> cameIn >> ws >> stock;
	ins.ignore();
}

void Plant::output(std::ostream& outs)const{
	/* You are to write the implementation of this function to write 
	to the monitor or to a file. Remember not to put labels into the 
	file.*/

	outs << name << endl;
	outs << color << endl;
	outs << cameIn << endl;
	outs << stock << endl;
}

ostream& operator << (ostream& outs, const Plant& p){
	p.output(outs);
	return outs;
}

istream& operator >> (istream& ins, Plant& p){
	p.input(ins);
	return ins;
}