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
    void Menu();

    struct FileFlags
    {
        bool word_total,
             paragraph_total,
             flesch_level,
             top_ten,
             letter_count,
             runtime,
             word_index,
             all;
    };

protected:
    std::ifstream in;
    std::ofstream out;
    int sentence_;
    int syllables_;
    int syllableCounter(const std::string &word);
    double fleschKincaid(int words, int sentences, int syllables);
    void Output(std::ostream &out, FileFlags &my_flags);

};

#endif // EDITOR_H
