#ifndef SEQUENCEITERATOR_H
#define SEQUENCEITERATOR_H

template <class Key, class Info>
class Sequence<Key, Info>::iterator {
    friend class Sequence;

    private:
        SequenceNode* node;
        Key key;
        bool keyed;

    public:
        iterator();

        KeyInfoPair& operator*();
        KeyInfoPair* operator->();
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator&);
        bool operator!=(const iterator&);

        bool isKeyed() const;
        Key getKey() const;
};
template <class Key, class Info>
class Sequence<Key, Info>::const_iterator {
    friend class Sequence;

    private:
        SequenceNode* node;
        Key key;
        bool keyed;

    public:
        const_iterator();

        const KeyInfoPair& operator*();
        const KeyInfoPair* operator->();
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator&);
        bool operator!=(const const_iterator&);

        bool isKeyed() const;
        Key getKey() const;
};

#endif
