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

///**
// * @brief This function inserts a given data into a binary tree
// * @param data
// * @param count
// * @modified 2019-05-18
// */
//template <typename T>
//void bst::BinaryTree<T>::Insert(const T &data, const unsigned int &count) { //todo add rebalance
//  bst::Node<T> *new_item = new bst::Node<T>(data, count);

//  if(root_ == nullptr) {
//    root_ = new_item;
//    return;
//  } else {
//    bst::Node<T> *temp = root_;

//    while (temp) {
//      if (*new_item == *temp) { //dereference the node pointers as a node
//        temp->count += count;
//        delete new_item;
//        return;
//      }

//      if (*new_item < *temp) { // if the item to be inserted is less than the current item
//        if (temp->left) // if temp left is not null, keep traversing
//          temp = temp->left;
//        else {
//          temp->left = new_item;
//          return;
//        }
//      } else { // the item to be inserted is greater than the current item
//        if (temp->right) // if temp right is not null, keep traversing
//          temp = temp->right;
//        else {
//          temp->right = new_item;
//          return;
//        }
//      }
//    }
//  }
//}

/**
 * @brief operator << This function utilizes the Insert functionality of the BinaryTree class
 * @param data
 * @return
 * @modified 2019-05-18
 */
template <typename T>
bst::BinaryTree<T>& bst::BinaryTree<T>::operator<<(const T & data) {
  root_ = Insert(root_, data, 1);
  return *this;
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
unsigned int bst::BinaryTree<T>::data_count(Node<T>* root) const {
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
unsigned int bst::BinaryTree<T>::node_count(Node<T>* root) const {
  if (root == nullptr)
    return 0;
  else
    return (1 + node_count(root->left) + node_count(root->right));
}

/**
 * @brief This function prints a given tree depending on the method passed
 * @param root
 * @param method
 * @modified 2019-05-19
 */
template <typename T>
void bst::BinaryTree<T>::PrintTree(std::ostream &out, Node<T>* root) const {

  if (root) {
    if (traversal() == bst::BST_TRAVERSAL::PRE_ORDER)
      out << root->data << '[' << root->count << ']' << " height: " << height(root) << std::endl;
    PrintTree(out, root->left);
    if (traversal() == bst::BST_TRAVERSAL::IN_ORDER)
      out << root->data << '[' << root->count << ']' << " height: " << height(root)<< std::endl;
    PrintTree(out, root->right);
    if (traversal() == bst::BST_TRAVERSAL::POST_ORDER)
      out << root->data << '[' << root->count << ']' << " height: " << height(root) << std::endl;
  }

}

template <typename T>
/**
 * @brief This function will find a given data in the BST as well as the parent and a lessthan comparator. This function is adapted from
 *         Paul Wilkinson's CS008 implementation
 * @param data
 * @return
 * @modified 2019-05-18
 */
bst::Node<T>* bst::BinaryTree<T>::Find(const T& data, Node<T> *root, Node<T>* &parent, bool &less_than) const {

  parent = root;
  less_than = true;
  bool cont = true;

  while (root && cont) {
    if(data == root->data) {
      less_than = (root == parent->left);
      cont = false;
    } else if (data < root->data) {
      parent = root;
      root = root->left;
    } else if (data > root->data) {
      parent = root;
      root = root->right;
    }
  }
  return root; // returns null if not found
}

/**
 * @brief Delete This function deletes N count occurences from the Binary Tree. Adapted from Paul Wilkinson's CS008 lectures.
 * @param data
 * @param count
 * @modified 2019-05-18
 */
template <typename T>
bool bst::BinaryTree<T>::Delete(const T &data, const unsigned int &count) {
  bool less_than;
  Node<T> *parent = nullptr,
            *child = Find(data, root_, parent, less_than);

  if (child) { // if an item was found..
    if ((child->count -= count) < 1) {
      if (less_than)
        DeleteLeftChild(child, parent);
      else
        DeleteRightChild(child, parent);
    }
    return true;
  } else {
    std::cout << "No item to delete";
    return false;
  }
}

/**
 * @brief bst::BinaryTree<T>::Insert
 * @param root
 * @param data
 * @return
 */
template <typename T>
bst::Node<T>* bst::BinaryTree<T>::Insert(Node<T>* root, const T &data, const unsigned int &count) {
  if (root == nullptr) {
    root = new Node<T>(data, count);
    return root;
  } else if (data < root->data) {
    root->left = Insert(root->left, data, count);
    if ((Node<T>::Height(root->left) - Node<T>::Height(root->right)) == 2) {
      if (data < root->left->data)
        root = RotateLeft(root);
      else
        root = RotateLeftRight(root);
    }
  } else if (data > root->data) {
    root->right = Insert(root->right, data, count);
    if ((Node<T>::Height(root->right) - Node<T>::Height(root->left)) == 2) {
      if (data < root->right->data)
        root = RotateRight(root);
      else
        root = RotateRightLeft(root);
    }
  } else if (data == root->data) {
    root->count += count;
  }
  root->height = std::max (Node<T>::Height(root->left), Node<T>::Height(root->right)) + 1;
  return root;
}

template <typename S>
std::ostream& operator<<(std::ostream& out, const bst::BinaryTree<S> &other) {
//  other.PrintTree(out, other.root_);
  other.PrintTreeDepth(out, other.root_, 0);
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

/**
 * @brief FindSmallest This will return the smallest node for a given root
 * @param root
 * @return
 * @modified 2019-05-18
 */
template <typename T>
bst::Node<T>* bst::BinaryTree<T>::FindSmallest(Node<T>* root) const {
  for ( ; root->left != nullptr; root = root->left);
  return root;
}

/**
 * @brief This function has been adapted from Paul Wilkinson's CS008 lectures.
 * @param child
 * @param parent
 * @modified 2019-05-18
 */
template <typename T>
void bst::BinaryTree<T>::DeleteLeftChild(Node<T>* &child, Node<T>* &parent) {
  if (child->right) {  // if the child to be deleted has a right child, we need to relink it
    parent->left = child->right;
    FindSmallest(child->right)->left = child->left;
  } else  // if child has no right child, then we proceed to replace the node to be deleted with its left child
    parent->left = child->left;
  delete child;
}

/**
 * @brief This function has been adapted from Paul Wilkinson's CS008 lectures.
 * @param child
 * @param parent
 * @modified 2019-05-18
 */
template <typename T>
void bst::BinaryTree<T>::DeleteRightChild(Node<T>* &child, Node<T>* &parent) {
  if (parent == root_) { // special case: when deleting the root's right child
    if (root_->right) {
      root_ = root_->right;
      FindSmallest(root_)->left = parent->left;
    } else {
      root_ = root_->left;
    }
    delete parent;

  } else {
    if (child->right) {
      parent->right = child->right;
      FindSmallest(child->right)->left = child->left;
      }// if child has a right, we need to relink
    else
      parent->right = child->left;
    delete child;
  }
}

/**
 * @brief This function will rebalance a given tree with a series of rotations.
 * @modified 2019-05-18
 */
template <typename T>
bst::Node<T>* bst::BinaryTree<T>::Rebalance(Node <T>* root) {

//  if (root->balance_factor() > 1) {
//    if (root->left->balance_factor() > 0)
//      root = RotateRight(root);
//  } else if (root->balance_factor() < -1) {
//    root =
//  }

  return root;
}

/**
 * @brief
 * @param root
 * @return
 * @modified 2019-05-19
 */

/** Example, where x is the root
 *        W                  X
 *      /  \               /  \
 *     A    X            W    C
 *         / \          / \
 *        B   C       A   B
 *
 */
template <typename T>
bst::Node<T>* bst::BinaryTree<T>::RotateRight(Node<T> *root) { // RR case
  Node<T> * temp = root->right;
  root->right = temp->left;
  temp->left = root;
  root->height = std::max(Node<T>::Height(root->right), Node<T>::Height(root->left)) + 1;
  temp->height = std::max(Node<T>::Height(temp->right), root->height) + 1;
  return temp;
}

/**
 * @brief
 * @param root
 * @return
 * @modified 2019-05-19
 */
/** Where X is the root
 *        X                W
 *       / \              / \
 *     W   C            A   X
 *    / \                   / \
 *   A  B                  B  C
 */

template <typename T>
bst::Node<T>* bst::BinaryTree<T>::RotateLeft(Node<T> *root) { // LL case
  Node<T> *temp = root->left; // set w to temp
  root->left = temp->right; // set x's left to B
  temp->right = root; // set W's right to X
  root->height = std::max(Node<T>::Height(root->left), Node<T>::Height(root->right)) + 1;
  temp->height = std::max(Node<T>::Height(temp->left), root->height) + 1;
  return temp;
}


/**
 * @brief
 * @param root
 * @return
 * @modified 2019-05-19
 */
template <typename T>
bst::Node<T>* bst::BinaryTree<T>::RotateLeftRight(Node<T> *root) { // also known as left right case
  root->left = RotateRight(root->left);
  return RotateLeft(root);
}

/**
 * @brief RotateRightLeft
 * @param root
 * @return
 * @modified 2019-05-19
 */
template <typename T>
bst::Node<T>* bst::BinaryTree<T>::RotateRightLeft(Node<T> *root) { // also known as right left case
  root->right = RotateLeft(root->right);
  return RotateRight(root);
}

/**
 * @brief PrintTreeDepth This function prints a given tree with depth
 * @param out
 * @param root
 * @param depth
 * @modified 2019-05-18
 */
template <typename T>
void bst::BinaryTree<T>::PrintTreeDepth(std::ostream &out, Node<T>* root, size_t depth) const {
    out << std::setw(4*depth) << "";
  if (root == nullptr) {
    out << "[Empty]" << std::endl;
  }  else if (root->is_leaf()) {
    out << root->data << " [leaf]" << std::endl;
  } else {
    out << root->data << std::endl;
    PrintTreeDepth(out, root->right, depth+1);
    PrintTreeDepth(out, root->left, depth+1);
  }
}


