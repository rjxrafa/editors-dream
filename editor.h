#ifndef EDITOR_H
#define EDITOR_H
#include "node.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>

enum EDITOR_ERRORS {INVALID_INPUT,OPTION_USED};

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
    void Display();

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
    std::vector<int> uniqueLetterCounts_;
    std::vector<int> letterCounts_;
    std::vector<bst::Node<std::string>*> wordData_;
    std::vector<bst::Node<std::string>> topWords_;
    std::ifstream in;
    std::ofstream out;
    int sentence_, total_, paragraphs_, syllables_;
    double seconds_;
    clock_t begin_;
    int syllableCounter(const std::string &word);
    double fleschKincaid(int words, int sentences, int syllables);
    void Output();
    void FileOutput(std::ostream &out, FileFlags &my_flags);
    bool getInput(const std::string &s);
};

#endif // EDITOR_H
