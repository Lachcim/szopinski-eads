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

        KeyInfoPair& getIndex(int) const;
        static SequenceNode* createNode(const Key&, const Info&);

    public:
        Sequence<Key, Info>();
        Sequence<Key, Info>(const Sequence<Key, Info>&);
        Sequence<Key, Info>& operator=(const Sequence<Key, Info>&);
        ~Sequence<Key, Info>();

        class iterator;
        iterator begin();
        iterator end();
        class const_iterator;
        const_iterator cbegin() const;
        const_iterator cend() const;

        KeyInfoPair& operator[](int);
        const KeyInfoPair& operator[](int) const;
        KeyInfoPair& front();
        const KeyInfoPair& front() const;
        KeyInfoPair& back();
        const KeyInfoPair& back() const;

        int size() const;
        bool empty() const;

        void add(const Key&, const Info&);
        void add(const KeyInfoPair&);
        bool add(const Key&, const Info&, int);
        bool add(const KeyInfoPair&, int);
        bool add(const Sequence<Key, Info>&);
        bool remove();
        bool remove(int);
};

//declaration of iterators
#include "sequenceiterator.h"

//implementation of sequence and iterators
#include "sequence.hpp"
#include "sequenceiterator.hpp"

#endif
