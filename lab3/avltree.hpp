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

/*
*   ################################
*   SECTION: ITERATORS
*   ################################
*/

//return iterator to lowest key or end() if empty
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::begin() {
    if (empty())
        return iterator(nullptr, this);

    //obtain pointer to root
    Node* node = root;

    //keep requesting lower key
    while (node->left)
        node = node->left;

    return iterator(node, this);
}

//return iterator to highest key, incremented
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::end() {
    if (empty())
        return iterator(nullptr, this);

    Node* node = root;
    while (node->right)
        node = node->right;

    return iterator(node, this);
}

//return iterator to lowest key or cend() if empty
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cbegin() const {
    if (empty())
        return const_iterator(nullptr, this);

    Node* node = root;
    while (node->left)
        node = node->left;

    return const_iterator(node, this);
}

//return iterator to highest key, incremented
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cend() const {
    if (empty())
        return const_iterator(nullptr, this);

    Node* node = root;
    while (node->right)
        node = node->right;

    return const_iterator(node, this);
}

/*
*   ################################
*   SECTION: AVL LOGIC
*   ################################
*/

//insert a new leaf or update existing node if key exists
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::bstInsert(Node* node, const KeyInfoPair& kip) {
    //if key exists, update value
    if (node->keyInfoPair.key == kip.key) {
        node->keyInfoPair.info = kip.info;
        return node;
    }

    //standard BST insertion
    if (kip.key < node->keyInfoPair.key) {
        //append to the left
        if (!node->left) {
            //create new leaf
            node->left = new Node(kip);
            if (!node->right) node->height++;
            return node->left;
        }
        else {
            //delegate insertion further
            Node* output = bstInsert(node->left, kip);
            node->height = output->height + 1;
            return output;
        }
    }
    else {
        //append to the right
        if (!node->right) {
            //create new leaf
            node->right = new Node(kip);
            if (!node->left) node->height++;
            return node->right;
        }
        else {
            //delegate insertion further
            Node* output = bstInsert(node->right, kip);
            node->height = output->height + 1;
            return output;
        }
    }
}

/*
*   ################################
*   SECTION: CAPACITY
*   ################################
*/

//check if node count is zero
template <typename Key, typename Info>
bool AVLTree<Key, Info>::empty() const {
    return nodeCount == 0;
}

//return node count
template <typename Key, typename Info>
int AVLTree<Key, Info>::size() const {
    return nodeCount;
}
