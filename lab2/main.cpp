#include "ring.h"
#include <iostream>

void print(const Ring<int, int>& ring) {
    Ring<int, int>::const_iterator cit = ring.cbegin();

    for (int i = 0; i < ring.size(); i++){
        std::cout << cit->key << " ";
        ++cit;
    }

    std::cout << std::endl;
}

int main(){

}
