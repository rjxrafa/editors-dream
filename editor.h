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
    void menu();
    struct FileFlag
    {
        bool wordTota,pars,readLevel,topTen,letterC,runTime,wordIndex;
    };

protected:

    std::vector<bst::Node<std::string>> wordData_;
    std::vector<std::string> topWords;
    std::ifstream in;
    std::ofstream out;
    int sentence_;
    int syllables_;
    int syllableCounter(const std::string &word);
    double fleschKincaid(int words, int sentences, int syllables);
};

struct CompareNodes {
    bool operator()(const bst::Node<std::string>& x, const bst::Node<std::string>& y)
    {
        return x.count < y.count;
    }
};

#endif // EDITOR_H
