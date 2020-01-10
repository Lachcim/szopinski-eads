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
    this->beginNode = nullptr;
    this->endNode = nullptr;
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
    this->beginNode = other.beginNode;
    this->endNode = other.endNode;
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
    this->beginNode = other.beginNode;
    this->endNode = other.endNode;
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
    return iterator(beginNode, this);
}

//return iterator to highest key, incremented
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::end() {
    return ++iterator(endNode, this);
}

//return iterator to lowest key or cend() if empty
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cbegin() const {
    return const_iterator(beginNode, this);
}

//return iterator to highest key, incremented
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cend() const {
    return ++const_iterator(endNode, this);
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

/*
*   ################################
*   SECTION: HELPER FUNCTIONS
*   ################################
*/

//find beginNode and endNode
template <typename Key, typename Info>
void AVLTree<Key, Info>::findLimits() {
    if (empty()) {
        beginNode = nullptr;
        endNode = nullptr;
    }

    //obtain pointer to root, keep requesting lower number
    Node* node = root;
    while (node->left)
        node = node->left;
    beginNode = node;

    //repeat operation for higher numbers
    node = root;
    while (node->right)
        node = node->right;
    endNode = node;
}

//add leaf to node
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::addLeaf(Node* parent, bool right, const KeyInfoPair& kip) {
    //check if branch is free to take
    if (!right && parent->left)
        throw std::invalid_argument("this node already has a left branch");
    if (right && parent->right)
        throw std::invalid_argument("this node already has a right branch");

    //create and add new node
    Node*& newNode = right ? parent->right : parent->left;
    newNode = new Node(kip);
    newNode->parent = parent;

    //if this was the node's second child, return
    if (parent->left && parent->right)
        return newNode;

    //if this was the node's first child, update height
    while (parent) {
        parent->height++;
        parent = parent->parent;
    }

    return newNode;
}
