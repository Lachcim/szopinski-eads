#include <iostream>
#include <fstream>
#include "avltree.h"

template class AVLTree<std::string, int>;

int main(int argCount, char* args[])
{
    //require a path
    if (argCount < 2) {
        std::cout << "Please specify a path." << std::endl;
        return 0;
    }

    //create word counter
    AVLTree<std::string, int> counter;
    AVLTree<std::string, int>::iterator it;

    //open file for reading
    std::ifstream file;
    file.open(args[1]);

    //read file word by word and update counter
    std::string word;
    while (file >> word) {
        it = counter.find(word);

        if (it != counter.end())
            it->info++;
        else
            counter.insert(word, 1);
    }

    //list the encountered words and their occurrences
    for (it = counter.begin(); it != counter.end(); ++it)
        std::cout << it->key << " " << it->info << std::endl;

    //print unique word count
    std::cout << "Total encountered words: " << counter.size() << std::endl;
}
