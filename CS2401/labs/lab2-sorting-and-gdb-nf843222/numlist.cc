//************************************************************************
//	Implementation file for the Numlist class, which 
//	allows programmers to store a list of numbers that they
//	choose to have sorted if they like.
//
//	January 2013		John Dolan
//  January 2023		Patricia Lindner
//	Ohio University		EECS
//***********************************************************************/
#include "numlist.h"
#include <fstream>
using namespace std;

// Constructor
NumList::NumList(){
	used = 0;
}

void NumList::insert(int num){
	if(used < CAPACITY){
		data[used] = num;
		used++;
	}
	else{
		cout << "Error. List capacity has been reached.\n";
	}
}

void NumList::load_from_file(istream& ins){
// The implementation of this function is left to the student
	for (size_t i = 0; i < CAPACITY ; i++){
		ins >> data[used] >> ws;

		if (ins.fail()){
			break;
		}
		used++;
	}
}


void NumList::save_to_file(ostream& outs){
// The implementation of this function is left to the student
	for (size_t i = 0; i < used; i++){
		outs << data[i] << endl;
	}
}

void NumList::see_all()const{
	if(used == 0){
	    cout << "Empty list.\n";
	}
	else{
	    for(size_t i = 0; i < used; ++i)
		cout << data[i] << endl;
	}
}

int NumList::get_item(size_t index)const{
	if(index < used){
		return data[index];
	}
	else{
		return -1;
	}
}
	
void NumList::i_sort(){
	for (size_t i = 1; i < used; i++)
	{
		int next = data[i];
		// Move all larger elements up
		size_t j = i;
		while (j < used && data[j - 1] > next) // code should have data [j - 1] not [j = 1] ... Edited into program
		{
			data[j] = data[j - 1];
			j--;
		}
		// Insert the element
		data[j] = next;
	}
}
