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

}
