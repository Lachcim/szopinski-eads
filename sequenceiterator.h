#ifndef SEQUENCEITERATOR_H
#define SEQUENCEITERATOR_H

template <class Key, class Info>
class Sequence<Key, Info>::const_iterator {
    friend class Sequence;

    private:
        const_iterator();
        const_iterator(SequenceNode*);
    protected:
        SequenceNode* node;
    public:
        const KeyInfoPair& operator*();
        const KeyInfoPair* operator->();
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator&);
        bool operator!=(const const_iterator&);
};

template <class Key, class Info>
class Sequence<Key, Info>::iterator : public const_iterator {
    public:
        KeyInfoPair& operator*();
        KeyInfoPair* operator->();
        KeyInfoPair& operator=(const KeyInfoPair&);
        iterator& operator++();
        iterator operator++(int);
};

#endif
