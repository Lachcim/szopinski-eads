#include "ring.h"
#include <iostream>

void print(const BiRing<int, int>& ring) {
    BiRing<int, int>::const_iterator cit = ring.cbegin();
    for(int i=0; i<ring.size(); i++){
        std::cout << cit->key << " ";
        ++cit;
    }
    std::cout << std::endl;

}

int main(){

    BiRing<int, int> ring;
    ring.push_back(BiRing<int, int>::KeyInfoPair(1, 9));
    ring.push_back(BiRing<int, int>::KeyInfoPair(2, 5));
    ring.push_back(BiRing<int, int>::KeyInfoPair(6, 6));
    ring.push_back(BiRing<int, int>::KeyInfoPair(123, 6));
    ring.push_back(BiRing<int, int>::KeyInfoPair(6, 7));
    ring.push_back(BiRing<int, int>::KeyInfoPair(123, 6));
    ring.push_back(BiRing<int, int>::KeyInfoPair(123, 6));
    ring.push_back(BiRing<int, int>::KeyInfoPair(6, 8));
    ring.push_back(BiRing<int, int>::KeyInfoPair(123, 6));
    ring.push_back(BiRing<int, int>::KeyInfoPair(123, 6));
    ring.push_back(BiRing<int, int>::KeyInfoPair(123, 6));
    print(ring);

    BiRing<int, int> ring2(ring);
    //print(ring2);


    //std::cout << ring.size(6) << std::endl;

    BiRing<int, int>::iterator it = ring.begin();
    it++;
    //ring.insert(BiRing<int, int>::KeyInfoPair(12,12), it);
    //print(ring);

    //ring.clear(6);
    if(ring.empty(6)) std::cout << "dupa" << std::endl;
    
    print(ring);

    /*BiRing<int, int>::iterator result = ring.find(6, 0);
    std::cout << result->key << " " << result->info << std::endl;
    result = ring.find(6, 1);
    std::cout << result->key << " " << result->info << std::endl;
    result = ring.find(6, 2);
    std::cout << result->key << " " << result->info << std::endl;
    result = ring.find(6, 3);
    std::cout << result->key << " " << result->info << std::endl;
    result = ring.find(6, 4);
    std::cout << result->key << " " << result->info << std::endl;*/

}