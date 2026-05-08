CS 2401 – Spring 2024  
# Lab 5 - Linked Lists  
Due: 11:59 PM Friday, February 23rd
***  
This assignment is to be completed on your own. Refer to the plagiarism policy in the syllabus.  
***  
Begin by making a new directory for this lab, and then open a file called list.h. Into this file type the following code (please do type it on your own, it will help you learn it better and you can accidentally insert hidden characters if you copy and paste.  

```
#include <iostream>  
#include <string>  

struct Node{  
    std::string data;  
    Node *next;  
};

class Lilist{  
public:  
    Lilist(){head = NULL;}  
    void add(std::string item);  
    void show();  
        
private:  
    Node *head;  
};  

void Lilist::add(std::string item){  
    Node * tmp;  

    if(head == NULL){  
        head = new Node;  
        head -> data = item;  
        head -> next = NULL;  
    }  
    else{  
        for(tmp = head; tmp -> next != NULL; tmp = tmp -> next)  
            ;  // this loop simply advances the pointer to the last node in the list  
            
        tmp -> next = new Node;  
        tmp = tmp -> next;  
        tmp -> data = item;  
        tmp -> next = NULL;  
    }  
}    

void Lilist::show(){  
    for(Node *tmp = head; tmp != NULL; tmp = tmp -> next)  
        std::cout << tmp -> data << " ";
    std::cout << std::endl;  
}  
```

***  
Now write a main that looks like this in a file called main.cc.

```
#include <iostream>  
#include <string>  
#include "list.h"  

using namespace std;    

int main(){  
    Lilist L1, L2;  
    string target;  

    L1.add("Elizabeth");  
    L1.add("Zachary");  
    L1.add("Clay");  
    L1.add("Lainie");  
    L1.add("Izaak");  
    L1.add("Andrew");  

    cout << "Now showing list One:\n";  
    L1.show();  
    // END OF PART ONE  
    /*  
    cout << "Enter a name to search:";  
    cin >> target;  
    
    if(L1.search(target) != NULL)  
        cout << "That name is stored at address: " << L1.search(target) << endl;  
    else{  
        cout << ”That name is not in the list.\n”;  
    }  

    L1.move_front_to_back();  
    L1.move_front_to_back();  
    L1.show();  
    */  

    return 0;  
}  
```

***  

After you have written and run the program down to the place where it says End of Part One, go back into your class and write a search function that takes a string as its argument. It will return the address of the node holding the string, or NULL if the pointer runs off the end of the list.  

Part of this code will include:  
```
    if(cursor -> data == target) return cursor;  
```
***  

Then, write a move_front_to_back function. The key here is to:  
* Use an extra pointer to hold the first node in the list.  
* Move the head to the second node of the list.  
* With another pointer, find the last node in the list.  
* Hook the node that used to be at the front to the back. (Look at the code you’ve written for adding nodes). 

***  

Uncomment the rest of the main.   

The output should now show the list printed both in its original order and in the order with the first two names moved to the back of the list.  

Provide evidence that the program is working for you (screenshots will do).  

***  

**Your final GitHub repository should include:** Your source code and evidence that the program was working for you. All code should be adequately documented and neatly formatted. Submit a link to your repository on Blackboard when you are finished with the assignment.
