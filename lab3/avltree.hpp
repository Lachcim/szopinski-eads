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
    this->beginIterator = iterator(nullptr, this);
    this->endIterator = iterator(nullptr, this);
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

//return iterator to lowest key or cend() if empty
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cbegin() const {
    return const_iterator(beginIterator);
}

//return iterator to one past highest key
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::cend() const {
    return const_iterator(endIterator);
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
    Node* newLeaf;
    while (true) {
        //if a node was found with the same key, update the value and return
        if (parent->keyInfoPair.key == kip.key) {
            parent->keyInfoPair.info = kip.info;
            return iterator(parent, this);
        }

        //perform standard BST insertion
        if (kip.key < parent->keyInfoPair.key) {
            if (!parent->left) { newLeaf = addLeaf(parent, false, kip); break; }
            else parent = parent->left;
        }
        else {
            if (!parent->right) { newLeaf = addLeaf(parent, true, kip); break; }
            else parent = parent->right;
        }
    }

    //perform AVL balancing
    for (Node* ancestor = parent; ancestor; ancestor = ancestor->parent) {
        int balance = getBalance(ancestor);

        //left left
        if (balance > 1 && kip.key < ancestor->left->keyInfoPair.key) {
            ancestor = rotateRight(ancestor);
            continue;
        }
        //right right
        if (balance < -1 && kip.key > ancestor->right->keyInfoPair.key) {
            ancestor = rotateLeft(ancestor);
            continue;
        }
        //left right
        if (balance > 1 && kip.key > ancestor->left->keyInfoPair.key) {
            ancestor->left = rotateLeft(ancestor->left);
            ancestor = rotateRight(ancestor);
            continue;
        }
        //right left
        if (balance < -1 && kip.key < ancestor->right->keyInfoPair.key) {
            ancestor->right = rotateRight(ancestor->right);
            ancestor = rotateLeft(ancestor);
            continue;
        }
    }

    return iterator(newLeaf, this);
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::insert(const Key& key, const Info& info) {
    return insert(KeyInfoPair(key, info));
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::clear() {
    delete root;
    root = nullptr;
    nodeCount = 0;
    beginIterator = iterator(nullptr, this);
    endIterator = iterator(nullptr, this);
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

    //update tree parameters
    nodeCount++;
    findLimits();

    //update height in the branch
    while (parent) {
        updateHeight(parent);
        parent = parent->parent;
    }

    return newNode;
}

//get AVL balance
template <typename Key, typename Info>
int AVLTree<Key, Info>::getBalance(Node* node) {
    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;

    return leftHeight - rightHeight;
}

//get subtree height
template <typename Key, typename Info>
void AVLTree<Key, Info>::updateHeight(Node* node) {
    int newHeight = 0;

    if (node->left)
        if (node->left->height >= newHeight)
            newHeight = node->left->height + 1;

    if (node->right)
        if (node->right->height >= newHeight)
            newHeight = node->right->height + 1;

    node->height = newHeight;
}

//rotate node left, return new root
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::rotateLeft(Node* pivot) {
	//establish roles
	Node* newTop = pivot->right;
	Node* surrogateChild = newTop->left;

	//perform rotation
	newTop->left = pivot;
	pivot->right = surrogateChild;

	//update relations
	updateRelations(pivot, newTop, surrogateChild);

	return newTop;
}

//rotate node right, return new root
template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::rotateRight(Node* pivot) {
	//establish roles
	Node* newTop = pivot->left;
	Node* surrogateChild = newTop->right;

	//perform rotation
	newTop->right = pivot;
	pivot->left = surrogateChild;

	//update relations
	updateRelations(pivot, newTop, surrogateChild);

	return newTop;
}

//rotate node right, return new root
template <typename Key, typename Info>
void AVLTree<Key, Info>::updateRelations(Node* pivot, Node* newTop, Node* surrogateChild) {
	//update parents
	newTop->parent = pivot->parent;
	pivot->parent = newTop;
	if (surrogateChild) surrogateChild->parent = pivot;

	//update children of pivot's parent
	if (newTop->parent) {
        if (newTop->parent->left == pivot)
            newTop->parent->left = newTop;
        else
            newTop->parent->right = newTop;
	}

	//update root
	if (pivot == root)
        root = newTop;

	//update heights
	updateHeight(pivot);
	updateHeight(newTop);
}
