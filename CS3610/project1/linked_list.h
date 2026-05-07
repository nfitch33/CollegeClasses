
#include <iostream>
using namespace std;

template <typename T>

class LinkedList {

public:
  LinkedList() : head(NULL) {}

  // You need to implement the following functions. 
  
  ~LinkedList();
  void push_front(const T data);
  void pop_front();
  void reverse();
  void print() const;

private:
  
  struct ListNode {
    ListNode(const T data) : data(data), next(NULL) {}
    
    T data;
    ListNode* next;
  };

  ListNode* head;
};

template <typename T>
LinkedList<T>::~LinkedList(){

}

template <typename T>
void LinkedList<T>::push_front(const T data){

  //if no data
  if(head == nullptr){
    head = new ListNode(data);
    head->next = nullptr;
  }

  else{
    ListNode *ptr = head;
    head = new ListNode(data);
    head->next = ptr; 
  }
  return;
}

template <typename T>
void LinkedList<T>::pop_front(){
  if(head == nullptr){
    cout << "Empty" << endl;
    return;
  }
  else{
    ListNode *ptr = head;
    head = head->next;
    delete ptr;
    return;
  }
}

template <typename T>
void LinkedList<T>::reverse(){
  //If no data / one data
  if(head == nullptr){
    cout << "Empty" << endl;
    return;
  }
  else if(head->next == nullptr){
    return;
  }
  ListNode *cursor = head;
  ListNode *ptr = nullptr;
  ListNode *prev = nullptr;

  while(cursor != nullptr){
    ptr = cursor -> next;
    cursor -> next = prev;
    prev = cursor;
    cursor = ptr;
  }
  head = prev;
}

template <typename T>
void LinkedList<T>::print() const{
  if(head == nullptr){
    cout << "Empty" << endl;
    return;
  }
  else{
    ListNode *ptr = head;
    while(ptr != nullptr){
      cout << char(ptr->data) << ' '; 
      ptr = ptr->next;
    }
  }
  cout << endl;

}
