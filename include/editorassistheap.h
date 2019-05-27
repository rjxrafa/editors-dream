//@author Ara Mico Segismundo and Rafael Betita
#ifndef EDITORASSISTHEAP_H
#define EDITORASSISTHEAP_H
#include "editor.h"
#include "heap.h"
#include "string.h"
#include "node.h"
#include <ctime>
#include <vector>
#include <queue>
#include <cstdarg>

/**
 * @brief The EditorAssistHeap class
 * class that uses heap to process documents
 */
class EditorAssistHeap: public EditorAssist
{
public:
    EditorAssistHeap();
    ~EditorAssistHeap();

    void insertion();
    void extraction();
    void extractLetter(int &&count, ...);

private:
  //  std::vector<bst::Node<std::string>*> wordData;
    myHeap<std::string> orchard_[26];
//    int sentences_;
};

//Helper to tell the priority how to compare nodes by its count so it does not conflict
//with the current word comparison, this uses its count
//struct CompareNodes {
//    bool operator()(const bst::Node<std::string>& x, const bst::Node<std::string>& y)
//    {
//        return x.count < y.count;
//    }
//};

#endif // EDITORASSISTHEAP_H
