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

bool operator<(const bst::Node<std::string>& a, const bst::Node<std::string>& b)
{
  return a.count > b.count;
}

void EditorAssistHeap::extraction()
{
    std::ofstream myfile ("test.txt");
    clock_t begin = clock();
    std::string s = "A", previousWord = "A";
   // std::vector<bst::Node<std::string>> mostWords(10);
    std::vector<int> letterCounts(26);
    std::priority_queue<bst::Node<std::string>, std::vector<bst::Node<std::string>>, CompareNodes> mypq;
    bst::Node<std::string> temp;
    char c = 'A';
    int parag, line;
    int wordCount = 1, total = 0, size=0, letterCount=0;
    std::cout<<"hello"<<std::endl;
    for(int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {
            ++letterCount;
            ++total;
            previousWord = s;
            orchard_[i].extractData(s,parag,line);
            if(previousWord == s)
                ++wordCount;
            else
            {
                bst::Node<std::string> temp(previousWord, wordCount);
                mypq.push(temp);
                myfile<<previousWord<<":"<<"["<<wordCount<<"]"<<std::endl;
                wordCount = 1;
            }

           //  myfile << s;
        }
        letterCounts[i] = letterCount;
        letterCount = 0;
    }
    std::cout<<"Words: "<<total<<std::endl;
    std::cout<<"Paragraphs: "<<paragraphs<<std::endl;
    std::cout<<"Reading level: "<<"TODO"<<std::endl; //create readingLevel();
    std::cout<<"Top 10 words: "<<std::endl;
    for(int w = 0; w < 10; ++w)
    {
        std::cout<<mypq.top()<<std::endl;
        mypq.pop();
    }
    for(int w = 0; w < 26; ++w)
    {
        std::cout<<"Number of words that start with "<<c++
                 <<": "<<letterCounts[w]<<std::endl;
    }

    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    myfile.close();
}
//Word(count){[line,paragraph]}
