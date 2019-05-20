#include "editorassistbinarytree.h"

EditorAssistBinaryTree::EditorAssistBinaryTree()
{

}

EditorAssistBinaryTree::~EditorAssistBinaryTree()
{

}

void EditorAssistBinaryTree::insertion()
{
    paragraphs = 1;
    bool flag = false;
    std::string word, temp;
    std::stringstream words;
    int line = 1, letter;
    std::cout<<"Input file name:"<<std::endl;
    std::cin>>temp;
    //if file does not contain.txt add it
    if(temp.find(".txt") == std::string::npos)
        temp += ".txt";
    std::ifstream myfile(temp);
    clock_t begin = clock();
    while(!myfile.eof())
    {
        getline(myfile, temp);
        words.str(temp);
        if(temp.empty())
            flag = true;
        else
        {
            if(flag)
                ++paragraphs;
            flag = false;
            while(words >> word)
            {
                //ascii for a = 97 and 97-97 is for index 0
                if(SanitizeString(word)) //optimize sanitize?
                {
                    letter = word[0] - 65;
                    orchard_[letter].Insert(orchard_[letter].root(),word,paragraphs,line);
                    //orchard_[letter].insertData(word,paragraphs,line);
                }
            }
            words.clear();
        }
        ++line;
    }
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    myfile.close();
}

void EditorAssistBinaryTree::extraction()
{
    bool first = true;
    std::ofstream myfile ("test.txt");
    clock_t begin = clock();
    std::string s;
    std::vector<bst::Node<std::string>*> wordData;
    std::vector<int> letterCounts(26);
   // std::priority_queue<bst::Node<std::string>, std::vector<bst::Node<std::string>>, CompareNodes> mypq;
    bst::Node<std::string> temp;
    char c = 'A';
    int parag, line;
    int wordCount = 0, total = 0, letterCount = 0, indexTrack = 0;
    for(int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {
            ++letterCount;
            ++total;
          // Rafa implement
          //  wordData.pushback(orchard_[i].ExtractSmallest())
         }
        letterCounts[i] = letterCount;
        letterCount = 0;
    }
//    //put this in a separate function
    std::cout<<"Words: "<<total<<std::endl;
    std::cout<<"Paragraphs: "<<paragraphs<<std::endl;
    std::cout<<"Reading level: "<<"TODO"<<std::endl; //create readingLevel();
    std::cout<<"Top 10 words: "<<std::endl;
//    for(int w = 0; w < 10; ++w)
//    {
//        if(!mypq.empty())
//        {
//            std::cout<<mypq.top()<<std::endl;
//            mypq.pop();
//        }
//    }
    for(int w = 0; w < 26; ++w)
    {
        std::cout<<"Number of words that start with "<<c++;
        if(!letterCounts.empty())
            std::cout<<": "<<letterCounts[w]<<std::endl;
    }
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    myfile.close();
    std::cout<<"Press y when you are ready to continue";
    std::cin>>s;
    for(int w = 0; w < wordData.size(); ++w)
    {
        std::cout<<*wordData[w]<<":";
        for(int r = 0; r < wordData[w]->paragraph.size(); ++r)
        {
            std::cout<<"["<<wordData[w]->paragraph[r]<<","<<wordData[w]->line[r]<<"]";
        }
        std::cout<<std::endl;
    }
}
