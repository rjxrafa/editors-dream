#ifndef EDITORASSISTBINARYTREE_H
#define EDITORASSISTBINARYTREE_H
#include <iostream>
#include <ctime>
#include <queue>
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
    std::vector<bst::Node<std::string>*> wordData;
    bst::BinaryTree<std::string> orchard_[26];
};

//struct CompareNodes {
//    bool operator()(const bst::Node<std::string>& x, const bst::Node<std::string>& y)
//    {
//        return x.count < y.count;
//    }
//};

#endif // EDITORASSISTBINARYTREE_H
