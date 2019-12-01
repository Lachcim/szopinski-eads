#ifndef ITERATORS_H
#define ITERATORS_H
#include "ring.h"

template <typename Key, typename Info>
class BiRing<Key, Info>::iterator {

    friend class BiRing;

    private:
        Node* node;

    public:
        iterator();
        
        KeyInfoPair& operator*();
        KeyInfoPair* operator->();
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

};

template <typename Key, typename Info>
class BiRing<Key, Info>::const_iterator {

    friend class BiRing;

    private:
        Node* node;

    public:
        const_iterator();
        const_iterator(const iterator&);
        
        const KeyInfoPair& operator*();
        const KeyInfoPair* operator->();
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

};

#include "iterators.hpp"

#endif 