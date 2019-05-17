/****
 * This Binary Tree class has been adapted from Walter Savitch's Data Structures textbook.
 *
 * @author      Rafael Betita
 * @modified    05-16-2019
 ****/

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <node.h>
#include <QtDebug>

namespace bt {

enum class BT_TRAVERSAL{PRE_ORDER, IN_ORDER, POST_ORDER, BACKWARD_IN_ORDER};

template <typename T>
class BinaryTree
{
 public:
  BinaryTree(
    const Node<T> data = Node<T>(), BinaryTree<T>* left = nullptr, BinaryTree<T>* right = nullptr)
  {
    data_ = data;
    left_ = left;
    right_ = right;
  }

  Node<T>& data() {return data_;}
  Node<T>*& left() {return left_;}
  Node<T>*& right() {return right_;}
  void SetData(const Node<T>& data) {data_ = data;}
  void SetLeft(const Node<T>& data) {left_ = data;}
  void SetRight(const Node<T>& data) {right_ = data;}
  void ClearTree(BinaryTree<T>*& root);
  BinaryTree<T>* CopyTree(const BinaryTree<T>* root);

  const Node<T>& data() const {return data_;}
  const Node<T>* left() const {return left_;}
  const Node<T>* right() const {return right_;}
  void PrintTree(const BinaryTree<T>* node, const BT_TRAVERSAL method = POST_ORDER) const;
  bool IsLeaf() const {return (left_ == nullptr)&&(right_ == nullptr);}
  unsigned int size(const BinaryTree<T>* root) const;
  unsigned int height(const BinaryTree<T>* root) const;
  const Node<T>& Find(const BinaryTree<T>* root, const T& data) const;

 private:
  Node<T> data_;
  BinaryTree<T> *left_;
  BinaryTree<T> *right_;
};

#include "binarytree.tpp"

} // end namespace myBinaryTree

#endif // BINARYTREE_H
