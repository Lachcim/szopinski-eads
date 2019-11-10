#ifndef SEQUENCEITERATOR_H
#define SEQUENCEITERATOR_H

template <class Key, class Info>
class Sequence<Key, Info>::iterator {
    friend class Sequence;

    private:
        iterator(SequenceNode*);
        SequenceNode* node;

    public:
        iterator();

        KeyInfoPair& operator*();
        KeyInfoPair* operator->();
        KeyInfoPair& operator=(const KeyInfoPair&);
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator&);
        bool operator!=(const iterator&);
};

#endif
