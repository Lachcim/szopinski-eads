#include <stdio.h>
#include <cstring>
#include "sequence.h"

template <class Key, class Info>
void split(Sequence<Key, Info> origin, int start, Sequence<Key, Info>& dest1, int step1, int count1, Sequence<Key, Info>& dest2, int step2, int count2) {
    //obtain iterator of origin
    typename Sequence<Key, Info>::iterator it = origin.begin();

    //increment operator to start position
    for (int i = 0; i < start; i++)
        ++it;

    //output to dest1 and dest2 interchangeably until both destinations exhausted
    for (bool outputtingTo1 = true; count1 > 0 && count2 > 0; outputtingTo1 ^= true) {
        //handle destination exhaustion
        if (outputtingTo1 && count1 == 0) continue;
        if (!outputtingTo1 && count2 == 0) continue;

        //copy step1 or step2 elements to dest1 or dest2
        for (int i = 0; i < (outputtingTo1 ? step1 : step2) && it != origin.end(); i++)
            (outputtingTo1 ? dest1 : dest2).add(*it++);

        //exit function if end of origin reached
        if (it == origin.end())
            return;

        //decrement destination counter
        if (outputtingTo1) count1--;
        else count2--;
    }
}

void printSequence(Sequence<const char*, int>& sequence) {
    char bufferTop[256];
    char bufferBottom[256];
    char bufferTopTemp[16];
    char bufferBottomTemp[16];

    strcpy(bufferTop, "Key:  ");
    strcpy(bufferBottom, "Info: ");

    Sequence<const char*, int>::iterator i;
    for (i = sequence.begin(); i != sequence.end(); ++i) {
        sprintf(bufferTopTemp, "%s ", i->key);
        sprintf(bufferBottomTemp, "%d ", i->info);

        int lengthDifference = strlen(bufferTopTemp) - strlen(bufferBottomTemp);

        if (lengthDifference < 0)
            for (int j = lengthDifference; j != 0; j++)
                strcat(bufferTopTemp, " ");
        else
            for (int j = lengthDifference; j != 0; j--)
                strcat(bufferBottomTemp, " ");

        strcat(bufferTop, bufferTopTemp);
        strcat(bufferBottom, bufferBottomTemp);
    }

    printf("%s\n", bufferTop);
    printf("%s\n", bufferBottom);
}
int main()
{
    Sequence<const char*, int> source;
    source.add("stays", 123);
    source.add("stays", 12345);
    source.add("stays", 1234567);
    source.add("dest1", 31415);
    source.add("dest1", 27182);
    source.add("dest2", 2137);
    source.add("dest2", 69);
    source.add("dest2", 420);
    source.add("dest1", 16180);
    source.add("dest1", 14142);
    source.add("dest2", 1352);
    source.add("dest2", 911);
    source.add("dest2", 404);
    source.add("dest2", 1337);
    source.add("dest2", 8008135);

    printf("Original sequence:\n");
    printSequence(source);

    Sequence<const char*, int> destination1;
    Sequence<const char*, int> destination2;

    printf("\nSplitting: starting at 3, 2 elements to dest1 2 times, 3 elements to dest2 3 times\n");
    split(source, 3, destination1, 2, 2, destination2, 3, 3);

    printf("Destination 1:\n");
    printSequence(destination1);
    printf("\nDestination 2:\n");
    printSequence(destination2);

    int i; scanf("%d", &i);
}
