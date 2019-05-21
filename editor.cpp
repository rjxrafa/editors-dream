#include "editor.h"

EditorAssist::EditorAssist()
{
    sentence = 0;
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
    {
        s.erase(0,1);
    }
    if(s.empty())
        return false;
    //check back
    while(!isalpha(s[s.size()-1]))
    {
        if(s[s.size()-1] == '.' || s[s.size()-1] == '!' || s[s.size()-1] == '?')
            sentence += 1;
        s.pop_back();
    }
    //if string empty it was not a word
    if(s.empty())
        return false;
    //lower if it is a word
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    s[0] = toupper(s[0]);
   // s[0] = tolower(s[0]);
    //else true
    return true;
}

int EditorAssist::syllableCounter(const std::string &word)
{
    //vowels are aeiou
    //if vowels next to each other -1
    //e at the end is usually silent
    //if no vowels 1 syllable
    int syllables = 0;
    bool wasVowel = false;
    for(unsigned int i = 0; i < word.size(); ++i)
    {
        if(tolower(word[i]) == 'a' || tolower(word[i]) == 'e' || tolower(word[i]) == 'i'
                                   || tolower(word[i]) == 'o' || tolower(word[i]) == 'u')
        {
            if(wasVowel)
                syllables -=1;
            syllables += 1;
            wasVowel = true;
        }
        else
            wasVowel = false;
    }
    if(tolower(word[word.size()-1]) == 'e')
        syllables -= 1;
    if(!syllables)
        syllables +=1;
    return syllables;
}

double EditorAssist::fleschKincaid(int words, int sentences, int syllables)
{

}
