#ifndef EDITOR_H
#define EDITOR_H
#include "node.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

class EditorAssist
{
public:
    EditorAssist();
    virtual ~EditorAssist();
    bool SanitizeString(std::string &s);
    virtual void insertion() = 0;
    virtual void extraction() = 0;
    bool LoadFile();
    bool WriteToFile();

protected:
    std::ifstream in;
    std::ofstream out;
    int sentence_;
    int syllables_;
    int syllableCounter(const std::string &word);
    double fleschKincaid(int words, int sentences, int syllables);
};

#endif // EDITOR_H
