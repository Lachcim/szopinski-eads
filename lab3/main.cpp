#include <iostream>
#include <fstream>
#include "avltree.h"

template class AVLTree<std::string, int>;

int main(int argCount, char* args[])
{
    //no arguments - default test bench
    if (argCount < 2) {
        AVLTree<int, int> avl;
        avl.insert(5, 0);
        avl.insert(1, 0);
        avl.insert(10, 0);
        avl.print();

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
