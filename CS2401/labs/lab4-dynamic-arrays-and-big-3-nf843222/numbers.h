/*************************************************************************
	A little class that holds a dynamic array of numbers.
	I have provided a start here, you need to write the function
		implementations. DO NOT remove the byte_count lines that are
		already in a few of the functions.


    John Dolan			Spring 2013		CS2401 Lab Assignment 4
	Patricia Lindner	Fall 2021
*************************************************************************/

#include <iostream>
using namespace std;

size_t byte_count = 0;
class Numbers{
    public:
		Numbers();
		void add(unsigned long item);
		void resize();
		void remove_last();
		void display(std::ostream& outs);
		unsigned long* reveal_address()const;
		void operator =(const Numbers &second);
		~Numbers();

    private: 
		unsigned long * data;
		std::size_t used;
		std::size_t capacity;
};

Numbers::Numbers(){
	capacity = 5;
	used = 0;
	data = new unsigned long[capacity];
	byte_count += 5 * sizeof(unsigned long);
}

Numbers::~Numbers(){
	delete []data;
	byte_count = byte_count - (capacity * sizeof(unsigned long)); 
}

void Numbers::operator =(const Numbers &second){
	if (this == &second){
		return;
	}
	delete []data;
	capacity = second.capacity;
	used = second.used;
	data = new unsigned long[capacity];
	for (size_t x = 0; x < used; x++){
		data[x] = second.data[x];
	}
}
void Numbers::add(unsigned long item){
	if (used == capacity){
		resize();
	}
	data[used] = item;
	used++;
}

void Numbers::resize(){
		unsigned long* extra;
		extra = new unsigned long[capacity + 5];
		for (size_t x = 0; x < used; x++){
			extra[x] = data[x];
		}
		delete []data;
		capacity += 5;
		data[capacity];
		data = extra;
	byte_count += 5 * sizeof(unsigned long);
}

void Numbers::remove_last(){
	used--;
}

void Numbers::display(std::ostream& outs){
	for (size_t x = 0; x < used; x++){
		outs << data[x] << ' ';
	}
}

// You can leave this function alone
unsigned long *Numbers::reveal_address()const{
	return data;
}