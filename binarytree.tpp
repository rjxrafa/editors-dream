#include "binarytree.h"

/**
 * @brief This function is called when initializing a new tree with a data and count
 * @param data the data being inserted
 * @param count the count of the data
 * @modified 2019-05-18
 */
template <typename T>
bst::BinaryTree<T>::BinaryTree(const T &data, const unsigned int &count) {
  root_ = new Node<T>(data, count);
  traversal_ = bst::BST_TRAVERSAL::IN_ORDER;
}

/**
 * @brief This is the copy constructor for the BinaryTree class
 * @param other
 * @modified 2019-05-18
 */
template <typename T>
bst::BinaryTree<T>::BinaryTree(const BinaryTree<T> &other) {
  CopyTree(other.root());
  traversal_ = other.traversal();
}

/**
 * @brief This is the default destructor for the BinaryTree class
 * @modified 2019-05-18
 */
template <typename T>
bst::BinaryTree<T>::~BinaryTree() {
    ClearTree(root_);
}

/**
 * @brief operator = This is the assignment operator for the BinaryTree class
 * @param other
 * @return the address of the newly assigned tree
 * @modified 2019-05-18
 */
template <typename T>
bst::BinaryTree<T>& bst::BinaryTree<T>::operator=(const BinaryTree<T> &other) {
  if (this != &other) {
    ClearTree(root_);
    CopyTree(other.root());
  }
  return this;
}

/**
 * @brief This function inserts a given data into a binary tree
 * @param data
 * @param count
 * @modified 2019-05-18
 */
template <typename T>
void bst::BinaryTree<T>::Insert(const T &data, const unsigned int &count) { //todo add rebalance
  bst::Node<T> *new_item = new bst::Node<T>(data, count);

  if(root_ == nullptr) {
    root_ = new_item;
    return;
  } else {
    bst::Node<T> *temp = root_;

    while (temp) {
      if (*new_item == *temp) { //dereference the node pointers as a node
        temp->count += count;
        std::cout << "test";
        delete new_item;
        return;
      }

      if (*new_item < *temp) { // if the item to be inserted is less than the current item
        if (temp->left) // if temp left is not null, keep traversing
          temp = temp->left;
        else {
          temp->left = new_item;
          return;
        }
      } else { // the item to be inserted is greater than the current item
        if (temp->right) // if temp right is not null, keep traversing
          temp = temp->right;
        else {
          temp->right = new_item;
          return;
        }
      }
    }
  }
}

/**
 * @brief operator << This function utilizes the Insert functionality of the BinaryTree class
 * @param data
 * @return
 * @modified 2019-05-18
 */
template <typename T>
bst::BinaryTree<T>& bst::BinaryTree<T>::operator<<(const T & data) {
  Insert(data);
  return *this;
}

/**
 * @brief Delete This function deletes N count occurences from the Binary Tree.
 * @param data
 * @param count
 */
template <typename T>
void bst::BinaryTree<T>::Delete(const T &data, const unsigned int &count) {
  //todo
}



/**
 * @brief This function will copy a given tree from its root node
 * @param root
 * @modified 2019-05-18
 * @note This implementation assumes that the caller is already empty
 */
template <typename T>
void bst::BinaryTree<T>::CopyTree(const Node<T>& root) {

  if (root == nullptr)
    return;

  Insert(root.data, root.count);
  CopyTree(root.left);
  CopyTree(root.right);
}

/**
 * This function will clear the tree from a given root node and return
 * them to the heap.
 *
 * @modified    2019-05-18
 **/
template <typename T>
void bst::BinaryTree<T>::ClearTree(Node<T>*& root) {
  if (root == nullptr)
    return;

  ClearTree(root->left);
  ClearTree(root->right);
  delete root;
  root = nullptr;
}

/**
 * @brief data_count This function will return a total data count for a given root node and its children
 * @param root
 * @return
 * @modified 2019-05-18
 */
template <typename T>
unsigned int bst::BinaryTree<T>::data_count(const Node<T>* &root) const {
  if (root == nullptr)
    return 0;
  else
    return (root->count + data_count(root->left) + data_count(root->right));
}

/**
 * @brief node_count This function will return a total node count for a given root node and its children
 * @param root
 * @return
 * @modified 2019-05-18
 */
template <typename T>
unsigned int bst::BinaryTree<T>::node_count(const Node<T>* &root) const {
  if (root == nullptr)
    return 0;
  else
    return (1 + node_count(root->left) + node_count(root->right));
}

/**
 * @brief bst::BinaryTree<T>::height
 * @param root
 * @return
 */
template <typename T>
unsigned int bst::BinaryTree<T>::height(const Node<T>* &root) const {
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

/**
 * @brief This function prints a given tree depending on the method passed
 * @param root
 * @param method
 * @modified 2019-05-18
 */
template <typename T>
void bst::BinaryTree<T>::PrintTree(std::ostream &out, const Node<T>* root, const BST_TRAVERSAL method) const {

  if (root != nullptr) {
    switch(method) {
    case BST_TRAVERSAL::IN_ORDER:
      PrintTree(out, root->left, BST_TRAVERSAL::POST_ORDER);
      PrintTree(out, root->right, BST_TRAVERSAL::POST_ORDER);
      out << '[' << root->data << ']' << '(' <<root->count  << ')' <<std::endl;
      break;
    case BST_TRAVERSAL::PRE_ORDER:
      out << '[' << root->data << ']' << '(' <<root->count  << ')' <<std::endl;
      PrintTree(out, root->left, BST_TRAVERSAL::PRE_ORDER);
      PrintTree(out, root->right, BST_TRAVERSAL::PRE_ORDER);
      break;
    case BST_TRAVERSAL::POST_ORDER:
      PrintTree(out, root->left, BST_TRAVERSAL::POST_ORDER);
      PrintTree(out, root->right, BST_TRAVERSAL::POST_ORDER);
      out << '[' << root->data << ']' << '(' <<root->count  << ')' <<std::endl;
      break;
    case BST_TRAVERSAL::BACKWARD_IN_ORDER:
      break; //todo implement
    default:
      out << "Invalid traversal method" << std::endl;
    }
  }
}

template <typename T>
const bst::Node<T>* bst::BinaryTree<T>::Find(const bst::BinaryTree<T>* root, const T& data) const {
//  if (root == nullptr) // if not found, then data is not found
//    return nullptr;
//  else {
//    if (data == root_->data)
//      return root;
//    else {
//      Node<T>* temp = Find(root_->left)
//    }
//  }
  //  while(root) {
//    if (data == root->data())
//      return root;
//    else if (data > root->data())
//      root = root->right();
//    else {
//      root = root->left();
//    }
//  }
//  return nullptr;
}

template <typename S>
std::ostream& operator<<(std::ostream& out, const bst::BinaryTree<S> &other) {
  other.PrintTree(out, other.root());
  return out;
}

template <typename S>
std::istream& operator>>(std::istream& in, bst::BinaryTree<S> &other) {
  bst::Node<S> temp;
  while (in >> temp) {
    other.Insert(temp.data, temp.count);
  }
  return in;
}

