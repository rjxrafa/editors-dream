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

//        for(unsigned int i = 0; i < s.size(); ++i)
//        {
//            switch(tolower(s[i]))
//            {
//            case 't': wordTotal = true;
//                break;
//            case 'p': pars = true;
//                break;
//            case '3': readLevel = true;
//                break;
//            case '4': topTen = true;
//                break;
//            case '5': letterC = true;
//                break;
//            case 'r': runTime = true;
//                break;
//            case '7': wordInfo = true;
//                break;
//            default : return
//            }
    };

protected:
    std::vector<bst::Node<std::string>> wordData_;
    std::ifstream in;
    std::ofstream out;
    int sentence_;
    int syllables_;
    int syllableCounter(const std::string &word);
    double fleschKincaid(int words, int sentences, int syllables);
};

#endif // EDITOR_H
