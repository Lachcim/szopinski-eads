#include <stdio.h>
#include <cstring>
#include "sequence.h"

template <class Key, class Info>
void split(Sequence<Key, Info> origin, int start, Sequence<Key, Info>& dest1, int step1, int count1, Sequence<Key, Info>& dest2, int step2, int count2) {
    //obtain iterator of origin
    typename Sequence<Key, Info>::iterator it = origin.start();

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
    Sequence<const char*, int> mySequence;
    mySequence.add("alpha", 123);
    mySequence.add("beta", 123456);
    mySequence.add("gamma", 98765);

    printSequence(mySequence);

    int i; scanf("%d", &i);
}
