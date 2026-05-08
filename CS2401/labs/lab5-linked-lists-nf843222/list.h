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
    void move_front_to_back();
    Node* search(std::string target) const;
        
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
Node* Lilist::search(std::string target) const{
    for (Node *tmp = head; tmp != NULL; tmp = tmp -> next){
        if (tmp -> data == target){
            return tmp;
        }
    }
    return NULL;
}
void Lilist::move_front_to_back(){ // Moves the first name to the back
    if(head -> next == NULL){
        return;
    }
    else{
    Node *section = head;
    head = head -> next;
    Node *tmp = head; 
    while(tmp -> next != NULL){
        tmp = tmp -> next;
    }
    tmp -> next = section;
    section -> next = NULL;
    }
}
