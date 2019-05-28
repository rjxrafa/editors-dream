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
    void timeTest(std::string fileName);

private:
    myHeap<std::string> orchard_[26];
};

#endif // EDITORASSISTHEAP_H
