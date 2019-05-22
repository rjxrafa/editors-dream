#include "editorassistheap.h"

EditorAssistHeap::EditorAssistHeap()
{

}

EditorAssistHeap::~EditorAssistHeap()
{

}

//TODO:Create with string parameter for auto run
/**
 * @brief EditorAssistHeap::insertion
 * information insertion to the heap
 */
void EditorAssistHeap::insertion()
{
    std::cout<<"Heap Start:"<<std::endl;
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
                //ascii for a = 97 and 97-97 is for index 0
                if(SanitizeString(word)) //optimize sanitize?
                {
                    letter = word[0] - 65;
                    syllables_ += syllableCounter(word);
                    orchard_[letter].insertData(word,paragraphs_,line);
                }
            }
            words.clear();
        }
        ++line;
    }
    in.close();
}

/**
 * @brief EditorAssistHeap::extraction
 * information extraction from the heap
 */
void EditorAssistHeap::extraction()
{
    bool first = true;
    std::string s, previousWord;
    std::priority_queue<bst::Node<std::string>, std::vector<bst::Node<std::string>>, CompareNodes> mypq;
    int parag, line, letterCount = 0, uniqueletterCount = 0;
    unsigned int wordCount = 0, indexTrack = 0;
    for(unsigned int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {

            ++letterCount;
            ++total_;
            previousWord = s;
            orchard_[i].extractData(s,parag,line);
            if(first)
            {
                ++uniqueletterCount;
                previousWord = s;
                first=false;
                bst::Node<std::string> *temp2 = new bst::Node<std::string>(s,0);
                wordData_.push_back(temp2);
            }
            if(previousWord == s)
            {
                ++wordCount;
                wordData_[indexTrack]->count += 1;
                wordData_[indexTrack]->paragraph.push_back(parag);
                wordData_[indexTrack]->line.push_back(line);
            }
            else
            {
                ++uniqueletterCount;
                bst::Node<std::string> *temp = new bst::Node<std::string>(previousWord, wordCount);
                mypq.push(*temp);
                wordCount = 1;
                ++indexTrack;
                bst::Node<std::string> *temp2 = new bst::Node<std::string>(s);
                wordData_.push_back(temp2);
                wordData_[indexTrack]->paragraph.push_back(parag);
                wordData_[indexTrack]->line.push_back(line);
            }
        }
        if(i == 25 && orchard_[i].empty())
        {
            bst::Node<std::string> *temp = new bst::Node<std::string>(s, wordCount);
            //std::set might be faster TODO:replace and see time
            mypq.push(*temp);
        }
        letterCounts_[i] = letterCount;
        uniqueLetterCounts_[i] = uniqueletterCount;
        letterCount = 0;
        uniqueletterCount = 0;
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
