#include <stdexcept>

/*
*   ################################
*   SECTION: CONSTRUCTORS, DESTRUCTORS AND ASSIGNMENT OPERATORS
*   ################################
*/

//default KeyInfoPair constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree::KeyInfoPair::KeyInfoPair(Key newKey, Info newInfo): key(newKey), info(newInfo) {
    //assign key and info with initializer list
}

//default constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree() {
    //create empty tree
    this->root = nullptr;
    this->nodeCount = 0;
}

//default destructor
template <typename Key, typename Info>
AVLTree<Key, Info>::~AVLTree() {
    delete this->root;
}

//copy constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(const AVLTree<Key, Info>& other) {
    //prevent self-copying
    if (&other == this)
        return;

    //copy nodes from the other tree
    this->root = new Node(*other.root);
    this->nodeCount = other.nodeCount;
}

//move constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(AVLTree<Key, Info>&& other) {
    //take over other tree's resources
    this->root = other.root;
    this->nodeCount = other.nodeCount;

    //mark other tree as empty
    other.root = nullptr;
}

//copy assignment operator
template <typename Key, typename Info>
AVLTree<Key, Info>& AVLTree<Key, Info>::operator=(const AVLTree<Key, Info>& other) {
    //prevent self-assignment
    if (&other == this)
        return *this;

    //destroy current root and copy nodes from other tree
    delete this->root;
    this->root = new Node(*other.root);

    return *this;
}

//move assignment operator
template <typename Key, typename Info>
AVLTree<Key, Info>& AVLTree<Key, Info>::operator=(AVLTree<Key, Info>&& other) {
    //deallocate node list and take over other tree's resources
    delete this->root;
    this->root = other.root;
    this->nodeCount = other.nodeCount;

    //mark other tree as empty
    other.root = nullptr;

    return *this;
}
