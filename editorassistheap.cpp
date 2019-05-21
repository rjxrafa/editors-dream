#include "editorassistheap.h"

EditorAssistHeap::EditorAssistHeap()
{
    paragraphs_ = 1;
}

EditorAssistHeap::~EditorAssistHeap()
{
//    for(int i = 0; i < 26; ++i)
//        orchard_[i].clear();
}

//TODO:File check
//TODO:Create with string parameter for auto run
void EditorAssistHeap::insertion()
{
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
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"heapo "<<std::endl;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    in.close();
}
void EditorAssistHeap::Menu()
{
   std::cout<<"What would you like to save?\n"
              "[ ] (T)otal Words\n"
              "[ ] (P)aragraph Count\n"
              "[ ] (F)lesch Reading Grade Level\n"
              "[ ] (M)ost Used Words\n"
              "[ ] (R)untime\n"
              "[x] (L)etter count\n"
              "[ ] (A)ll of the above\n"

              "Press return to quit.\n";
   std::string s;
   std::cin>>s;
   Output(out,s);
}
void EditorAssistHeap::Output(std::ostream &out, const std::string & s)
{
    bool wordTotal,pars,readLevel,topTen,letterC,runTime,wordIndex;
    wordTotal=pars=readLevel=topTen=letterC=runTime=wordIndex= false;
    for(unsigned int i = 0; i < s.size(); ++i)
    {
        switch(tolower(s[i]))
        {
        case 't': wordTotal = true;
            break;
        case 'p': pars = true;
            break;
        case 'f': readLevel = true;
            break;
        case 'M': topTen = true;
            break;
        case '5': letterC = true;
            break;
        case 'l': runTime = true;
            break;
        case '7': wordIndex = true;
            break;
        default : return;
        }
    }

    if(wordTotal)
       // out<<"Words: "<<total<<std::endl;
    if(pars)
        out<<"Paragraphs: "<<paragraphs_<<std::endl;
    if(readLevel)
     //   out<<"Reading level: "<<"Grade "<<round(fleschKincaid(total,sentence_,syllables_))<<std::endl;
    if(topTen)
    {
        out<<"Top 10 words: "<<std::endl;
        for(int w = 0; w < 10; ++w)
        {
          //  if(!mypq.empty())
            {
          //      std::cout<<mypq.top()<<std::endl;
           //     mypq.pop();
            }
        }
    }
    if(letterC)
        for(int w = 0; w < 26; ++w)
        {
            //out<<"Number of words that start with "<<c++;
            //if(!letterCounts.empty())
            //    out<<": "<<letterCounts[w]<<std::endl;
        }
    if(runTime)
       // std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    if(wordIndex)
        for(int w = 0, total = wordData.size(); w < total; ++w)
        {
            out<<*wordData[w]<<":";
            for(int r = 0; r < wordData[w]->paragraph.size(); ++r)
            {
                out<<"["<<wordData[w]->paragraph[r]<<","<<wordData[w]->line[r]<<"]";
            }
            out<<std::endl;
        }
}

void EditorAssistHeap::extraction()
{
    bool first = true;
    std::ofstream myfile ("test.txt");
    clock_t begin = clock();
    std::string s, previousWord;
    std::vector<int> letterCounts(26);
    std::priority_queue<bst::Node<std::string>, std::vector<bst::Node<std::string>>, CompareNodes> mypq;
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
            previousWord = s;
            orchard_[i].extractData(s,parag,line);
            if(first)
            {
                previousWord = s;
                first=false;
                bst::Node<std::string> *temp2 = new bst::Node<std::string>(s);
                wordData.push_back(temp2);
            }
            if(previousWord == s)
            {
                ++wordCount;
                wordData[indexTrack]->count += 1;
                wordData[indexTrack]->paragraph.push_back(parag);
                wordData[indexTrack]->line.push_back(line);
            }
            else
            {
//                bst::Node<std::string> *temp  = new bst::Node<std::string>(previousWord, wordCount);
//                //std::set might be faster TODO:replace and see time
//                mypq.push(*temp);
                bst::Node<std::string> *temp = new bst::Node<std::string>(previousWord, wordCount);
                //std::set might be faster TODO:replace and see time
                mypq.push(*temp);
                myfile<<previousWord<<":"<<"["<<wordCount<<"]"<<std::endl;
                wordCount = 1;
                ++indexTrack;
                bst::Node<std::string> *temp2 = new bst::Node<std::string>(s);
                wordData.push_back(temp2);
                wordData[indexTrack]->count += 1;
                wordData[indexTrack]->paragraph.push_back(parag);
                wordData[indexTrack]->line.push_back(line);
            }
           //  myfile << s;
        }
        if(i == 25 && orchard_[i].empty())
        {
            myfile<<s<<":"<<"["<<wordCount<<"]"<<std::endl;
            bst::Node<std::string> *temp = new bst::Node<std::string>(s, wordCount);
            //std::set might be faster TODO:replace and see time
            mypq.push(*temp);
        }
        letterCounts[i] = letterCount;
        letterCount = 0;
    }
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    //put this in a separate function
    std::cout<<"Words: "<<total<<std::endl;
    std::cout<<"Paragraphs: "<<paragraphs_<<std::endl;
    std::cout<<"Reading level: "<<"Grade "<<round(fleschKincaid(total,sentence_,syllables_))<<std::endl; //create readingLevel();
    std::cout<<"Top 10 words: "<<std::endl;
    for(int w = 0; w < 10; ++w)
    {
        if(!mypq.empty())
        {
            std::cout<<mypq.top()<<std::endl;
            mypq.pop();
        }
    }
    for(int w = 0; w < 26; ++w)
    {
        std::cout<<"Number of words that start with "<<c++;
        if(!letterCounts.empty())
            std::cout<<": "<<letterCounts[w]<<std::endl;
    }
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    myfile.close();
    //Output(std::cout);
    if (WriteToFile())
      Menu();
}
//Word(count){[line,paragraph]}
