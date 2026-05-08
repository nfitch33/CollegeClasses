#include <cstdlib>
#include <iostream>

struct node{
     int data;
     node* next;
};


/**
 * @brief remove nodes with repeated values in a linked list
 * 
 * @param head - a pointer to the beginning of a linked list
 */
void remove_repeats(node*& head) {
     if(head == nullptr){ // return if null
          return;
     }

     node* cursor = head;
     node* previous = head;   // 3 new nodes to help move through linked list
     node* extra = head;

     while(extra->next != nullptr){     // Will exit when extra reaches the end.
          previous = extra;
          
          while(previous->next != nullptr){  // Will keep going through data until previous is at end. Then we will "increment" extra;
               cursor = previous->next;

               if(cursor->data == extra->data){   // If data has been shown before
                    if(cursor->next != nullptr){  // Check to make sure its not the end
                         previous->next = cursor->next;
                         delete cursor;
                         cursor = previous->next;
                    }

                    else{     // If its at the end, we create a new nullptr
                         previous->next = nullptr;
                         delete cursor;
                         cursor = previous->next;
                    }
               }

               else{     // If data is unique, we just "increment" both cursor and previous
                    cursor = cursor->next;
                    previous = previous->next;
               }
          }
          extra = extra->next;

     }
}
     

/**
 * @brief split the original list at a value present in the list
 * 
 * @param original - a pointer to the beginning of a linked list
 * @param lesser - a pointer to the beginning of the lesser value list
 * @param greater - a pointer to the beginning of the greater value list
 * @param split_value - a number to split the list on
 */
void split_list(const node* original, node*& lesser, node*& greater, int split_value) {
     //add a CONST cursor for original
     const node *cursor = original;
     //add a cursor for lesser and greater
     node* less;
     node* big;

     if(original == nullptr){ // return if null;
          return;
     }

     while(cursor != nullptr){     // Keeps going until cursor reaches end of list
          if(cursor->data < split_value){    // If the value is less than split_value
               if(lesser == nullptr){
                    // This is first case, Are there special rules to adding to the beginning of a list? YES
                    lesser = new node();
                    less = lesser;
                    less->data = cursor->data;
                    less->next = nullptr;
               }
               else{
                    // Everything else, note I will need to make a new nullptr in each if else statement
                    less->next = new node();
                    less = less->next;
                    less->data = cursor->data;
                    less->next = nullptr;
               }
               cursor = cursor->next; // Needed after each to "increment" through the while loop
          }
          else if(cursor->data > split_value){    // If the value is greater than split value
               if(greater == nullptr){
                    greater = new node();
                    big = greater;
                    big->data = cursor->data;
                    big->next = nullptr;
               }
               else{
                    big->next = new node();
                    big = big->next;
                    big->data = cursor->data;
                    big->next = nullptr;
               }
               cursor = cursor->next; // "Increment"
          }
          else{     // If the value is the split_value
               cursor = cursor->next; // "Increment" if value is split_value
          }
     }

}

/**
 * @brief builds a linked list of 2000 random integers, all in the range 1 - 500
 * 
 * @param head - a pointer to the beginning of a linked list
 */
void build_list(node*& head){
     node* cursor;

     head = new node;
     head -> data = std::rand() % 500 + 1;

     cursor = head;
     for(int i = 0; i < 2000; ++i){
		cursor -> next = new node;
        cursor = cursor -> next;
        cursor -> data = std::rand() % 500 + 1;
     }
     cursor -> next = NULL;
}

/**
 * @brief outputs the contents of a linked list to the screen
 * 
 * @param head - a pointer to the beginning of a linked list
 */
void show_list(const node* head){
     // This pointer cannot be used to change the data in the nodes that it points to
     const node* cursor = head;

     while(cursor !=  NULL){
		std::cout << cursor -> data << "  ";
		cursor = cursor -> next;
	}
	std::cout << std::endl;
}

/**
 * @brief returns the number of nodes in a linked list
 * 
 * @param head - a pointer to the beginning of a linked list
 * @return int - the number of nodes in the list
 */
int size(const node* head){
     // This pointer cannot be used to change the dat ain the nodes that it points to
	const node* cursor = head;
	int count = 0;

	while(cursor != NULL){
  	    count++;
	    cursor = cursor -> next;
	}

	return count;
}
