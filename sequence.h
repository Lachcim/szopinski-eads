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
            SequenceNode(const Key&, const Info&);

            KeyInfoPair data;
            SequenceNode* next;
        };

        SequenceNode* head;
        SequenceNode* tail;
        int nodeCount;

        void copyList(const Sequence<Key, Info>&);
        void deleteList();

        KeyInfoPair& getElement(const Key&, int) const;
        KeyInfoPair& getLastElement(const Key&) const;
    public:
        Sequence<Key, Info>();
        Sequence<Key, Info>(const Sequence<Key, Info>&);
        Sequence<Key, Info>& operator=(const Sequence<Key, Info>&);
        ~Sequence<Key, Info>();

        class iterator;
        iterator begin();
        iterator begin(const Key&);
        iterator end();
        class const_iterator;
        const_iterator cbegin() const;
        const_iterator cbegin(const Key&) const;
        const_iterator cend() const;

        KeyInfoPair& at(const Key&, int);
        const KeyInfoPair& at(const Key&, int) const;
        KeyInfoPair& front(const Key&);
        const KeyInfoPair& front(const Key&) const;
        KeyInfoPair& back(const Key&);
        const KeyInfoPair& back(const Key&) const;

        int size() const;
        int size(const Key&) const;
        bool empty() const;
        bool empty(const Key&) const;

        iterator insert(iterator, const Info&);
        iterator erase(iterator);
        void push_back(const Key&, const Info&);
        void push_back(const KeyInfoPair&);
        void pop_back(const Key&);
        void clear();
        void clear(const Key&);
};

//declaration of iterators
#include "sequenceiterator.h"

//implementation of sequence and iterators
#include "sequence.hpp"
#include "sequenceiterator.hpp"

#endif
