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
    this->beginIterator = iterator(nullptr, nullptr);
    this->endIterator = iterator(nullptr, nullptr);
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
    findLimits();
}

//move constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(AVLTree<Key, Info>&& other) {
    //take over other tree's resources
    this->root = other.root;
    this->beginIterator = other.beginIterator;
    this->endIterator = other.endIterator;
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
    this->nodeCount = other.nodeCount;
    findLimits();

    return *this;
}

//move assignment operator
template <typename Key, typename Info>
AVLTree<Key, Info>& AVLTree<Key, Info>::operator=(AVLTree<Key, Info>&& other) {
    //deallocate node list and take over other tree's resources
    delete this->root;
    this->root = other.root;
    this->beginIterator = other.beginIterator;
    this->endIterator = other.endIterator;
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
    return beginIterator;
}

//return iterator to one past highest key
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::end() {
    return endIterator;
}

//return iterator to lowest key or end() if empty
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cbegin() const {
    return const_iterator(beginIterator);
}

//return iterator to one past highest key
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cend() const {
    return ++const_iterator(endIterator);
}

/*
*   ################################
*   SECTION: MODIFIERS
*   ################################
*/

//insert a new leaf or update existing node if key exists
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::insert(const KeyInfoPair& kip) {
    //if the tree is empty, insert element as root
    if (empty()) {
        root = new Node(kip);
        nodeCount++;
        findLimits();
        return iterator(root, this);
    }

    //find the right insertion point
    Node* parent = root;
    while (true) {
        //if a node was found with the same key, update the value and return
        if (parent->keyInfoPair.key == kip.key) {
            parent->keyInfoPair.info = kip.info;
            return iterator(parent, this);
        }

        //perform standard BST insertion
        if (kip.key < parent->keyInfoPair.key) {
            if (parent->left) { parent = parent->left; continue; }
            else return addLeaf(parent, false, kip);
        }
        else {
            if (parent->right) { parent = parent->right; continue; }
            else return addLeaf(parent, true, kip);
        }
    }

    //TODO: balancing
}
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::insert(const Key& key, const Info& info) {
    return insert(KeyInfoPair(key, info));
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

/*
*   ################################
*   SECTION: HELPER FUNCTIONS
*   ################################
*/

//buffer begin and end iterators
template <typename Key, typename Info>
void AVLTree<Key, Info>::findLimits() {
    if (empty()) {
        beginIterator = iterator(nullptr, this);
        endIterator = iterator(nullptr, this);
    }

    //obtain pointer to root, keep requesting lower number
    Node* node = root;
    while (node->left)
        node = node->left;
    beginIterator = iterator(node, this);

    //repeat operation for higher numbers
    node = root;
    while (node->right)
        node = node->right;
    endIterator = ++iterator(node, this);
}

//add leaf to node
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::addLeaf(Node* parent, bool right, const KeyInfoPair& kip) {
    //check if branch is free to take
    if (!right && parent->left)
        throw std::invalid_argument("this node already has a left branch");
    if (right && parent->right)
        throw std::invalid_argument("this node already has a right branch");

    //create and add new node
    Node*& newNode = right ? parent->right : parent->left;
    newNode = new Node(kip);
    newNode->parent = parent;

    //update tree parameters
    nodeCount++;
    findLimits();

    //if this was the node's second child, return
    if (parent->left && parent->right)
        return iterator(newNode, this);

    //if this was the node's first child, update height
    while (parent) {
        parent->height++;
        parent = parent->parent;
    }

    return iterator(newNode, this);;
}
