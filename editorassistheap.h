#ifndef EDITORASSISTHEAP_H
#define EDITORASSISTHEAP_H
#include "editor.h"
#include "heap.h"
#include "string.h"
#include <ctime>

class EditorAssistHeap: public EditorAssist
{
public:
    EditorAssistHeap();
    ~EditorAssistHeap();

    void insertion();
    void extraction();


private:
    myHeap<std::string> orchard_[26];
};

#endif // EDITORASSISTHEAP_H
