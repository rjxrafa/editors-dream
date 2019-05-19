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
    bool flag = false;
    std::string word, temp;
    std::stringstream words;
    int paragraph = 1, line = 1, letter;
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
                ++paragraph;
            flag = false;
            while(words >> word)
            {
                //myfile >> temp;
                //ascii for a = 97 and 97-97 is for index 0
                if(SanitizeString(word)) //optimize sanitize?
                {
                    letter = word[0] - 65;
                    orchard_[letter].insertData(word,paragraph,line);
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
    bool leastCount = false;
    std::ofstream myfile ("test.txt");
    clock_t begin = clock();
    std::string s = "A", previousWord = "A";
    std::vector<bst::Node<std::string>> mostWords(10);
    std::priority_queue<bst::Node<std::string>> mypq;
    int paragraph, line;
    int wordCount = 1, total = 0, size=0;
    std::cout<<"hello"<<std::endl;
    for(int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {
            ++total;
            previousWord = s;
            //orchard_[i]>>s;
            orchard_[i].extractData(s,paragraph,line);
            if(previousWord == s)
                ++wordCount;
            else
            {
                if(mostWords.size() < 10)
                {
                    mostWords[size].data = previousWord;
                    mostWords[size++].count = wordCount;
//                    mostWords[mostWords.size()].paragraph.push_back(paragraph);
//                    mostWords[mostWords.size()].line.push_back(line);
                }
               else
                {
                    for(int j = 0; j<10;++j)
                    {
                        if(wordCount > mostWords[j].count)
                        {
                            mostWords[j].data = previousWord;
                            mostWords[j].count = wordCount;
                            break;
                        }
                    }
                }
                myfile<<previousWord<<":"<<"["<<wordCount<<"]"<<std::endl;
                wordCount = 1;
            }

           //  myfile << s;
        }
    }
    for(int w = 0; w < 10; ++w)
    {
        std::cout<<mostWords[w]<<std::endl;
    }
    std::cout<<"Total words: "<<total<<std::endl;
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    myfile.close();
}
