/*************************************************************************
    This file is borrowed heavily from Main/Savitch Data Structures and
    Other Objects Using C++, Chapter 5. It features a node class that 
    can be used in the construction of linked lists.
    
	Patricia Lindner	February 2024
*************************************************************************/

#ifndef NODE_H
#define NODE_H
#include "assignment.h"

class node{
    public:
        // If you want this node to store a different type of data, change Assignment to that type
        // in the next line, and that is all you will have to do.
		typedef Assignment value_type;

		/**
		 * @brief Construct a new node object
		 * 
		 * @param d - the data you want to store (default to whatever the default constructor makes)
		 * @param n - the address to the next node in the list
		 */
        node(value_type d = value_type(), node *n = NULL) {data_field = d;  next_field = n;}

        // Mutator functions
        /**
         * @brief Set the data_field member
         * 
         * @param d - the data to assign to the data_field member
         */
		void set_data(value_type d) {data_field = d;}

        /**
         * @brief Set the next_field member
         * 
         * @param n - the address to assign to the next_field member
         */
		void set_next(node *n) {next_field = n;}

        // Accessor functions
        /**
         * @brief return the data stored by this node
         * 
         * @return value_type - the data
         */
        value_type data() const {return data_field;}

        /**
         * @brief return the address to the next node
         * 
         * @return node* - the address to the next node
         */
        node* next() {return next_field;}

        /**
         * @brief return the address to the next node as a const pointer
         * 
         * @return const node* - the address to the next node
         */
		const node* next() const {return next_field;}

    private:
		value_type data_field;
		node* next_field;
};

#endif