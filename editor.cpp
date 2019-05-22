#include "editor.h"

EditorAssist::EditorAssist()
{
    uniqueLetterCounts.resize(26);
    letterCounts_.resize(26);
    sentence_ = 1;
    syllables_ = 0;
    total_ = 0;
    paragraphs_ = 1;
    seconds_ = 0;
}

EditorAssist::~EditorAssist()
{
    sentence_ = 0;
    syllables_ = 0;
}

bool EditorAssist::SanitizeString(std::string &s)
{
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

void EditorAssist::Menu()
{
    FileFlags my_flags;
    my_flags.paragraph_total = my_flags.flesch_level = my_flags.top_ten =
    my_flags.letter_count = my_flags.runtime = my_flags.word_index = my_flags.all = false;

    while (1) {
    std::cout << "What would you like to save?\n"
              <<  "[" << ((my_flags.word_total) ? 'x' : ' ' )<< "]"
              << "(T)otal Words\n"
              << "["<< ((my_flags.paragraph_total) ? 'x' : ' ' )<< "]"
              << "(P)aragraph Count\n"
              << "["<< ((my_flags.flesch_level) ? 'x' : ' ' )<< "]"
              << "(F)lesch Reading Grade Level\n"
              << "["<< ((my_flags.letter_count) ? 'x' : ' ' )<< "]"
              << "(L)etter Count\n"
              << "["<< ((my_flags.word_index) ? 'x' : ' ' )<< "]"
              << "(W)ord Info (index)\n"
              << "["<< ((my_flags.top_ten) ? 'x' : ' ' )<< "]"
              << "(M)ost Used Words\n"
              << "["<< ((my_flags.runtime) ? 'x' : ' ' )<< "]"
              << "(R)untime\n"
              << "["<< ((my_flags.all) ? 'x' : ' ' )<< "]"
              << "(A)ll of the above\n\n" << "Press enter to quit.\n"
              <<  std::endl;

    std::string user_input;
    getline(std::cin, user_input);
    fflush(stdin);

    if (user_input.empty())
        return;

    switch(tolower(user_input[0])) {

    case 't':
        my_flags.word_total = !my_flags.word_total;
        break;
    case 'p':
        my_flags.paragraph_total = !my_flags.paragraph_total;
        break;
    case 'f':
        my_flags.flesch_level = !my_flags.flesch_level;
        break;
    case 'm':
        my_flags.top_ten = !my_flags.top_ten;
        break;
    case 'l':
        my_flags.letter_count = !my_flags.letter_count;
        break;
    case 'r':
        my_flags.runtime = !my_flags.runtime;
        break;
    case 'w':
        my_flags.word_index = !my_flags.word_index;
        break;
    case 'a':
        my_flags.all = !my_flags.all;
        break;
     default:
        std::cout << "Invalid input!\n";
        }
    Output(out, my_flags);
    }

}


//
//   Output(out,s);
//}


void EditorAssist::Output(std::ostream &out, FileFlags &my_flags) {
    if (my_flags.all)
        out << "Stuff here\n" ;
    if (my_flags.word_total)
        out<<"Words: "<<total_<<std::endl;
    if(my_flags.paragraph_total)
        out<<"Paragraphs: "<<paragraphs_<<std::endl;
    if(my_flags.flesch_level)
        out<<"Reading level: "<<"Grade "<<round(fleschKincaid(total_,sentence_,syllables_))<<std::endl;
    if(my_flags.top_ten)
    {
        out<<"Top 10 words: "<<std::endl;
        for(int w = 0; w < 10; ++w)
        {
            if(!topWords_[w].empty())
            {
                std::cout<<topWords_[w]<<std::endl;
            }
        }
    }
    if(my_flags.letter_count)
    {
        char c='A';
        for(int w = 0; w < 26; ++w)
        {
            out<<"Number of words that start with "<<c++;
            if(!letterCounts_.empty())
                out<<": "<<letterCounts_[w]<<std::endl;
        }
    }
    if(my_flags.runtime)
        std::cout<<"Runtime: "<<seconds_<<" seconds"<<std::endl<<std::endl;
    if(my_flags.word_index)
    {
        for (int i = 0, total = wordData_.size(); i < total; ++i)
        {
            out << *wordData_[i] << ":";
            for (int s = 0, total_ = wordData_[i]->paragraph.size(); s < total_; ++s)
            {
                out << " [" << wordData_[i]->paragraph[s] << ',' << wordData_[i]->line[s]<<']';
            }
            out << std::endl;
        }
    }
}
