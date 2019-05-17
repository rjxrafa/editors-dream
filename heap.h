#ifndef HEAP_H
#define HEAP_H


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

enum HEAP_ERRORS {FULL, EMPTY, ILLEGAL_CHANGE};

template<typename T>
class myHeap
{
public:
    myHeap();
    ~myHeap();
    myHeap(const myHeap<T> &other);
    myHeap<T>& operator=(const myHeap<T> &other);
//    myHeap<T>& operator<<(const T &data);
    void insertData(const T &data,const int &paragr, const int &index);
    void extractData(T &data, int &paragr, int &index);
    myHeap<T>& operator>>(T &data);
    bool empty();
    bool full();
    unsigned int size();
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);

    template<typename S>
    friend
    std::ostream& operator<<(std::ostream &, const myHeap<S> &);

    template<typename S>
    friend
    std::istream& operator>>(std::istream &, myHeap<S> &);

private:
    std::vector<T> theHeap;
    std::vector<int> paragraph;
    std::vector<int> lineNumber;
    std::vector<int> myPointer;
    void shuffleUp();
    void shuffleDown(int i);
    //void swap(T &x, T &y);
    void xorSwap(int &x, int &y);
};

template<typename T>
myHeap<T>::myHeap()
{

}

template<typename T>
myHeap<T>::~myHeap()
{
    theHeap.clear();
    myPointer.clear();
}

template<typename T>
myHeap<T>::myHeap(const myHeap<T> &other)
{
    theHeap = other.theHeap;
    myPointer = other.myPointer;
}

template<typename T>
myHeap<T>& myHeap<T>::operator=(const myHeap<T> &other)
{
    if(this != &other)
    {
        theHeap = other.theHeap;
        myPointer = other.myPointer;
    }
    return *this;
}

//template<typename T>
//myHeap<T>& myHeap<T>::operator<<(const T &data, int paragr, int index)
//{
//    theHeap.push_back(data);
//    paragraph.push_back(paragr);
//    lineNumber.push_back(index);
//    myPointer.push_back(theHeap.size()-1);
//    shuffleUp();
//    return *this;
//}

template<typename T>
void myHeap<T>::insertData(const T &data, const int &paragr, const int &index)
{
    theHeap.push_back(data);
    paragraph.push_back(paragr);
    lineNumber.push_back(index);
    myPointer.push_back(theHeap.size()-1);
    shuffleUp();
}

template<typename T>
myHeap<T>& myHeap<T>::operator>>(T &data)
{
    if(empty())
        throw EMPTY;
    //data = theHeap[0];
  //  swap(theHeap[0],theHeap[theHeap.size()-1]);
    data = theHeap[myPointer[0]];
    //swap(theHeap[0],theHeap[theHeap.size()-1]);
    xorSwap(myPointer[0],myPointer[theHeap.size()-1]);
   // data = theHeap.back();
    theHeap.pop_back();
    shuffleDown(0);
    return *this;
}

template<typename T>
bool myHeap<T>::empty()
{
    return theHeap.size() == 0;
}

template<typename T>
bool myHeap<T>::full()
{
    return false;
}

template<typename T>
unsigned int myHeap<T>::size()
{
    return theHeap.size();
}

template<typename T>
int myHeap<T>::parent(int i)
{
    return (i-1)/2;
}

template<typename T>
int myHeap<T>::leftChild(int i)
{
    return (2*i)+1;
}

template<typename T>
int myHeap<T>::rightChild(int i)
{
    return (2*i)+2;
}

template<typename T>
void myHeap<T>::shuffleUp()
{
    int i = theHeap.size()-1;
    while (i != 0 && theHeap[myPointer[parent(i)]] > theHeap[myPointer[i]])
       {
          //swap(theHeap[i], theHeap[parent(i)]);
          xorSwap(myPointer[i], myPointer[parent(i)]);
          i = parent(i);
       }
}

template<typename T>
void myHeap<T>::shuffleDown(int i)
{
    int left = leftChild(i);
    int right = rightChild(i);
    int smallest = i;
    if (left < theHeap.size() && theHeap[myPointer[left]] < theHeap[myPointer[i]])
        smallest = left;
    if (right < theHeap.size() && theHeap[myPointer[right]] < theHeap[myPointer[smallest]])
        smallest = right;
    if (smallest != i)
    {
       //swap(theHeap[i], theHeap[smallest]);
        xorSwap(myPointer[i], myPointer[smallest]);
        shuffleDown(smallest);
    }
    return;
}

//template<typename T>
//void myHeap<T>::swap(T &x, T &y)
//{
//    T temp = x;
//    x = y;
//    y = temp;
//}

template<typename T>
void myHeap<T>::xorSwap(int &x, int &y)
{
    x ^= y ^= x ^= y;
}

template<typename S>
std::ostream& operator<<(std::ostream &out, const myHeap<S> &heap)
{
    for(unsigned int i = 0; i < heap.theHeap.size(); ++i)
        std::cout<<heap.theHeap[heap.myPointer[i]]<<std::endl;
    return out;
}

template<typename S>
std::istream& operator>>(std::istream &in, myHeap<S> &heap)
{
    return in;
}

#endif // HEAP_H
