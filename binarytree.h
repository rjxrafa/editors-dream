/****
 * This Binary Tree class has been adapted from Paul Wilkinson's CS008 lectures.
 *
 * @author      Rafael Betita
 * @modified    05-16-2019
 ****/

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"

namespace bst {

enum class BST_TRAVERSAL{PRE_ORDER, IN_ORDER, POST_ORDER, BACKWARD_IN_ORDER};

template <typename T>
class BinaryTree
{
 public:
  BinaryTree() : root_(nullptr), traversal_(BST_TRAVERSAL::IN_ORDER) {}
  BinaryTree(const T &data, const unsigned int &count);
  BinaryTree(const BinaryTree<T> &other);
  ~BinaryTree();
  BinaryTree<T> &operator=(const BinaryTree<T> &other);

  void Insert(const T &data, const unsigned int &count = 1);
  BinaryTree<T>& operator<<(const T & data);
  void Delete(const T &data, const unsigned int &count = 1);

  // Const members
  bool empty() {return !root_;}
  unsigned int data_count() const {return data_count(root_);}
  unsigned int node_count() const {return node_count(root_);}
  unsigned int height() const {return height(root_);}
  const Node<T>* root() const {return root_;}
  BST_TRAVERSAL traversal() const {return traversal;}
  void PrintTree(const Node<T>* root, const BST_TRAVERSAL method = BST_TRAVERSAL::POST_ORDER) const;
  const Node<T>* Find(const BinaryTree<T>* root, const T& data) const;

  template <typename S>
  friend
  std::ostream& operator<<(std::ostream& out, const BinaryTree<T> &other);

  template <typename S>
  friend
  std::istream& operator>>(std::ostream& out, const BinaryTree<T> &other);

 private:
  Node<T> *root_;
  BST_TRAVERSAL traversal_;

  void CopyTree(const Node<T>& root);
  void ClearTree(Node<T>*& root);

  unsigned int data_count(const Node<T>* &root) const;
  unsigned int node_count(const Node<T>* &root) const;
  unsigned int height(const Node<T>* &root) const;
};

#include "binarytree.tpp"

} // end namespace bst

#endif // BINARYTREE_H
