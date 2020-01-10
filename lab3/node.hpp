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
    this->left = nullptr;
    this->right = nullptr;

    //copy children, set their parent
    if (other.left) {
        this->left = new Node(*other.left);
        this->left->parent = this;
    }
    if (other.right) {
        this->right = new Node(*other.right);
        this->right->parent = this;
    }

    //copy parameters
    this->parent = other.parent;
    this->height = other.height;
}

//move constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(Node&& other) : keyInfoPair(other.keyInfoPair) {
    this->left = other.left;
    this->right = other.right;
    this->parent = other.parent;
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

    this->left = nullptr;
    this->right = nullptr;

    if (other.left) {
        this->left = new Node(*other.left);
        this->left->parent = this;
    }
    if (other.right) {
        this->right = new Node(*other.right);
        this->right->parent = this;
    }

    //copy properties
    this->parent = other.parent;
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
