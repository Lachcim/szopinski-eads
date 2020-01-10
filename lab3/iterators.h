#ifndef ITERATORS_H
#define ITERATORS_H

template <typename Key, typename Info>
class AVLTree<Key, Info>::iterator {
    friend class AVLTree;

    private:
        Node* prev;
        Node* node;
        Node* next;

        AVLTree* parent;

    public:
        iterator();

        KeyInfoPair& operator*() const;
        KeyInfoPair* operator->() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

    private:
        iterator(Node*, AVLTree*);
        Node* advance(Node*, Node*);
        Node* recede(Node*, Node*);
};

template <typename Key, typename Info>
class AVLTree<Key, Info>::const_iterator {
    friend class AVLTree;

    private:
        Node* prev;
        Node* node;
        Node* next;

        const AVLTree* parent;

    public:
        const_iterator();
        const_iterator(const iterator&);

        const KeyInfoPair& operator*() const;
        const KeyInfoPair* operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

    private:
        const_iterator(Node*, const AVLTree*);
};

#include "iterators.hpp"

#endif
