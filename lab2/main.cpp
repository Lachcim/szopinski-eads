#include "ring.h"
#include <iostream>

template <typename Key, typename Info>
Ring<Key, Info> shuffle(const Ring<Key, Info>& ring1, int count1, const Ring<Key, Info>& ring2, int count2, int reps) {
    //prepare empty output ring
    Ring<Key, Info> output;

    //obtain iterators to both rings
    typename Ring<Key, Info>::const_iterator it1 = ring1.cbegin();
    typename Ring<Key, Info>::const_iterator it2 = ring2.cbegin();

    //mix both rings reps times
    for (int i = 0; i < reps; i++) {
        //add count1 elements from ring1, unless ring1 empty
        if (it1 != ring1.cend())
            for (int j = 0; j < count1; j++)
                output.push_back(*it1++);

        //do the analogous for ring2
        if (it2 != ring2.cend())
            for (int j = 0; j < count2; j++)
                output.push_back(*it2++);
    }

    //return output ring
    return output;
}
void printCharLongRing(const char* label, const Ring<const char*, long>& ring) {
    //print label
    std::cout << label << ":" << std::endl;

    //if ring is empty, print appropriate information
    if (ring.empty()) {
        std::cout << "\t(empty ring)" << std::endl;
        return;
    }

    //obtain const iterator of ring
    Ring<const char*, long>::const_iterator cit = ring.cbegin();

    //iterate over ring, print key and info
    for (int i = 0; i < ring.size(); i++){
        std::cout << "\t(" << cit->key << ") " << cit->info << std::endl;
        ++cit;
    }
}

int main() {
    Ring<const char*, long> smallNumbers;
    smallNumbers.push_back("math", 314);
    smallNumbers.push_back("math", 271);
    smallNumbers.push_back("math", 223);
    smallNumbers.push_back("phys", 662);
    smallNumbers.push_back("phys", 602);
    smallNumbers.push_back("phys", 160);
    smallNumbers.push_back("misc", 420);
    smallNumbers.push_back("misc", 666);
    smallNumbers.push_back("misc", 123);
    smallNumbers.push_back("misc", 404);

    Ring<const char*, long> largeNumbers;
    largeNumbers.push_back("math", 141421356);
    largeNumbers.push_back("math", 173205080);
    largeNumbers.push_back("math", 161803398);
    largeNumbers.push_back("phys", 299792458);
    largeNumbers.push_back("phys", 885418781);
    largeNumbers.push_back("phys", 667430151);
    largeNumbers.push_back("misc", 213702137);
    largeNumbers.push_back("misc", 133701337);

    printCharLongRing("Small numbers", smallNumbers);
    printCharLongRing("Large numbers", largeNumbers);
    printCharLongRing("Shuffled ring", shuffle(smallNumbers, 2, largeNumbers, 3, 5));
}
