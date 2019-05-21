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
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    s[0] = toupper(s[0]);
   // s[0] = tolower(s[0]);
    //else true
    return true;
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

void EditorAssist::WriteToFile() {

  std::string user_input, filename;

  std::cout << "Do you want to save this file? Type 'Y' for yes" << std::endl;

  getline(std::cin, user_input);

  if (tolower(user_input[0]) == 'y') {
    std::cout << "Enter filename: " << std::endl;

    getline(std::cin, filename);

    std::ifstream temp;
    temp.open(filename);
    temp.close();

    if (in.fail()) {
      out.open(user_input);
    } else {
      std::cout << "File already exists! Do you want to overwrite it?" << std::endl;
      getline(std::cin, user_input);

      if (tolower(user_input[0]) == 'y') {
        out.open(user_input);
      } else {
        std::cout << "File not saved." << std::endl;
        return;
      }
    }
  }
}
