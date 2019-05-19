#ifndef EDITOR_H
#define EDITOR_H
#include <iostream>
#include <string>
#include <fstream>

class EditorAssist
{
public:
    EditorAssist();
    virtual ~EditorAssist();
    bool SanitizeString(std::string &s);
    virtual void insertion() = 0;
    virtual void extraction() = 0;

};

#endif // EDITOR_H
