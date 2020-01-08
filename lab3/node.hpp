/*
*   ################################
*   SECTION: CONSTRUCTORS, DESTRUCTORS AND ASSIGNMENT OPERATORS
*   ################################
*/

//default constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(KeyInfoPair kip) : keyInfoPair(kip) {
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
}

//destructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::~Node() {
    if (this->left) delete this->left;
    if (this->right) delete this->right;
}

//copy constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(const Node& other) : keyInfoPair(other.keyInfoPair) {
    this->left = other.left ? new Node(*other.left) : nullptr;
    this->right = other.right ? new Node(*other.right) : nullptr;
    this->height = other.height;
}

//move constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(Node&& other) : keyInfoPair(other.keyInfoPair) {
    this->left = other.left;
    this->right = other.right;
    this->height = other.height;

    other.left = nullptr;
    other.right = nullptr;
}

//copy assignment operator
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node& AVLTree<Key, Info>::Node::operator=(const Node& other) {
    //prevent self-assignment
    if (&other == this)
        return *this;

    //delete own nodes and copy other nodes
    if (this->left) delete this->left;
    if (this->right) delete this->right;
    this->left = other.left ? new Node(*other.left) : nullptr;
    this->right = other.right ? new Node(*other.right) : nullptr;

    //copy properties
    this->height = other.height;

    return *this;
}

//move assignment operator
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node& AVLTree<Key, Info>::Node::operator=(Node&& other) {
    //prevent self-assignment
    if (&other == this)
        return *this;

    //delete own nodes
    if (this->left) delete this->left;
    if (this->right) delete this->right;

    //take over other nodes and copy properties
    this->left = other.left;
    this->right = other.right;
    this->height = other.height;

    //mark other node as empty
    other.left = nullptr;
    other.right = nullptr;

    return *this;
}

/*
*   ################################
*   SECTION: AVL LOGIC
*   ################################
*/

//insert a new leaf or update existing node if key exists
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::Node::insert(const KeyInfoPair& kip) {
    //if key exists, update value
    if (this->keyInfoPair.key == kip.key) {
        this->keyInfoPair.info = kip.info;
        return this;
    }

    //standard BST insertion
    if (kip.key < this->keyInfoPair.key) {
        //append to the left
        if (!this->left) {
            //create new leaf
            this->left = new Node(kip);
            if (!this->right) this->height++;
            return this->left;
        }
        else {
            //delegate insertion further
            Node* output = this->left->insert(kip);
            this->height = output->height + 1;
            return output;
        }
    }
    else {
        //append to the right
        if (!this->right) {
            //create new leaf
            this->right = new Node(kip);
            if (!this->left) this->height++;
            return this->right;
        }
        else {
            //delegate insertion further
            Node* output = this->right->insert(kip);
            this->height = output->height + 1;
            return output;
        }
    }
}
