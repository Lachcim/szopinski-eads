#include <stdexcept>
#include <cmath>
#include <sstream>

/*
*   ################################
*   SECTION: CONSTRUCTORS, DESTRUCTORS AND ASSIGNMENT OPERATORS
*   ################################
*/

//default KeyInfoPair constructor
template <typename Key, typename Info>
AVLTree<Key, Info>::AVLTree::KeyInfoPair::KeyInfoPair(const Key& newKey, const Info& newInfo): key(newKey), info(newInfo) {
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
*   SECTION: CONTAINER COMPARISON
*   ################################
*/

//compare all nodes in order, regardless of internal structure
template <typename Key, typename Info>
bool AVLTree<Key, Info>::operator==(const AVLTree<Key, Info>& other) const {
    //return false on node count mismatch
    if (nodeCount != other.nodeCount)
        return false;

    const_iterator it1 = cbegin();
    const_iterator it2 = other.cbegin();

    //check every node in nominal order
    while (it1 != cend()) {
        if (it1->key != it2->key || it1->info != it2->info)
            return false;

        ++it1;
        ++it2;
    }

    return true;
}

//complement of == operator
template <typename Key, typename Info>
bool AVLTree<Key, Info>::operator!=(const AVLTree<Key, Info>& other) const {
    return !(*this == other);
}

/*
*   ################################
*   SECTION: ELEMENT ACCESS
*   ################################
*/

//internal random access function
template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::internalAt(int index) const {
    //handle empty tree
    if (empty())
        throw std::out_of_range("can't access element of empty tree");

    if (index < 0 || index >= nodeCount)
        throw std::out_of_range("index out of range");

    //optimization: access last element using cend()
    if (index == nodeCount - 1)
        return *(--cend());

    //use iterator to access nth element
    const_iterator it = cbegin();
    for (int i = 0; i < index; i++) ++it;
    return *it;
}

//public interface of internalAt
template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::at(int index) {
    return (KeyInfoPair&)internalAt(index);
}

//const version of at
template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::at(int index) const {
    return internalAt(index);
}

//return first element
template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::front() {
    return (KeyInfoPair&)internalAt(0);
}

//const version of front
template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::front() const {
    return internalAt(0);
}

//return last element
template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::back() {
    return (KeyInfoPair&)internalAt(nodeCount - 1);
}

//const version of back
template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::back() const {
    return internalAt(nodeCount - 1);
}

//return element with the given key
template <typename Key, typename Info>
Info& AVLTree<Key, Info>::operator[](const Key& key) {
    iterator it = find(key);

    if (it == end())
        throw std::out_of_range("no such key");

    return it->info;
}

//const alias of operator[]
template <typename Key, typename Info>
const Info& AVLTree<Key, Info>::operator[](const Key& key) const {
    const_iterator it = find(key);

    if (it == cend())
        throw std::out_of_range("no such key");

    return it->info;
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

//overload of insert
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::insert(const Key& key, const Info& info) {
    return insert(KeyInfoPair(key, info));
}

//erase the node at the given position
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::erase(const iterator& position) {
    if (position.parent != this)
        throw std::invalid_argument("iterator doesn't belong to this container");
    if (position.node == nullptr)
        throw std::out_of_range("can't erase end iterator");

    //obtain reference to next node sans the iterator as well as the current parent
    Node* nextPosition = (++iterator(position)).node;
    Node* originalParent = position.node->parent;

    //perform standard BST removal
    if (!position.node->left && !position.node->right) {
        //if the erased node is a leaf, simply delete it

        updateParent(position.node, nullptr);
        updateHeight(position.node->parent);

        if (position.node == root)
            root = nullptr;

        delete position.node;
    }
    else if (!position.node->left || !position.node->right) {
        //if the erased node only has one child, replace the node with the child

        Node*& child = position.node->left ? position.node->left : position.node->right;
        updateParent(position.node, child);
        child->parent = position.node->parent;
        updateHeight(child->parent);

        if (position.node == root)
            root = child;

        //delete node, prevent former subtree from being deleted
        child = nullptr;
        delete position.node;
    }
    else {
        //if the erased node has two children, replace it with its successor
        //can't replace key because key is const

        //find successor, lowest node in right subtree
        Node* successor = position.node->right;
        while (successor->left)
            successor = successor->left;

        updateParent(successor, nullptr);
        updateHeight(successor->parent);
        updateParent(position.node, successor);
        successor->left = position.node->left;
        successor->right = position.node->right;
        successor->parent = position.node->parent;

        if (position.node == root)
            root = successor;

        //delete node, prevent former subtree from being deleted
        position.node->left = nullptr;
        position.node->right = nullptr;
        delete position.node;
    }

    //perform AVL balancing
    for (Node* ancestor = originalParent; ancestor; ancestor = ancestor->parent) {
        int balance = getBalance(ancestor);

        //left left
        if (balance > 1 && getBalance(ancestor->left) >= 0) {
            ancestor = rotateRight(ancestor);
            continue;
        }
        //right right
        if (balance < -1 && getBalance(ancestor->right) <= 0) {
            ancestor = rotateLeft(ancestor);
            continue;
        }
        //left right
        if (balance > 1 && getBalance(ancestor->left) < 0) {
            ancestor->left = rotateLeft(ancestor->left);
            ancestor = rotateRight(ancestor);
            continue;
        }
        //right left
        if (balance < -1 && getBalance(ancestor->left) > 0) {
            ancestor->right = rotateRight(ancestor->right);
            ancestor = rotateLeft(ancestor);
            continue;
        }
    }

    //final considerations, return iterator to next node
    nodeCount--;
    findLimits();
    return iterator(nextPosition, this);
}

//erase all nodes
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
*   SECTION: LOOKUP
*   ################################
*/

//internal key lookup function
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::internalFind(const Key& soughtKey) const {
    //traverse the binary tree
    Node* node = root;
    while (node) {
        //if the key matches, return an iterator to node
        if (soughtKey == node->keyInfoPair.key)
            return const_iterator(node, this);

        //go left if lower key sought, else go right
        if (soughtKey < node->keyInfoPair.key)
            node = node->left;
        else
            node = node->right;
    }

    //if nothing was found, return cend()
    return cend();
}

//public interface of internalFind
template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::find(const Key& soughtKey) {
    const_iterator it = internalFind(soughtKey);

    iterator output;
    output.node = it.node;
    output.prev = it.prev;
    output.parent = (AVLTree*)it.parent; //discard const in good faith

    return output;
}

//const version of find
template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::find(const Key& soughtKey) const {
    return internalFind(soughtKey);
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
*   SECTION: MISC
*   ################################
*/

//print a graphical representation of the tree
template <typename Key, typename Info>
void AVLTree<Key, Info>::print() const {
    if (!root) {
        std::cout << "(empty tree)" << std::endl;
        return;
    }

    //calculate graphic buffer dimensions
    int bufHeight = root->height * 2 + 1;
    int bufWidth = (int)pow(2, root->height); //number of nodes at lowest point
    bufWidth += (bufWidth - 1) * 5 + 1; //spacing between nodes + eof

    //allocate graphic buffer
    char** buffer = new char*[bufHeight];
    for (int i = 0; i < bufHeight; i++)
        buffer[i] = new char[bufWidth](); //initialize to 0

    //print root in top center
    internalPrint(buffer, bufWidth, root, (bufWidth - 1) / 2, 0);

    //print buffer, treat zero as space
    for (int i = 0; i < bufHeight; i++) {
        for (int j = 0; j < bufWidth - 1; j++) {
                if (buffer[i][j])
                    putchar(buffer[i][j]);
                else
                    putchar(' ');
        }

        putchar('\n');
    }

    //deallocate graphic buffer
    for (int i = 0; i < bufHeight; i++)
        delete buffer[i];
    delete buffer;
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
        return;
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
    updateHeight(parent);

    return newNode;
}

//get AVL balance
template <typename Key, typename Info>
int AVLTree<Key, Info>::getBalance(Node* node) {
    if (!node)
        return 0;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;

    return leftHeight - rightHeight;
}

//update subtree height
template <typename Key, typename Info>
void AVLTree<Key, Info>::updateHeight(Node* node) {
    while (node) {
        int newHeight = 0;

        if (node->left)
            if (node->left->height >= newHeight)
                newHeight = node->left->height + 1;

        if (node->right)
            if (node->right->height >= newHeight)
                newHeight = node->right->height + 1;

        node->height = newHeight;

        node = node->parent;
    }
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
    //update children of pivot's parent
	updateParent(pivot, newTop);

	//update parents
	newTop->parent = pivot->parent;
	pivot->parent = newTop;
	if (surrogateChild) surrogateChild->parent = pivot;

	//update root
	if (pivot == root)
        root = newTop;

	//update heights
	updateHeight(pivot);
}

//change parent's child if the
template <typename Key, typename Info>
void AVLTree<Key, Info>::updateParent(Node* oldChild, Node* newChild) {
	if (!oldChild->parent)
        return;

    if (oldChild->parent->left == oldChild)
        oldChild->parent->left = newChild;
    else
        oldChild->parent->right = newChild;

}

//print a subtree to a graphical buffer at the given coordinates
template <typename Key, typename Info>
void AVLTree<Key, Info>::internalPrint(char** buffer, int bufWidth, Node* node, int x, int y) const {
    //find out graphical key length
    std::stringstream keyBuffer;
    keyBuffer << node->keyInfoPair.key;
    int keyWidth = keyBuffer.tellp();

    //calculate dimensions of key
    int keyStart = x - keyWidth / 2;
    if (keyStart < 0) keyStart = 0;
    if (keyStart + keyWidth >= bufWidth) keyWidth = bufWidth - keyStart - 1;

    //print key at given coordinates
    snprintf(&buffer[y][keyStart], keyWidth + 1, "%s", keyBuffer.str().c_str());

    //print subtrees
    if (node->left) {
        buffer[y + 1][x - 2] = '/';
        internalPrint(buffer, bufWidth, node->left, x - 3, y + 2);
    }
    if (node->right) {
        buffer[y + 1][x + 2] = '\\';
        internalPrint(buffer, bufWidth, node->right, x + 3, y + 2);
    }
}
