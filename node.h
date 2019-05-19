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
#include <vector>

namespace bst{

template <typename T>
struct Node {
  T data;
  unsigned int count;
  std::vector<int> line;
  std::vector<int> paragraph;
  struct Node* left;
  struct Node* right;

  Node (const T &data = T(), const unsigned int &c = 0);
  ~Node();
  Node(const Node<T> &other);

  Node<T>& operator=(const Node<T> &other);
  Node<T>& operator^=(Node<T> &other); // this is the swap function for Nodes to swap values
  Node<T>& operator-=(const unsigned int &c);
  Node<T>& operator+=(const unsigned int &c);

  bool empty() const;
  bool is_leaf() const {return (left == nullptr)&&(right == nullptr);}
  void Set(const T& d, const unsigned int &c);
  void SetLeft(Node<T> &other);
  void SetRight(Node<T> &other);
  void Clear(); // This function clears all values from a Node

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
  bool operator>>(std::istream& in, Node<S> &n);

private:
  void copy(const Node<T> &other);
};


/**
 * @brief Default constructor for the Node
 * @param d the data
 * @param c the count of the data
 */
template<typename T>
Node<T>::Node(const T &d, const unsigned int &c)
    : data(d),
      count(c),
      left(nullptr),
      right(nullptr) {
}

/**
 * This is the destructor for the node, which clears the data within the node and sets own children to
 * nullptr.
 */
template<typename T>
Node<T>::~Node() {
  data = T();
  count = 0;
  left = right = nullptr;
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
 * This function swaps the values of two Nodes (not including the child links)
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
  other.count ^= count ^= other.count ^= count;
  return *this;
}

template<typename T>
Node<T> &Node<T>::operator-=(const unsigned int &c) {
// if c is greater than current count, then set count to 0, otherwise, subtract c from count
  count = (c>=count) ? 0 : count - c;
  return *this;
}

template<typename T>
Node<T> &Node<T>::operator+=(const unsigned int &c) {
  count += c;
  return *this;
}

template<typename T>
bool Node<T>::empty() const {
  return count == 0;
}

template<typename T>
void Node<T>::Set(const T &d, const unsigned int &c) {
  data = d;
  count = c;
}

template <typename T>
void Node<T>::SetLeft(Node<T> &other) {
  left = other;
}

template<typename T>
void Node<T>::SetRight(Node<T> &other) {
  right = other;
}

/**
 * This function simply clears the data within the node, but does not delete the link to its children.
 */
template<typename T>
void Node<T>::Clear() {
  data = T();
  count = 0;
}

template<typename T>
void Node<T>::copy(const Node<T> &other) {
  Set(other.data, other.count);
  left = other.left;
  right = other.right;
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
bool operator>>(std::istream &in, Node<S> &n) {
//    char junk;
  if (&in == &std::cin) {
    std::string line;
    std::cout << "Data: ";
    if (std::cin>>n.data) { // todo need some data validation
      getline(in,line);
      n.count = line.empty() ? 1 : stoi(line);
      fflush(stdin);
      return true;
    } else
      return false;
  }
  else
//        in >> n.data >> junk >> n.count >> junk;
    std::cout << "test"; // todo

  return false;
}


} // end namespace bst


#endif // Node_H
