/****
 * This Node implementation has been adapted from Paul Wilkinson's CS008 lectures.
 *
 * @author      Rafael Betita
 * @modified    05-16-2019
 ****/

#ifndef Node_H
#define Node_H

#include <iostream>
#include <cstdio>

namespace bt{

template <typename T>
struct Node {
    T data;
    unsigned int count;
    Node* lineNumbers; //need container for line Numbers

    Node (const T &data = T(), int count= 0);
    ~Node();
    Node(const Node<T> &other);

    Node<T>& operator=(const Node<T> &other);
    Node<T>& operator^=(Node<T> &other); // this is the swap function for Nodes to swap values
    Node<T>& operator-=(unsigned int c);
    Node<T>& operator+=(unsigned int c);

    bool empty() const;
    void set(const T& d, unsigned int c);
    void clear(); // This function clears all values from a Node

    // Node-Node comparison operators
    template<typename S>
    friend
    bool operator<(const Node<S> &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator<=(const Node<S> &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator>(const Node<S> &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator>=(const Node<S> &x, const Node<S> &y);

    // This will check for data match
    template<typename S>
    friend
    bool operator==(const Node<S> &x, const Node<S> &y);

    // This will check for exact match (data & count)
    template<typename S>
    friend
    bool operator&=(const Node<S> &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator!=(const Node<S> &x, const Node<S> &y);

    // Data-Node comparison operators
    template<typename S>
    friend
    bool operator<(const S &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator<=(const S &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator>(const S &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator>=(const S &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator==(const S &x, const Node<S> &y);

    template<typename S>
    friend
    bool operator!=(const S &x, const Node<S> &y);

    // Node-Data comparison operators
    template<typename S>
    friend
    bool operator<(const Node<S> &x, const S &y);

    template<typename S>
    friend
    bool operator<=(const Node<S> &x, const S &y);

    template<typename S>
    friend
    bool operator>(const Node<S> &x, const S &y);

    template<typename S>
    friend
    bool operator>=(const Node<S> &x, const S &y);

    template<typename S>
    friend
    bool operator==(const Node<S> &x, const S &y);

    template<typename S>
    friend
    bool operator!=(const Node<S> &x, const S &y);

    template<typename S>
    friend
    std::ostream& operator<<(std::ostream& out, const Node<S> &n);

    template<typename S>
    friend
    void operator>>(std::istream& in, Node<S> &n);


private:
    void copy(const Node<T> &other);
};

template<typename T>
Node<T>::Node(const T &d, int c) {
    set(d,c);
}

template<typename T>
Node<T>::~Node() {
    clear();
}

template<typename T>
Node<T>::Node(const Node<T> &other) {
    copy(other);
}

template<typename T>
Node<T> &Node<T>::operator=(const Node<T> &other) {
    if (this != &other)
        copy(other);
    return *this;
}

/**
 * This function swaps the values of two Nodes
 * @tparam T
 * @param other
 * @return
 */
template<typename T>
Node<T> &Node<T>::operator^=(Node<T> &other) {
    T temp = data;
    data = other.data;
    other.data = temp;

    // XOR Swap for ints
    other.count ^= count ^=other.count ^= count;
    return *this;
}

template<typename T>
Node<T> &Node<T>::operator-=(unsigned int c) {
// if c is greater than current count, then set count to 0, otherwise, subtract c from count
    count = (c>=count) ? 0 : count - c;
    return *this;
}

template<typename T>
Node<T> &Node<T>::operator+=(unsigned int c) {
    count += c;
    return *this;
}

template<typename T>
bool Node<T>::empty() const {
    return count == 0;
}

template<typename T>
void Node<T>::set(const T &d, unsigned int c) {
    data = d;
    count = c;
}

template<typename T>
void Node<T>::clear() {
    set(T(), 0);
}

template<typename T>
void Node<T>::copy(const Node<T> &other) {
    set(other.data, other.count);
}

/// Node-Node comparison operators

template<typename S>
bool operator<(const Node<S> &x, const Node<S> &y) {
    return x.data < y.data;
}

template<typename S>
bool operator<=(const Node<S> &x, const Node<S> &y) {
    return x.data <= y.data;
}

template<typename S>
bool operator>(const Node<S> &x, const Node<S> &y) {
    return x.data > y.data;
}

template<typename S>
bool operator>=(const Node<S> &x, const Node<S> &y) {
    return x.data >= y.data;
}

template<typename S>
bool operator==(const Node<S> &x, const Node<S> &y) {
    return x.data == y.data;
}

template<typename S>
bool operator&=(const Node<S> &x, const Node<S> &y) {
    return (x.data == y.data) && (x.count == y.count);
}

template<typename S>
bool operator!=(const Node<S> &x, const Node<S> &y) {
    return x.data != y.data;
}

/// Data-Node comparison operators

template<typename S>
bool operator<(const S &x, const Node<S> &y) {
    return x < y.data;
}

template<typename S>
bool operator<=(const S &x, const Node<S> &y) {
    return x <= y.data;
}

template<typename S>
bool operator>(const S &x, const Node<S> &y) {
    return x > y.data;
}

template<typename S>
bool operator>=(const S &x, const Node<S> &y) {
    return x >= y.data;
}

template<typename S>
bool operator==(const S &x, const Node<S> &y) {
    return x == y.data;
}

template<typename S>
bool operator!=(const S &x, const Node<S> &y) {
    return x != y.data;
}

/// Node-data comparison operators

template<typename S>
bool operator<(const Node<S> &x, const S &y) {
    return x.data < y;
}

template<typename S>
bool operator<=(const Node<S> &x, const S &y) {
    return x.data <= y;
}

template<typename S>
bool operator>(const Node<S> &x, const S &y) {
    return x.data > y;
}

template<typename S>
bool operator>=(const Node<S> &x, const S &y) {
    return x.data >= y;
}

template<typename S>
bool operator==(const Node<S> &x, const S &y) {
    return x.data == y;
}

template<typename S>
bool operator!=(const Node<S> &x, const S &y) {
    return x.data != y;
}

template<typename S>
std::ostream &operator<<(std::ostream &out, const Node<S> &n) {
    out << n.data << "  (" << n.count << ") ";
    return out;
}

template<typename S>
void operator>>(std::istream &in, Node<S> &n) {
    std::string line;
//    char junk;
    if (&in == &std::cin) {
        std::cout << "Data: ";
        std::cin >> n.data; // todo: add data validation
        getline(in,line);
        n.count = line.empty() ? 1 : stoi(line);
        fflush(stdin);
    }
    else
//        in >> n.data >> junk >> n.count >> junk;
        std::cout << "test";

}

} // end namespace myBinaryTree

#endif // Node_H
