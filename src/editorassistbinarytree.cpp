#include "../include/editorassistbinarytree.h"

EditorAssistBinaryTree::EditorAssistBinaryTree() = default;

EditorAssistBinaryTree::~EditorAssistBinaryTree() = default;

/**
 * @brief EditorAssistBinaryTree::insertion
 * information insertion to the binary tree
 */
void EditorAssistBinaryTree::insertion()
{
    std::cout<<"Binary Tree Start:"<<std::endl;
    bool flag = false;
    std::string word, temp;
    std::stringstream words;
    int line = 1, letter;

    while (!LoadFile());
    begin_ = clock();
    while(!in.eof())
    {
        getline(in, temp);
        words.str(temp);
        if(temp.empty())
            flag = true;
        else
        {
            if(flag)
                ++paragraphs_;
            flag = false;
            while(words >> word)
            {

                //ascii for A = 65 and 65 is for index 0
                if(SanitizeString(word))
                {
                    letter = word[0] - 65;
                    syllables_ += syllableCounter(word);
                    orchard_[letter].InsertData(word, paragraphs_, line);
                }
            }
            words.clear();
        }
        ++line;
    }
    in.close();
    std::cout << orchard_[25];
}

/**
 * @brief EditorAssistBinaryTree::extraction
 * information extractrion from the binary tree
 */
void EditorAssistBinaryTree::extraction()
{
    std::string s;
    std::priority_queue<bst::Node<std::string>, std::vector<bst::Node<std::string>>, CompareNodes> mypq;
    int letterCount = 0, uniqueletterCount = 0;
    unsigned int indexTrack = 0;
    for(unsigned int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {
             bst::Node<std::string> *temp = new bst::Node<std::string>(orchard_[i].ExtractSmallest());
             wordData_.push_back(temp);
             mypq.push(*temp);
             letterCount+= wordData_[indexTrack]->count;
             ++uniqueletterCount;
             total_ += wordData_[indexTrack++]->count;
         }
        uniqueLetterCounts_[i] = uniqueletterCount;
        letterCounts_[i] = letterCount;
        uniqueletterCount = 0;
        letterCount = 0;
    }
    seconds_ = (double)(clock()-begin_)/CLOCKS_PER_SEC;
    for(int w = 0; w < 10; ++w)
    {
        if(!mypq.empty())
        {
            topWords_.push_back(mypq.top());
            mypq.pop();
        }
    }
}

void EditorAssistBinaryTree::extractLetter(char &&ch) {
  std::ifstream in;
  std::string temp;
  int mych = tolower(ch) - 97;
  ch = tolower(ch);
  in.open("war_and_peace.txt");
//
  while (in >> temp) {
    if (tolower(temp[0]) == ch)
      orchard_[mych].Insert(temp, 0, 0);
  }
  in.close();

//  std::cout << orchard_[mych];
  std::cout << char(ch) << " done\n";
}