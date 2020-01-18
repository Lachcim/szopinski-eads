#ifndef AVLTREE_H
#define AVLTREE_H

template <typename Key, typename Info>
class AVLTree {
    public:
        struct KeyInfoPair {
            const Key key;
            Info info;

            KeyInfoPair(const Key&, const Info&);
        };

        class iterator;
        class const_iterator;

    private:
        struct Node;

        Node* root;
        int nodeCount;
        iterator beginIterator;
        iterator endIterator;
    public:
        AVLTree();
        ~AVLTree();
        AVLTree(const AVLTree&);
        AVLTree(AVLTree&&);

        AVLTree<Key, Info>& operator=(const AVLTree<Key, Info>&);
        AVLTree<Key, Info>& operator=(AVLTree<Key, Info>&&);

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

        bool operator==(const AVLTree<Key, Info>&) const;
        bool operator!=(const AVLTree<Key, Info>&) const;

        KeyInfoPair& at(int);
        KeyInfoPair& front();
        KeyInfoPair& back();
        Info& operator[](const Key&);
        const KeyInfoPair& at(int) const;
        const KeyInfoPair& front() const;
        const KeyInfoPair& back() const;
        const Info& operator[](const Key&) const;

        iterator insert(const KeyInfoPair&);
        iterator insert(const Key&, const Info&);
        iterator erase(const iterator&);
        void clear();

        iterator find(const Key&);
        const_iterator find(const Key&) const;

        bool empty() const;
        int size() const;
    private:
        void findLimits();

        Node* addLeaf(Node*, bool, const KeyInfoPair&);
        int getBalance(Node*);
        void updateHeight(Node*);
        Node* rotateLeft(Node*);
        Node* rotateRight(Node*);
        void updateRelations(Node*, Node*, Node*);
        void updateParent(Node*, Node*);

        const KeyInfoPair& internalAt(int) const;
        const_iterator internalFind(const Key&) const;
};

#include "avltree.hpp"
#include "node.h"
#include "iterators.h"

#endif
