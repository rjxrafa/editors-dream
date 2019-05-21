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
    void insertData(const T &data,const int &paragr, const int &index);
    void extractData(T &data, int &paragr, int &index);
    myHeap<T>& operator>>(T &data);
    bool empty() const;
    bool full() const;
    unsigned int size() const;
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
    std::vector<T> theWords_;
    std::vector<int> paragraph_;
    std::vector<int> lineNumber_;
    std::vector<int> theHeap_;
    void shuffleUp();
    bool shuffleDown(int i);
    bool xorSwap(int &x, int &y);
    bool setLeast(int &x, int y);
    void copy(const myHeap<T> &other);
};

template<typename T>
myHeap<T>::myHeap()
{

}

template<typename T>
myHeap<T>::~myHeap()
{
    theWords_.clear();
    paragraph_.clear();
    lineNumber_.clear();
    theHeap_.clear();
}

template<typename T>
myHeap<T>::myHeap(const myHeap<T> &other)
{
    copy(other);
}

template<typename T>
myHeap<T>& myHeap<T>::operator=(const myHeap<T> &other)
{
    if(this != &other)
    {
        copy(other);
    }
    return *this;
}

template<typename T>
void myHeap<T>::insertData(const T &data, const int &paragr, const int &index)
{
    theWords_.push_back(data);
    paragraph_.push_back(paragr);
    lineNumber_.push_back(index);
    theHeap_.push_back(theWords_.size()-1);
    shuffleUp();
}

template<typename T>
void myHeap<T>::extractData(T &data, int &paragr, int &index)
{
    if(empty())
        throw EMPTY;
    data = theWords_[theHeap_[0]];
    paragr = paragraph_[theHeap_[0]];
    index = lineNumber_[theHeap_[0]];
    if(theHeap_.size() > 1)
        xorSwap(theHeap_[0],theHeap_[theHeap_.size()-1]);
    theHeap_.pop_back();
    shuffleDown(0);
}

template<typename T>
myHeap<T>& myHeap<T>::operator>>(T &data)
{
    if(empty())
        throw EMPTY;
    data = theWords_[theHeap_[0]];
    if(theHeap_.size() > 1)
        xorSwap(theHeap_[0],theHeap_[theHeap_.size()-1]);
    theHeap_.pop_back();
    shuffleDown(0);
    return *this;
}

template<typename T>
bool myHeap<T>::empty() const
{
    return !theHeap_.size();
}

template<typename T>
bool myHeap<T>::full() const
{
    return false;
}

template<typename T>
unsigned int myHeap<T>::size() const
{
    return theHeap_.size();
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
    int i = theHeap_.size()-1;
    while (i != 0 && theWords_[theHeap_[parent(i)]] > theWords_[theHeap_[i]])
       {
          xorSwap(theHeap_[i], theHeap_[parent(i)]);
          i = parent(i);
       }
    return;         //swap(theWords_[i], theWords_[parent(i)]);
}

template<typename T>
bool myHeap<T>::shuffleDown(int i)
{
    //left 2n+1, right 2n+2
    int left = leftChild(i), right = rightChild(i), toBeSwapped = i;
    //first check if it is within the vector then if the left is less than it
    (left < theHeap_.size())&&(theWords_[theHeap_[left]] < theWords_[theHeap_[i]])&&setLeast(toBeSwapped,left);
    //if so set it to the left and then check if the right is less than it
    (right < theHeap_.size())&&(theWords_[theHeap_[right]] < theWords_[theHeap_[toBeSwapped]])&&setLeast(toBeSwapped,right);
    (toBeSwapped != i)&&xorSwap(theHeap_[i], theHeap_[toBeSwapped])&&shuffleDown(toBeSwapped);
    return true;
}

template<typename T>
bool myHeap<T>::xorSwap(int &x, int &y)
{
    x ^= y ^= x ^= y;
    return true;
}

template<typename T>
bool myHeap<T>::setLeast(int &x, int y)
{
    x = y;
    return true;
}

template<typename T>
void myHeap<T>::copy(const myHeap<T> &other)
{
    theWords_ = other.theWords_;
    paragraph_ = other.paragraph_;
    lineNumber_ = other.lineNumber_;
    theHeap_ = other.theHeap_;
}

template<typename S>
std::ostream& operator<<(std::ostream &out, const myHeap<S> &heap)
{
    for(unsigned int i = 0; i < heap.theWords_.size(); ++i)
        std::cout<<heap.theWords_[heap.theHeap_[i]]<<std::endl;
    return out;
}

template<typename S>
std::istream& operator>>(std::istream &in, myHeap<S> &heap)
{

    return in;
}

#endif // HEAP_H
