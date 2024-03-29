#include "../include/editor.h"

/**
 * @brief EditorAssist::EditorAssist
 * letter counts, unique counts
 * sentences, syllables, total, paragraphs
 * and seconds
 */
EditorAssist::EditorAssist()
{
    uniqueLetterCounts_.resize(26);
    letterCounts_.resize(26);
    sentence_ = 1;
    syllables_ = 0;
    total_ = 0;
    paragraphs_ = 1;
    seconds_ = 0;
}

EditorAssist::~EditorAssist()
{
    uniqueLetterCounts_.clear();
    letterCounts_.clear();
    for(unsigned int i = 0; i < wordData_.size();++i)
    {
        delete wordData_.back();
        wordData_.pop_back();
    }
    topWords_.clear();
    sentence_ = 0;
    syllables_ = 0;
    total_ = 0;
    paragraphs_ = 0;
    seconds_ = 0;
}

/**
 * @brief EditorAssist::SanitizeString
 * @param s
 * @return
 * Sanitizes string removes anything from the left and right
 * that isnt a letter also counts '.' as sentences
 */
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
/**
 * @brief EditorAssist::syllableCounter
 * @param word
 * @return
 * Counts the syllables by using vowels and subtracting silent vowels
 */
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
    if(syllables < 1)
        syllables +=1;
    return syllables;
}

/**
 * @brief EditorAssist::FleschKincaid
 * @param words
 * @param sentences
 * @param syllables
 * @return
 * Uses the FleschKincaid math to calculate grade level
 */
double EditorAssist::FleschKincaid(int words, int sentences, int syllables) const
{
    double temp = 0.39 * ((double)words/sentences) + 11.8 * ((double)syllables/words) - 15.9;
    if(temp < 0)
        temp = 1;
    return temp;
}
/**
 * @brief EditorAssist::LoadFile
 * @return
 * check for file to load
 */
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

/**
 * @brief EditorAssist::WriteToFile
 * @return
 * check for writing to file
 */
bool EditorAssist::WriteToFile() {

  while (1) {
    std::string user_input, user_input2;
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
        getline(std::cin, user_input2);
        fflush(stdin);

        if (tolower(user_input2[0]) == 'y') {
          out.open(user_input);
          return true;
        } else {
          return false;
        }
      }
      out.open(user_input);
      return true;
    }
  }
}
/**
 * @brief EditorAssist::QtWriteToFile
 * @param fileName
 * different file instructions if writing
 * from qt gui
 */
void EditorAssist::QtWriteToFile(const std::string &fileName)
{
    OutputFlags my_flags;
    my_flags.all= true;
    out.open(fileName);
    Output(out, my_flags);
    out.close();
}

/**
 * @brief EditorAssist::Menu for the file save
 */
void EditorAssist::Menu()
{
    OutputFlags my_flags;
    my_flags.word_total = my_flags.paragraph_total = my_flags.flesch_level = my_flags.top_ten =
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
              << "["<< ((my_flags.top_ten) ? 'x' : ' ' )<< "]"
              << "(M)ost Used Words\n"
              << "["<< ((my_flags.runtime) ? 'x' : ' ' )<< "]"
              << "(R)untime\n"
              << "["<< ((my_flags.word_index) ? 'x' : ' ' )<< "]"
              << "(W)ord Info (index)\n"
              << "["<< ((my_flags.all) ? 'x' : ' ' )<< "]"
              << "(A)ll of the above\n\n" << "Press enter to save.\n"
              <<  std::endl;

    std::string user_input;
    getline(std::cin, user_input);
    fflush(stdin);

    if (user_input.empty())
    {
        Output(out, my_flags);
        out.close();
        return;
    }

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
        std::cout<<"Invalid Input"<<std::endl;
        }
    }
}

/**
 * @brief EditorAssist::Output
 * @param out
 * @param my_flags
 * output for any output stream
 */
void EditorAssist::Output(std::ostream &out, OutputFlags &my_flags) {
    if (&out == &std::cout || my_flags.all) {
          my_flags.flesch_level = true;
          my_flags.word_total = true;
          my_flags.paragraph_total = true;
          my_flags.top_ten = true;
          my_flags.letter_count = true;
          my_flags.runtime = true;
          my_flags.word_index = true;
        }

    if (my_flags.word_total)
        out<<"Words: "<<total_<<std::endl<<std::endl;
    if(my_flags.paragraph_total)
        out<<"Paragraphs: "<<paragraphs_<<std::endl<<std::endl;
    if(my_flags.flesch_level)
        out<<"Reading level: "<<"Grade "<< round(FleschKincaid(total_,sentence_,syllables_))<<std::endl
             <<std::endl;
    if(my_flags.top_ten)
    {
        out<<"Top 10 words: "<<std::endl;
        for(unsigned int w = 0; w < topWords_.size(); ++w)
        {
            if(!topWords_[w].empty())
            {
                out<<topWords_[w]<<std::endl;
            }
        }
        out<<std::endl;
    }
    if(my_flags.letter_count)
    {
        char c='A';
        for(unsigned int w = 0; w < 26; ++w)
        {
            if(letterCounts_[w] != 0)
            {
                out<<c
                  <<": "<<letterCounts_[w]<< " (" <<uniqueLetterCounts_[w]<< ')' <<std::endl;
            }
            ++c;
        }
        out<<std::endl;
    }
    if(my_flags.runtime)
        out<<"Runtime: "<<seconds_<<" seconds"<<std::endl<<std::endl;
    if(my_flags.word_index)
    {
       if(&out != &std::cout || (&out == &std::cout && getInput("Would you like to see where the words are located?")))
        for (unsigned int i = 0, total = wordData_.size(); i < total; ++i)
        {
            out << *wordData_[i] << ":";
            for (unsigned int s = 0; s < wordData_[i]->paragraph.size(); ++s)
            {
                out << " [" << wordData_[i]->paragraph[s] << ',' << wordData_[i]->line[s]<<']';
            }
            out << std::endl;
        }
    }
}

/**
 * @brief EditorAssist::Run
 * @param fileWrite
 * instructions on function call order for program
 */
void EditorAssist::Run(bool fileWrite)
{
    OutputFlags cout_flags;
    insertion();
    extraction();
    Output(std::cout,cout_flags);
    if(fileWrite)
    {
        if(WriteToFile())
        {
            Menu();
        }
    }
}

/**
 * @brief EditorAssist::getInput
 * @param s
 * @return
 * input check for y or anything else
 */
bool EditorAssist::getInput(const std::string &s)
{
    std::string user_input;
    std::cout<<s<<std::endl;
    getline(std::cin, user_input);
    fflush(stdin);
    if(user_input.empty())
        return false;
    return tolower(user_input[0]) == 'y';
}
/**
 * @brief EditorAssist::QtLoadFile
 * @param qs
 * Instructions on how to load file
 * if using qt Gui
 */
bool EditorAssist::QtLoadFile(QString qs)
{
  std::string filename = qs.toStdString();

  in.close(); // closes if already open
  in.open(filename);
  in.clear();

  return in.good();
}

/**
 * @brief EditorAssist::QtOutput
 * Output to qt textDisplay
 */
QString EditorAssist::QtOutput() const
{
    QString message =  "";

    message += QString("Words: %1 \n\n").arg(total_);

    message += QString("Paragraphs:  %1 \n\n").arg(paragraphs_);

    message += QString("Reading Level: Grade %1 \n\n").arg(round(FleschKincaid(total_,sentence_,syllables_)));

    message += QString("Top 10 words: \n");

    for(unsigned int w = 0; w < topWords_.size(); ++w)
    {
        if(!topWords_[w].empty())
        {
            std::string temp = topWords_[w].data;
            message += QString("%1 (%2)\n").arg(QString::fromStdString(temp)).arg(topWords_[w].count);
        }
    }
    message += QString("\n");

    message += QString("Letter: count (unique)\n");
    char c = 'A';
    for(unsigned int w = 0; w < 26; ++w)
    {
        if(letterCounts_[w] != 0)
        {
            message += QString("%1: %2 (%3)\n").arg(QChar(c)).arg(letterCounts_[w]).arg(uniqueLetterCounts_[w]);
        }
        ++c;
    }
    message += QString("\n");

    message += QString("Runtime: %1 seconds").arg(seconds_);

    return message;
}
/**
 * @brief EditorAssist::QtTabWords
 * @param letter
 * The words to display to on the letter tabs
 */
QString EditorAssist::QtTabWords(char letter) const
{
    QString message = "";

    for (unsigned int i = 0, total = wordData_.size(); i < total; ++i)
    {
        if(wordData_[i]->data[0] == letter)
            message += QString("%1(%2):").arg(QString::fromStdString(wordData_[i]->data)).arg(wordData_[i]->count);
        for (unsigned int s = 0; s < wordData_[i]->paragraph.size(); ++s)
        {
            if(wordData_[i]->data[0] == letter)
                message += QString("[%1,%2]").arg(wordData_[i]->paragraph[s]).arg(wordData_[i]->line[s]);
        }
        if(wordData_[i]->data[0] == letter)
        message += ("\n");
    }
    if(message == "")
        message = "No words with letter found";
    return message;
}

//Seconds getter
double EditorAssist::getSeconds() const
{
    return seconds_;
}
//Seconds setter
void EditorAssist::setSeconds(double d)
{
    seconds_ = d;
}

