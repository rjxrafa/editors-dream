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

    while (!LoadFile());
    clock_t begin = clock();
    while(!in.eof())
    {
        getline(in, temp);
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
//                    std::cout << word << std::endl;
                    letter = word[0] - 65;
                    orchard_[letter].InsertData(word, paragraphs, line);
                }
            }
            words.clear();
        }
        ++line;
    }
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"binaryTree"<<std::endl;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    in.close();
}

void EditorAssistBinaryTree::extraction()
{
    bool first = true;
    std::ofstream myfile ("test.txt");
    clock_t begin = clock();
    std::string s;
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
                      // Rafa implement
             wordData.push_back(orchard_[i].ExtractSmallest());
             total += wordData[indexTrack++].count;
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
        std::cout<<"Number of words that start with "<<c++; // todo add count
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
        std::cout<< wordData[w]<<":";
        for(int r = 0; r < wordData[w].paragraph.size(); ++r)
        {
            std::cout<<"["<<wordData[w].paragraph[r]<<","<<wordData[w].line[r]<<"]";
        }
        std::cout<<std::endl;
    }
}
