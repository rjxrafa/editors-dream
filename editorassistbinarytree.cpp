#include "editorassistbinarytree.h"

EditorAssistBinaryTree::EditorAssistBinaryTree()
{

}

EditorAssistBinaryTree::~EditorAssistBinaryTree()
{

}

void EditorAssistBinaryTree::insertion()
{
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
                    orchard_[letter].InsertData(word, paragraphs_, line);
                }
            }
            words.clear();
        }
        ++line;
    }
    std::cout<<"binaryTree"<<std::endl;
    in.close();
}

void EditorAssistBinaryTree::extraction()
{
//    std::ofstream myfile ("test.txt");
    std::string s;
    std::priority_queue<bst::Node<std::string>, std::vector<bst::Node<std::string>>, CompareNodes> mypq;
    int letterCount = 0, uniqueletterCount = 0;
    unsigned int indexTrack = 0;
    for(unsigned int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {
                      // Rafa implement
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

//   myfile.close();
//    //put this in a separate function
//    std::cout<<"Words: "<<total_<<std::endl;
//    std::cout<<"Paragraphs: "<<paragraphs_<<std::endl;
//    std::cout<<"Reading level: "<<"Grade "<<round(fleschKincaid(total_,sentence_,syllables_))<<std::endl;  //create readingLevel();
//    std::cout<<"Top 10 words: "<<std::endl;
//    for(int w = 0; w < 10; ++w)
//    {
//        if(!mypq.empty())
//        {
//            topWords_.push_back(mypq.top());
//            mypq.pop();
//        }
//    }
//    for(int w = 0; w < 26; ++w)
//    {
//        std::cout<<"Number of words that start with "<<c++; // todo add count
//        if(!letterCounts_.empty())
//            std::cout<<": "<<letterCounts_[w]<<" Unique: "<<uniqueLetterCounts_[w]<<std::endl;
//    }
//    std::cout<<"Runtime: "<<seconds_<<" seconds"<<std::endl<<std::endl;
//    myfile.close();
//    std::cout<<"Press y when you are ready to continue";
//    std::cin>>s;
//    for(int w = 0; w < wordData.size(); ++w)
//    {
//        std::cout<< *wordData[w]<<":";
//        for(int r = 0; r < wordData[w]->paragraph.size(); ++r)
//        {
//            std::cout<<"["<<wordData[w]->paragraph[r]<<","<<wordData[w]->line[r]<<"]";
//        }
//        std::cout<<std::endl;
//    }
}
