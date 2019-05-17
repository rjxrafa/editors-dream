#include "binarytree.h"

/**
 * This function will clear the nodes from a given tree's root and return
 * them to the heap.
 *
 * @author      Rafael Betita
 * @modified    05-16-2019
 **/
template <typename T>
void bt::BinaryTree<T>::ClearTree(BinaryTree<T>*& root) {
  if (root == nullptr)
    return;
  ClearTree(root->left());
  ClearTree(root->right());
  delete root;
  root = nullptr;
}

/***
 * This function copies a given tree recursively and returns the pointer to
 * a new instance of that tree.
 *
 * @author     Rafael Betita
 * @modified  05-16-2019
 ***/
template <typename T>
bt::BinaryTree<T>* bt::BinaryTree<T>::CopyTree(const BinaryTree* root) {

  BinaryTree<T> *left;
  BinaryTree<T> *right;

  if (root == nullptr) {
    return nullptr;
  } else {
    left = CopyTree(root->left());
    right = CopyTree(root->right());
    return new BinaryTree<T>(root->data(), left, right);
  }
}

template <typename T>
void bt::BinaryTree<T>::PrintTree(const BinaryTree<T>* node, const BT_TRAVERSAL method) const {

  if (node != nullptr) {
    if (method == BT_TRAVERSAL::PRE_ORDER) {
      qDebug() << node->data() << endl;
      PrintTree(node->left(), BT_TRAVERSAL::PRE_ORDER);
      PrintTree(node->right(), BT_TRAVERSAL::PRE_ORDER);
    } else if (method == BT_TRAVERSAL::IN_ORDER) {
        PrintTree(node->left(), BT_TRAVERSAL::IN_ORDER);
        qDebug() << node->data() << endl;
        PrintTree(node->right(), BT_TRAVERSAL::IN_ORDER);
    } else if (method == BT_TRAVERSAL::POST_ORDER)
        PrintTree(node->left(), BT_TRAVERSAL::IN_ORDER);
        PrintTree(node->right(), BT_TRAVERSAL::IN_ORDER);
        qDebug() << node->data() << endl;
  }
}

template <typename T>
unsigned int bt::BinaryTree<T>::size(const BinaryTree<T>* root) const {
  if (root == nullptr)
    return 0;
  else
    return (size(root->left() + 1 + size(right())));
}

template <typename T>
unsigned int bt::BinaryTree<T>::height(const BinaryTree<T>* root) const {
  if (root == nullptr)
    return 0;
  else {
    unsigned int left_height = height(root->left);
    unsigned int right_height = height(root->right);

    if (left_height > right_height)
      return ++left_height;
    else {
      return ++right_height;
    }
  }

}

template <typename T>
const bt::Node<T>& bt::BinaryTree<T>::Find(const bt::BinaryTree<T>* root, const T& data) const {
  if (root == nullptr)
    return nullptr;
  while(root) {
    if (data == root->data())
      return root;
    else if (data > root->data())
      root = root->right();
    else {
      root = root->left();
    }
  }
  return nullptr;
}

