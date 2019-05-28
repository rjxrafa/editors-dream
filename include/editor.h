/**
 * @author Ara Miro Segismundo & Rafael Betita
 * @modified 2019-0
 */

#ifndef EDITOR_H
#define EDITOR_H
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cmath>
#include <map>
#include "node.h"
#include <QString>

/**
 * @brief The EditorAssist class
 * base class for the binary tree and heap to help editors
 */
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
    void Run(bool fileWrite = true);
    QString QtOutput() const;
    QString QtTabWords(char letter) const;
    void QtWriteToFile(const std::string &fileName);
    bool QtLoadFile(QString qs);
    double getSeconds() const;
    void setSeconds(double d);

protected:
    //Output flags to tell us what we want printed to file
    struct OutputFlags
    {
        OutputFlags() {
            word_total = paragraph_total = flesch_level = top_ten =
            letter_count = runtime = word_index = all = false;
        }
        ~OutputFlags() {
            word_total = paragraph_total = flesch_level = top_ten =
            letter_count = runtime = word_index = all = false;
        }
        bool word_total,
             paragraph_total,
             flesch_level,
             top_ten,
             letter_count,
             runtime,
             word_index,
             all;
    };
    std::vector<int> uniqueLetterCounts_;
    std::vector<int> letterCounts_;
    std::vector<bst::Node<std::string> * > wordData_;
    std::vector<bst::Node<std::string>> topWords_;
    std::ifstream in;
    std::ofstream out;
    int sentence_, total_, paragraphs_, syllables_;
    double seconds_;
    clock_t begin_;
    int syllableCounter(const std::string &word);
    double FleschKincaid(int words, int sentences, int syllables) const;
    void Output(std::ostream &out, OutputFlags &my_flags);
    bool getInput(const std::string &s);
};

#endif // EDITOR_H
