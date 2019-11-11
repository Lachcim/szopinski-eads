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
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator&);
        bool operator!=(const iterator&);
};
template <class Key, class Info>
class Sequence<Key, Info>::const_iterator {
    friend class Sequence;

    private:
        const_iterator(SequenceNode*);
        SequenceNode* node;

    public:
        const_iterator();

        const KeyInfoPair& operator*();
        const KeyInfoPair* operator->();
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator&);
        bool operator!=(const const_iterator&);
};

#endif
