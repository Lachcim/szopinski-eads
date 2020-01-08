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
