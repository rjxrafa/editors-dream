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
//    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
//    std::cout<<"heapo "<<std::endl;
//    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    in.close();
}

//void EditorAssistHeap::Output(std::ostream &out, const std::string & s)
//{
//    if(wordTotal)
//       // out<<"Words: "<<total<<std::endl;
//    if(pars)
//        out<<"Paragraphs: "<<paragraphs_<<std::endl;
//    if(readLevel)
//     //   out<<"Reading level: "<<"Grade "<<round(fleschKincaid(total,sentence_,syllables_))<<std::endl;
//    if(topTen)
//    {
//        out<<"Top 10 words: "<<std::endl;
//        for(int w = 0; w < 10; ++w)
//        {
//            if(!topWords.empty())
//            {
//                topWords[w];
//            }
//        }
//    }
//    if(letterC)
//        for(int w = 0; w < 26; ++w)
//        {
//            //out<<"Number of words that start with "<<c++;
//            //if(!letterCounts.empty())
//            //    out<<": "<<letterCounts[w]<<std::endl;
//        }
//    if(runTime)
//       // std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
//    if(wordIndex)
//        for(int w = 0, total = wordData.size(); w < total; ++w)
//        {
//            out<<*wordData[w]<<":";
//            for(int r = 0; r < wordData[w]->paragraph.size(); ++r)
//            {
//                out<<"["<<wordData[w]->paragraph[r]<<","<<wordData[w]->line[r]<<"]";
//            }
//            out<<std::endl;
//        }
//}

void EditorAssistHeap::extraction()
{
    bool first = true;
  //  std::ofstream myfile ("test.txt");
  //  clock_t begin = clock();
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
               // uniqueLetterCounts[i]
//                bst::Node<std::string> *temp  = new bst::Node<std::string>(previousWord, wordCount);
                bst::Node<std::string> *temp = new bst::Node<std::string>(previousWord, wordCount);
                //std::set might be faster TODO:replace and see time
                mypq.push(*temp);
               // myfile<<previousWord<<":"<<"["<<wordCount<<"]"<<std::endl;
                wordCount = 1;
                ++indexTrack;
                bst::Node<std::string> *temp2 = new bst::Node<std::string>(s);
                wordData_.push_back(temp2);
                wordData_[indexTrack]->paragraph.push_back(parag);
                wordData_[indexTrack]->line.push_back(line);
            }
           //  myfile << s;
        }
        if(i == 25 && orchard_[i].empty())
        {
//            myfile<<s<<":"<<"["<<wordCount<<"]"<<std::endl;
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
//    myfile.close();
    //put this in a separate function
//    std::cout<<"Words: "<<total_<<std::endl;
//    std::cout<<"Paragraphs: "<<paragraphs_<<std::endl;
//    std::cout<<"Reading level: "<<"Grade "<<round(fleschKincaid(total_,sentence_,syllables_))<<std::endl; //create readingLevel();
//    std::cout<<"Top 10 words: "<<std::endl;
//    for(int w = 0; w < 10; ++w)
//    {
//        if(!topWords_[w].empty())
//        {
//            std::cout<<topWords_[w]<<std::endl;
//        }
//    }
//    for(int w = 0; w < 26; ++w)
//    {
//        std::cout<<"Number of words that start with "<<c++;
//        if(!letterCounts_.empty())
//            std::cout<<": "<<letterCounts_[w]<<" Unique: "<<uniqueLetterCounts_[w]<<std::endl;
//    }
//    std::cout<<"Runtime: "<<seconds_<<" seconds"<<std::endl<<std::endl
//    for(int w = 0; w < wordData_.size(); ++w)
//    {
//        std::cout<< *wordData_[w]<<":";
//        for(int r = 0; r < wordData_[w]->paragraph.size(); ++r)
//        {
//            std::cout<<"["<<wordData_[w]->paragraph[r]<<","<<wordData_[w]->line[r]<<"]";
//        }
//        std::cout<<std::endl;
//    }
    //Output(std::cout);
//    if (WriteToFile())
//      Menu();
}
//Word(count){[line,paragraph]}
