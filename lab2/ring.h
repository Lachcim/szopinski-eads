#ifndef RING_H
#define RING_H

template <typename Key, typename Info>
class Ring {
    public:
        struct KeyInfoPair {
            Key key;
            Info info;

            KeyInfoPair(Key, Info);
        };

    private:
        struct Node {
            KeyInfoPair keyAndInfo;
            Node* next;
            Node* prev;

            Node(Key, Info, Node*, Node*);
        };

        Node* anchor;
        int nodeCount;
    public:
        Ring();
        ~Ring();
        Ring(const Ring&);
        Ring(Ring&&);

        Ring<Key, Info>& operator=(const Ring<Key, Info>&);
        Ring<Key, Info>& operator=(Ring<Key, Info>&&);
        bool operator==(const Ring<Key, Info>&) const;
        bool operator!=(const Ring<Key, Info>&) const;

        class iterator;
        class const_iterator;

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

        iterator insert(const KeyInfoPair&, iterator&);
        iterator insert(const Key&, const Info&, iterator&);
        void push_back(const KeyInfoPair&);
        void push_back(const Key&, const Info&);
        iterator erase(const iterator&);
        void clear();
        void clear(const Key&);
        void rotate(int);

        iterator find(const Key&, int);
        const_iterator find(const Key&, int) const;
        iterator advance(const iterator&, const Key&);
        const_iterator advance(const const_iterator&, const Key&) const;

        bool empty() const;
        bool empty(const Key&) const;
        int size() const;
        int size(const Key&) const;

    private:
        void copyNodes(const Ring&);
        const_iterator internalFind(const Key&, int) const;
        const_iterator internalAdvance(const const_iterator&, const Key&) const;
};

#include "ring.hpp"
#include "iterators.h"

#endif
