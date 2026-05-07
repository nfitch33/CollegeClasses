#include <array>
using namespace std;

const int SIZE = 10;

template <class elemType>
class arrayListType {
    public:
        //default index is 0
        int seqSearch(const elemType& item, int i = 0) const;
        void setArray(const elemType& data, int index);
    private:
        elemType array[SIZE];
};

template <class elemType>
int arrayListType<elemType>::seqSearch(const elemType& item, int i) const{
    //return -1 if item is not in the array
    if(i > SIZE || i < 0){
        return -1;
    }
    
    //return current index if item is there
    if(array[i] == item){
        return i;
    }

    //recursive call to next index
    else{
        return seqSearch(item, i+1);
    }
}

template <class elemType>
void arrayListType<elemType>::setArray(const elemType& data, int index){
    if(index > SIZE || index < 0){
        return;
    }
    else{
        array[index] = data;
    }
}