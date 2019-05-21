#ifndef EDITOR_H
#define EDITOR_H
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
    void WriteToFile();

protected:
  std::ifstream in;
  std::ofstream out;


};

#endif // EDITOR_H
