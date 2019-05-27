//@author Ara Mico Segismundo and Rafael Betita
#ifndef EDITORASSISTBINARYTREE_H
#define EDITORASSISTBINARYTREE_H
#include <iostream>
#include <ctime>
#include <queue>
#include "editor.h"
#include "binarytree.h"
#include <cstdarg>

/**
 * @brief The class that uses binary tree to process documents
 */
class EditorAssistBinaryTree : public EditorAssist
{
public:
    EditorAssistBinaryTree();
    ~EditorAssistBinaryTree();

    void insertion();
    void extraction();
    void extractLetter(int &&count, ...);

 private:
  bst::BinaryTree<std::string> orchard_[26];
};

#endif // EDITORASSISTBINARYTREE_H
