#ifndef EDITORASSISTBINARYTREE_H
#define EDITORASSISTBINARYTREE_H
#include <iostream>
#include <ctime>
#include "editor.h"
#include "binarytree.h"
#include "vector"

class EditorAssistBinaryTree : public EditorAssist
{
public:
    EditorAssistBinaryTree();
    ~EditorAssistBinaryTree();

    void insertion();
    void extraction();
private:
    bst::BinaryTree<std::string> orchard_[26];
    int paragraphs;
};

#endif // EDITORASSISTBINARYTREE_H
