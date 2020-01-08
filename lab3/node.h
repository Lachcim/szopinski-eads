#ifndef NODE_H
#define NODE_H

template <typename Key, typename Info>
struct AVLTree<Key, Info>::Node {
    Node(KeyInfoPair);
    ~Node();
    Node(const Node&);
    Node(Node&&);

    AVLTree<Key, Info>::Node& operator=(const Node&);
    AVLTree<Key, Info>::Node& operator=(Node&&);

    KeyInfoPair keyInfoPair;
    Node* left;
    Node* right;

    int height;

    Node* insert(const KeyInfoPair&);
};

#include "node.hpp"

#endif
