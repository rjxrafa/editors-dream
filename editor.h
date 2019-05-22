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
    std::vector<int> letterCounts;
    std::vector<bst::Node<std::string>*> wordData_;
    std::vector<std::string> topWords_;
    std::ifstream in;
    std::ofstream out;
    int sentence_, total_, paragraphs_, syllables_, seconds_;
    int syllableCounter(const std::string &word);
    double fleschKincaid(int words, int sentences, int syllables);
    void Output(std::ostream &out, FileFlags &my_flags);

};

struct CompareNodes {
    bool operator()(const bst::Node<std::string>& x, const bst::Node<std::string>& y)
    {
        return x.count < y.count;
    }
};

#endif // EDITOR_H
