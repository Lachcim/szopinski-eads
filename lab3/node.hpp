/*
*   ################################
*   SECTION: CONSTRUCTORS, DESTRUCTORS AND ASSIGNMENT OPERATORS
*   ################################
*/

//default constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(KeyInfoPair kip) : keyInfoPair(kip) {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
}

//destructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::~Node() {
    if (left) delete left;
    if (right) delete right;
}

//copy constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(const Node& other) : keyInfoPair(other.keyInfoPair) {
    left = nullptr;
    right = nullptr;

    //copy children, set their parent
    if (other.left) {
        left = new Node(*other.left);
        left->parent = this;
    }
    if (other.right) {
        right = new Node(*other.right);
        right->parent = this;
    }

    //copy parameters
    parent = other.parent;
    height = other.height;
}

//move constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::Node::Node(Node&& other) : keyInfoPair(other.keyInfoPair) {
    left = other.left;
    right = other.right;
    parent = other.parent;
    height = other.height;

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
    if (left) delete left;
    if (right) delete right;

    left = nullptr;
    right = nullptr;

    if (other.left) {
        left = new Node(*other.left);
        left->parent = this;
    }
    if (other.right) {
        right = new Node(*other.right);
        right->parent = this;
    }

    //copy properties
    parent = other.parent;
    height = other.height;

    return *this;
}

//move assignment operator
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node& AVLTree<Key, Info>::Node::operator=(Node&& other) {
    //prevent self-assignment
    if (&other == this)
        return *this;

    //delete own nodes
    if (left) delete left;
    if (right) delete right;

    //take over other nodes and copy properties
    left = other.left;
    right = other.right;
    height = other.height;

    //mark other node as empty
    other.left = nullptr;
    other.right = nullptr;

    return *this;
}
