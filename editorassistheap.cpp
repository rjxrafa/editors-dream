#include "editorassistheap.h"

EditorAssistHeap::EditorAssistHeap()
{

}

EditorAssistHeap::~EditorAssistHeap()
{
//    for(int i = 0; i < 26; ++i)
//        orchard_[i].clear();
}

//TODO:File check
void EditorAssistHeap::insertion()
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
                    orchard_[letter].insertData(word,paragraphs,line);
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

void EditorAssistHeap::extraction()
{
    bool first = true;
    std::ofstream myfile ("test.txt");
    clock_t begin = clock();
    std::string s, previousWord;
    std::vector<bst::Node<std::string>*> wordData;
    std::vector<int> letterCounts(26);
    std::priority_queue<bst::Node<std::string>, std::vector<bst::Node<std::string>>, CompareNodes> mypq;
    bst::Node<std::string> temp;
    char c = 'A';
    int parag, line;
    int wordCount = 1, total = 0, letterCount=0, indexTrack=0;
    for(int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {
            ++letterCount;
            ++total;
            previousWord = s;
            orchard_[i].extractData(s,parag,line);
           // std::cout<<s<<std::endl;
           // std::cout<<total<<" Parag:"<<parag<<" "<<"Line: "<<line<<std::endl;
            if(first)
            {
                previousWord = s;
                first=false;
//                bst::Node<std::string> *temp2 = new bst::Node<std::string>(s);
//                wordData.push_back(temp2);
            }
            if(previousWord == s)
            {
                ++wordCount;
//                wordData[indexTrack]->count += 1;
//                wordData[indexTrack]->paragraph.push_back(parag);
//                wordData[indexTrack]->line.push_back(line);
            }
            else
            {
//                bst::Node<std::string> temp(previousWord, wordCount);
//                mypq.push(temp);
                myfile<<previousWord<<":"<<"["<<wordCount<<"]"<<std::endl;
                wordCount = 1;
                ++indexTrack;
//                bst::Node<std::string> *temp2 = new bst::Node<std::string>(s);
//                wordData.push_back(temp2);
//                wordData[indexTrack]->count += 1;
//                wordData[indexTrack]->paragraph.push_back(parag);
//                wordData[indexTrack]->line.push_back(line);
            }
           //  myfile << s;
        }
        letterCounts[i] = letterCount;
        letterCount = 0;
    }
    //put this in a separate function
//    std::cout<<"Words: "<<total<<std::endl;
//    std::cout<<"Paragraphs: "<<paragraphs<<std::endl;
//    std::cout<<"Reading level: "<<"TODO"<<std::endl; //create readingLevel();
//    std::cout<<"Top 10 words: "<<std::endl;
//    for(int w = 0; w < 10; ++w)
//    {
//        std::cout<<mypq.top()<<std::endl;
//        mypq.pop();
//    }
//    for(int w = 0; w < 26; ++w)
//    {
//        std::cout<<"Number of words that start with "<<c++
//                 <<": "<<letterCounts[w]<<std::endl;
//    }
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    myfile.close();
    std::cout<<"Press y when you are ready to continue";
    std::cin>>s;
//    std::cout<<wordData[0].paragraph.size()<<std::endl;
//    std::cout<<wordData[0]<<std::endl;
//            for(int r = 0; r < wordData[0].paragraph.size(); ++r)
//            {
//                std::cout<<"Hello;"<<std::endl;
//                std::cout<<wordData[0]<<":";
//                std::cout<<"Press y when you are ready to continue";
//                std::cout<<"["<<wordData[0].paragraph[r]<<","<<wordData[0].line[r]<<"]";
//            }
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
//Word(count){[line,paragraph]}
