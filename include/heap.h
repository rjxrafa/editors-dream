//@author Ara Mico Segismundo
//min heap array implementation with "pointers"
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

//#define leftChild(x) (2*x + 1)
//#define rightChild(x) (2*x + 2)
//#define parent(x) ((x-1)/2)

enum HEAP_ERRORS {FULL, EMPTY};

template<typename T>
/**
 * @brief The myHeap class
 * min heap implementation with fake pointers
 */
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
    void sort();

    template<typename S>
    friend
    std::ostream& operator<<(std::ostream &, const myHeap<S> &);

    template<typename S>
    friend
    std::istream& operator>>(std::istream &, myHeap<S> &);

private:
    std::vector<T> theWords_;
    std::vector<int> paragraph_;
    std::vector<int> lineNumber_;
    std::vector<int> theHeap_;
    void shuffleUp();
    bool shuffleDown(int i);
    bool xorSwap(int &x, int &y);
//    bool setLeast(int &x, int y);
    void copy(const myHeap<T> &other);
};

template<typename T>
/**
 * @brief constructor is empty because vectors handle it
 */
myHeap<T>::myHeap()
{

}

template<typename T>
/**
 * @brief clear works because no node or pointers are used
 */
myHeap<T>::~myHeap()
{
    theWords_.clear();
    paragraph_.clear();
    lineNumber_.clear();
    theHeap_.clear();
}

template<typename T>
/**
 * @brief myHeap<T>::myHeap copies another heap using vector stl
 * @param other
 */
myHeap<T>::myHeap(const myHeap<T> &other)
{
    copy(other);
}

template<typename T>
/**
 * @brief assignment operator copies another heap using vector stl
 * @param other
 * @return
 */
myHeap<T>& myHeap<T>::operator=(const myHeap<T> &other)
{
    if(this != &other)
    {
        copy(other);
    }
    return *this;
}

template<typename T>
/**
 * @brief myHeap<T>::insertData inserts data using pushback and keeping "pointers" in
 * the heap vector.
 * @param data
 * @param paragr
 * @param index
 */
inline void myHeap<T>::insertData(const T &data, const int &paragr, const int &index)
{
    theWords_.push_back(data);
    paragraph_.push_back(paragr);
    lineNumber_.push_back(index);
    theHeap_.push_back(theWords_.size()-1);
    shuffleUp();
}

template<typename T>
/**
 * @brief myHeap<T>::extractData uses the "pointers" to get the top of the heap
 * only pointers need to be deleted since it uses size of another vector
 * @param data
 * @param paragr
 * @param index
 */
inline void myHeap<T>::extractData(T &data, int &paragr, int &index)
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
/**
 * @brief myHeap<T>::operator >> if we only need to pull data
 * overloaded >> is used
 * @param data
 * @return
 */
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
/**
 * @brief myHeap<T>::empty if size is 0
 * @return
 */
bool myHeap<T>::empty() const
{
    return !theHeap_.size();
}

template<typename T>
/**
 * @brief myHeap<T>::full will never be full because we pushback
 * @return
 */
bool myHeap<T>::full() const
{
    return false;
}

template<typename T>
/**
 * @brief myHeap<T>::size only needs the size of the "pointers"
 * @return
 */
unsigned int myHeap<T>::size() const
{
    return theHeap_.size();
}

template<typename T>
/**
 * @brief myHeap<T>::parent is n-1/2 ex:2-1/2 = 0 in c++
 * @param i
 * @return
 */
inline int myHeap<T>::parent(int i)
{
    return (i-1)/2;
}

template<typename T>
/**
 * @brief myHeap<T>::leftChild 2n+1
 * @param i
 * @return
 */
inline int myHeap<T>::leftChild(int i)
{
    return (2*i)+1;
}

template<typename T>
/**
 * @brief myHeap<T>::rightChild 2n+2
 * @param i
 * @return
 */
inline int myHeap<T>::rightChild(int i)
{
    return (2*i)+2;
}

template<typename T>
/**
 * @brief myHeap<T>::shuffleUp insert and shuffle from the end
 */
void myHeap<T>::shuffleUp()
{
    int i = theHeap_.size()-1;
    while (i != 0 && theWords_[theHeap_[parent(i)]] > theWords_[theHeap_[i]])
       {
          xorSwap(theHeap_[i], theHeap_[parent(i)]);
          i = parent(i);
       }
    return;
}

template<typename T>
/**
 * @brief myHeap<T>::shuffleDown replace 0th index with last then needed to shuffle down
 * uses professors concept of no ifs
 * @param i
 * @return
 */
inline bool myHeap<T>::shuffleDown(int i)
{
    //left 2n+1, right 2n+2
    int left = leftChild(i), right = rightChild(i), toBeSwapped = i;
    //first check if it is within the vector then if the left is less than it
    (left < theHeap_.size())&&(theWords_[theHeap_[left]] < theWords_[theHeap_[i]])&&(toBeSwapped = left);
    //if so set it to the left and then check if the right is less than it
    (right < theHeap_.size())&&(theWords_[theHeap_[right]] < theWords_[theHeap_[toBeSwapped]])&&(toBeSwapped = right);
    (toBeSwapped != i)&&xorSwap(theHeap_[i], theHeap_[toBeSwapped])&&shuffleDown(toBeSwapped);
    return true;
//    xorSwap(theHeap_[0], theHeap_[i]); //Removed root from the heap
                                       //by swapping with last node
                                       //entered into the heap;
//    int lastEntered = i - 1,
//        nodeToMove = 0,                //Make the last entered one less
//                                       //on node list and start off with
//                                       //the root
//        toCompare = 0;
//    bool switched;//Node to compare with
//    bool done = false;                 //Semiphore to determine if
//    //more shuffling needs to be done
//    while(!done)
//    {
//        switched=false;
//        //if the left child is less than the parent
//        if(leftChild(nodeToMove) <= lastEntered && theWords_[theHeap_[leftChild(nodeToMove)]] < theWords_[theHeap_[nodeToMove]])
//        {
//            switched = true;
//            toCompare = leftChild(nodeToMove);
//        }
//        if(rightChild(nodeToMove) <= lastEntered && theWords_[theHeap_[rightChild(nodeToMove)]] < theWords_[theHeap_[toCompare]])
//        {
//            switched = true;
//            toCompare = rightChild(nodeToMove);
//        }
//        if(switched)
//        {
//            xorSwap(theHeap_[toCompare],theHeap_[nodeToMove]);
//            nodeToMove = toCompare;
//        }
//        else
//            done = true;
//    }
}
//template<typename T>
//void myHeap<T>::sort()
//{
//    for(int i = theHeap_.size()-1; i > 0; --i)
//        shuffleDown(i);
//}

template<typename T>
/**
 * @brief myHeap<T>::xorSwap implementation
 * @param x
 * @param y
 * @return
 */
inline bool myHeap<T>::xorSwap(int &x, int &y)
{
    x ^= y ^= x ^= y; return true;
}

//template<typename T>
/**
 * @brief myHeap<T>::setLeast
 * @param x number
 * @param y the least
 * @return
 */
//inline bool myHeap<T>::setLeast(int &x, int y)
//{
//    x = y; return true;
//}

template<typename T>
/**
 * @brief myHeap<T>::copy uses vectors = to copy
 * @param other
 */
void myHeap<T>::copy(const myHeap<T> &other)
{
    theWords_ = other.theWords_;
    paragraph_ = other.paragraph_;
    lineNumber_ = other.lineNumber_;
    theHeap_ = other.theHeap_;
}

template<typename S>
/**
 * @brief operator << output overload
 * @param out
 * @param heap
 * @return
 */
std::ostream& operator<<(std::ostream &out, const myHeap<S> &heap)
{
    for(unsigned int i = 0; i < heap.theWords_.size(); ++i)
        std::cout<<heap.theWords_[heap.theHeap_[i]]<<std::endl;
    return out;
}

template<typename S>
/**
 * @brief operator >> input overload
 * @param in
 * @param heap
 * @return
 */
std::istream& operator>>(std::istream &in, myHeap<S> &heap)
{
    std::string word;
    int num;
    std::cout<<"word"<<std::endl;
    in>>word;
    heap.theWords_.push_back(word);
    std::cout<<"paragraph"<<std::endl;
    in>>num;
    heap.paragraph_.push_back(num);
    std::cout<<"line"<<std::endl;
    in>>num;
    heap.lineNumber_.push_back(num);
    heap.theHeap_.push_back(heap.theWords_.size()-1);
    return in;
}

#endif // HEAP_H
