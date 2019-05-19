#include "editor.h"

EditorAssist::EditorAssist()
{

}

EditorAssist::~EditorAssist()
{

}

bool EditorAssist::SanitizeString(std::string &s)
{
//    std::cout<<"in sanitize"<<std::endl;
//    std::cout<<"word to sanitize: "<<s<<std::endl;
    //check front
    while(!s.empty()&&!isalpha(s[0]))
        s.erase(0,1);
    if(s.empty())
        return false;
    //check back
    while(!isalpha(s[s.size()-1]))
        s.pop_back();
    //if string empty it was not a word
    if(s.empty())
        return false;
    //lower if it is a word
    s[0] = tolower(s[0]);
    //else true
    return true;
}
