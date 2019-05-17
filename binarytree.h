/****
 * This Binary Tree class has been adapted from Walter Savitch's Data Structures textbook.
 *
 * @author      Rafael Betita
 * @modified    05-16-2019
 ****/

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <node.h>

namespace bt {

template <typename T>
class BinaryTree
{
 public:
  BinaryTree(
    const Node<T> data = Node<T>(), BinaryTree* left = NULL, BinaryTree* right = NULL)
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

  const Node<T>& data() const {return data_;}
  const Node<T>* left() const {return left_;}
  const Node<T>* right() const {return right_;}
  bool IsLeaf() const {return (left_ == nullptr)&&(right_ == nullptr);}

 private:
  Node<T> data_;
  Node<T> *left_;
  Node<T> *right_;
};

#include "binarytree.template"

} // end namespace myBinaryTree

#endif // BINARYTREE_H
