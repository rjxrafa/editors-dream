//@author Ara Mico Segismundo
#ifndef HEAP_H
#define HEAP_H


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

enum HEAP_ERRORS {FULL, EMPTY};

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

//    template<typename S>
//    friend
//    std::ostream& operator<<(std::ostream &, const myHeap<S> &);

//    template<typename S>
//    friend
//    std::istream& operator>>(std::istream &, myHeap<S> &);

private:
    std::vector<T> theWords;
    std::vector<int> paragraph;
    std::vector<int> lineNumber;
    std::vector<int> theHeap;
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
    theWords.clear();
    paragraph.clear();
    lineNumber.clear();
    theHeap.clear();
}

template<typename T>
myHeap<T>::myHeap(const myHeap<T> &other)
{
    theWords = other.theWords;
    paragraph = other.paragraph;
    lineNumber = other.lineNumber;
    theHeap = other.theHeap;
}

template<typename T>
myHeap<T>& myHeap<T>::operator=(const myHeap<T> &other)
{
    if(this != &other)
    {
        theWords = other.theWords;
        paragraph = other.paragraph;
        lineNumber = other.lineNumber;
        theHeap = other.theHeap;
    }
    return *this;
}

//template<typename T>
//myHeap<T>& myHeap<T>::operator<<(const T &data, int paragr, int index)
//{
//    theWords.push_back(data);
//    paragraph.push_back(paragr);
//    lineNumber.push_back(index);
//    theHeap.push_back(theWords.size()-1);
//    shuffleUp();
//    return *this;
//}

template<typename T>
void myHeap<T>::insertData(const T &data, const int &paragr, const int &index)
{
    theWords.push_back(data);
    paragraph.push_back(paragr);
    lineNumber.push_back(index);
    theHeap.push_back(theWords.size()-1);
    shuffleUp();
}

template<typename T>
void myHeap<T>::extractData(T &data, int &paragr, int &index)
{
    if(empty())
        throw EMPTY;
    data = theWords[theHeap[0]];
    paragr = paragraph[theHeap[0]];
    index = lineNumber[theHeap[0]];
    xorSwap(theHeap[0],theHeap[theWords.size()-1]);
    theWords.pop_back();
    paragraph.pop_back();
    lineNumber.pop_back();
    shuffleDown(0);
}

template<typename T>
myHeap<T>& myHeap<T>::operator>>(T &data)
{
    if(empty())
        throw EMPTY;
    //data = theWords[0];
  //  swap(theWords[0],theWords[theWords.size()-1]);
    data = theWords[theHeap[0]];
    //swap(theWords[0],theWords[theWords.size()-1]);
    xorSwap(theHeap[0],theHeap[theWords.size()-1]);
   // data = theWords.back();
    theWords.pop_back();
    shuffleDown(0);
    return *this;
}

template<typename T>
bool myHeap<T>::empty()
{
    return theWords.size() == 0;
}

template<typename T>
bool myHeap<T>::full()
{
    return false;
}

template<typename T>
unsigned int myHeap<T>::size()
{
    return theWords.size();
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
    int i = theWords.size()-1;
    while (i != 0 && theWords[theHeap[parent(i)]] > theWords[theHeap[i]])
       {
          //swap(theWords[i], theWords[parent(i)]);
          xorSwap(theHeap[i], theHeap[parent(i)]);
          i = parent(i);
       }
}

template<typename T>
void myHeap<T>::shuffleDown(int i)
{
    int left = leftChild(i);
    int right = rightChild(i);
    int smallest = i;
    if (left < theWords.size() && theWords[theHeap[left]] < theWords[theHeap[i]])
        smallest = left;
    if (right < theWords.size() && theWords[theHeap[right]] < theWords[theHeap[smallest]])
        smallest = right;
    if (smallest != i)
    {
       //swap(theWords[i], theWords[smallest]);
        xorSwap(theHeap[i], theHeap[smallest]);
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
    for(unsigned int i = 0; i < heap.theWords.size(); ++i)
        std::cout<<heap.theWords[heap.theHeap[i]]<<std::endl;
    return out;
}

template<typename S>
std::istream& operator>>(std::istream &in, myHeap<S> &heap)
{

    return in;
}

#endif // HEAP_H
