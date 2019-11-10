#include <stdio.h>
#include <cstring>
#include "sequence.h"

template <class Key, class Info>
void split(Sequence<Key, Info> origin, int start, Sequence<Key, Info>& destination1, int step1, int count1, Sequence<Key, Info>& destination2, int step2, int count2) {

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
