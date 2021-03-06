#include <stdio.h>
#include <cstring>
#include "sequence.h"

template <class Key, class Info>
void split(const Sequence<Key, Info>& source, int start, Sequence<Key, Info>& dest1, int step1, int count1, Sequence<Key, Info>& dest2, int step2, int count2) {
    //prevent incrementation past sequence
    if (start >= source.size())
        return;

    //obtain key-agnostic iterator of source
    typename Sequence<Key, Info>::const_iterator it = source.cbegin();

    //increment iterator to start position
    for (int i = 0; i < start; i++)
        ++it;

    //output to dest1 and dest2 interchangeably until both destinations exhausted
    for (bool outputtingTo1 = true; count1 > 0 || count2 > 0; outputtingTo1 ^= true) {
        //handle destination exhaustion
        if (outputtingTo1 && count1 == 0) continue;
        if (!outputtingTo1 && count2 == 0) continue;

        //copy step1 or step2 elements to dest1 or dest2
        for (int i = 0; i < (outputtingTo1 ? step1 : step2) && it != source.cend(); i++)
            (outputtingTo1 ? dest1 : dest2).push_back(*it++);

        //exit function if end of source reached
        if (it == source.cend())
            return;

        //decrement destination counter
        if (outputtingTo1) count1--;
        else count2--;
    }
}

void printSequence(const Sequence<const char*, int>& sequence) {
    //buffers for text storage
    char bufferTop[256];
    char bufferBottom[256];
    char bufferTopTemp[16];
    char bufferBottomTemp[16];

    //labels
    strcpy(bufferTop, "Key:  ");
    strcpy(bufferBottom, "Info: ");

    //add sequence data to buffers
    Sequence<const char*, int>::const_iterator i;
    for (i = sequence.cbegin(); i != sequence.cend(); ++i) {
        //write data to temp buffers
        sprintf(bufferTopTemp, "%s ", i->key);
        sprintf(bufferBottomTemp, "%d ", i->info);

        int lengthDifference = strlen(bufferTopTemp) - strlen(bufferBottomTemp);

        //add spaces to achieve equal length
        if (lengthDifference < 0)
            for (int j = lengthDifference; j != 0; j++)
                strcat(bufferTopTemp, " ");
        else
            for (int j = lengthDifference; j != 0; j--)
                strcat(bufferBottomTemp, " ");

        //append temp buffers to final buffers
        strcat(bufferTop, bufferTopTemp);
        strcat(bufferBottom, bufferBottomTemp);
    }

    //print buffers
    printf("%s\n", bufferTop);
    printf("%s\n\n", bufferBottom);
}
int main()
{
    Sequence<const char*, int> source;
    source.push_back("stays", 123);
    source.push_back("stays", 12345);
    source.push_back("stays", 1234567);
    source.push_back("dest1", 31415);
    source.push_back("dest1", 27182);
    source.push_back("dest2", 2137);
    source.push_back("dest2", 69);
    source.push_back("dest2", 420);
    source.push_back("dest1", 16180);
    source.push_back("dest1", 14142);
    source.push_back("dest2", 1352);
    source.push_back("dest2", 911);
    source.push_back("dest2", 404);
    source.push_back("dest2", 1337);
    source.push_back("dest2", 8008135);

    printf("Original sequence:\n");
    printSequence(source);

    Sequence<const char*, int> destination1;
    Sequence<const char*, int> destination2;

    printf("Splitting: starting at 3, 2 elements to dest1 2 times, 3 elements to dest2 3 times\n");
    split(source, 3, destination1, 2, 2, destination2, 3, 3);

    printf("Destination 1:\n");
    printSequence(destination1);
    printf("Destination 2:\n");
    printSequence(destination2);
}
