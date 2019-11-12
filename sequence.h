#ifndef SEQUENCE_H
#define SEQUENCE_H

template <class Key, class Info>
class Sequence {
    public:
        struct KeyInfoPair {
            Key key;
            Info info;
        };

    private:
        struct SequenceNode {
            KeyInfoPair data;
            SequenceNode* next;
        };

        SequenceNode* head;
        SequenceNode* tail;
        int nodeCount;

        void copyList(const Sequence<Key, Info>&);
        void deleteList();
        static SequenceNode* createNode(const Key&, const Info&);

    public:
        Sequence<Key, Info>();
        Sequence<Key, Info>(const Sequence<Key, Info>&);
        ~Sequence<Key, Info>();

        class iterator;
        iterator begin();
        iterator end();
        class const_iterator;
        const_iterator cbegin() const;
        const_iterator cend() const;

        Sequence<Key, Info>& operator=(const Sequence<Key, Info>&);

        void add(const Key&, const Info&);
        void add(const KeyInfoPair&);
        bool add(const Key&, const Info&, int);
        bool add(const KeyInfoPair&, int);
        bool add(const Sequence<Key, Info>&);
        bool get(int, Key&, Info&) const;
        bool get(int, KeyInfoPair&) const;
        bool remove();
        bool remove(int);
        int size() const;
};

//declaration of iterators
#include "sequenceiterator.h"

//implementation of sequence and iterators
#include "sequence.hpp"
#include "sequenceiterator.hpp"

#endif
