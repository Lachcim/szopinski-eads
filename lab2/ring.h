#ifndef RING_H
#define RING_H

template <typename Key, typename Info>
class BiRing {
    public:
        struct KeyInfoPair {
            Key key;
            Info info;

            KeyInfoPair() = default;
            KeyInfoPair(Key newKey, Info newInfo);
        };

    private:
        struct Node {
            
            KeyInfoPair keyAndInfo;
            Node* next;
            Node* prev;
            Node();
            Node(Key newKey, Info newInfo, Node* node, Node* prevNode);
        };
        Node* anchor;
        int nodeCount;
        void copyNodes(const BiRing&);

    public:

    BiRing();
    ~BiRing();
    BiRing(const BiRing&);
    BiRing(BiRing&&);
    
    BiRing<Key, Info>& operator=(const BiRing<Key, Info>&);
    BiRing<Key, Info>& operator=(BiRing<Key, Info>&&);
    bool operator==(const BiRing<Key, Info>&) const;
    bool operator!=(const BiRing<Key, Info>&) const;

    class iterator;
    class const_iterator;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    
    iterator insert(const KeyInfoPair&, iterator& beforeThis);
    void push_back(const KeyInfoPair&);
    iterator erase(const iterator&);
    iterator find(const Key&, int which = 0);
    const_iterator find(const Key&, int which = 0) const;
    void advance(const Key&, const_iterator&) const;
    void clear();
    void clear(const Key&);
    bool empty() const;
    bool empty(const Key&) const;
    int size() const;
    int size(const Key&) const;

    private:
    const_iterator internalFind(const Key&, int) const;
};

#include "ring.hpp"
#include "iterators.h"

#endif