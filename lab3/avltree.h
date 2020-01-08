#ifndef AVLTREE_G
#define AVLTREE_G

template <typename Key, typename Info>
class AVLTree {
    public:
        struct KeyInfoPair {
            Key key;
            Info info;

            KeyInfoPair(Key, Info);
        };

    private:
        struct Node {
            KeyInfoPair keyInfoPair;

            Node* left;
            Node* right;

            Node(Key, Info);
        };

        Node* root;
        int nodeCount;
    public:
        AVLTree();
        ~AVLTree();
        AVLTree(const AVLTree&);
        AVLTree(AVLTree&&);

        AVLTree<Key, Info>& operator=(const AVLTree<Key, Info>&);
        AVLTree<Key, Info>& operator=(AVLTree<Key, Info>&&);

        class iterator;
        class const_iterator;

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

        Info& operator[](const Key&);
        const Info& operator[](const Key&) const;

        iterator insert(const KeyInfoPair&);
        iterator insert(const KeyInfoPair&, const iterator&);
        iterator erase(const iterator&);
        iterator erase(const KeyInfoPair&);
        void clear();

        iterator find(const Key&);
        const_iterator find(const Key) const;

        bool empty() const;
        int size() const;
    private:
        void copyNodes(const AVLTree&);
        const_iterator internalFind(const Key&, int) const;
};

#include "avltree.hpp"
#include "iterators.h"

#endif
