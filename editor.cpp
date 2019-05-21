#include "editor.h"

EditorAssist::EditorAssist()
{
    sentence_ = 1;
    syllables_ = 0;
}

EditorAssist::~EditorAssist()
{
    sentence_ = 0;
    syllables_ = 0;
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
            sentence_ += 1;
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
    double temp = 0.39 * ((double)words/sentences) + 11.8 * ((double)syllables/words) - 15.9;
    if(temp < 0)
        temp = 1;
    return temp;
}

bool EditorAssist::LoadFile() {

  std::string filename;

  std::cout << "Filename: ";
  getline(std::cin, filename);

  in.close(); // closes if already open
  in.open(filename);

  if (!in.good())
    std::cout << "File not found! Try again. " << std::endl;

  return in.good();
}

bool EditorAssist::WriteToFile() {

  while (1) {
    std::string user_input;
    std::cout << "Do you want to save this file? Type 'Y' for yes: " << std::endl;
    getline(std::cin, user_input);
    fflush(stdin);

    if (tolower(user_input[0]) != 'y')
      return false;
    else {
      std::cout << "Enter filename: " << std::endl;
      getline(std::cin, user_input);
      fflush(stdin);

      // Checks for existing file
      std::ifstream temp;
      temp.open(user_input);
      temp.close();

      if (!temp.fail()) {
        std::cout << "File already exists! Do you want to overwrite it?" << std::endl;
        getline(std::cin, user_input);
        fflush(stdin);

        if (tolower(user_input[0]) == 'y') {
          out.open(user_input);
          return true;
        } else {
          continue;
        }
      }
      return true;
    }
  }
}

