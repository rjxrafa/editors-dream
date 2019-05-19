#include "editorassistheap.h"

EditorAssistHeap::EditorAssistHeap()
{

}

EditorAssistHeap::~EditorAssistHeap()
{
//    for(int i = 0; i < 26; ++i)
//        orchard_[i].clear();
}

void EditorAssistHeap::insertion()
{
    std::string temp, file;
    int paragraph, line, letter;
    std::cout<<"Input file name:"<<std::endl;
    std::cin>>file;
    //if file does not contain.txt add it
    if(file.find(".txt") == std::string::npos)
        file += ".txt";
    std::ifstream myfile(file);
    clock_t begin = clock();
    while(myfile >> temp)
    {
        //myfile >> temp;
        //ascii for a = 97 and 97-97 is for index 0
        if(SanitizeString(temp)) //optimize sanitize?
        {
        letter = temp[0] - 97;
        paragraph = 0;
        line = 0;
       // if(SanitizeString(temp))
            orchard_[letter].insertData(temp,paragraph,line);
        }
    }
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
    myfile.close();
}

void EditorAssistHeap::extraction()
{
    std::ofstream myfile ("test.txt");
    clock_t begin = clock();
    std::string s, previousWord;
    int wordCount;
    for(int i = 0; i < 26; ++i)
    {
        while(!orchard_[i].empty())
        {
            orchard_[i] >> s;


              myfile << s;
        }
    }
    double seconds = (double)(clock()-begin)/CLOCKS_PER_SEC;
    std::cout<<"Runtime: "<<seconds<<" seconds"<<std::endl<<std::endl;
      myfile.close();
}
