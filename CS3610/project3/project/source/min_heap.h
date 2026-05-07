#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
struct HeapNode {
  HeapNode(const T data, const int key) : data(data), key(key) {}
  bool operator<(const HeapNode<T>& rhs) {return this->key < rhs.key;}
  bool operator<=(const HeapNode<T>& rhs) {return this->key <= rhs.key;}

  T data;
  int key;
};

template <typename T>
class MinHeap {
public:
  MinHeap() {}
  ~MinHeap() {}

  void insert(const T data, const int key);
  T extract_min();
  T peek() const {T data; return data;}; 

  int size() const { return 0;};        

private:
  vector<HeapNode<T> > heap;
};


template <typename T>
void MinHeap<T>::insert(const T data, const int key) {  // need to implement this function

}

template <typename T>
T MinHeap<T>::extract_min() {                          // need to implement this function

  T data;
  
   return data;
}

template <typename T>
T MinHeap<T>::peek() const{ // need to implement this function

}

template <typename T>
int MinHeap<T>::size() const{ // need to implement this function

}
