/*
*   ################################
*   SECTION: ITERATOR
*   ################################
*/

template <typename Key, typename Info>
AVLTree<Key, Info>::iterator::iterator() {
    prev = nullptr;
    node = nullptr;
    parent = nullptr;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::iterator::iterator(Node* start, AVLTree* newParent) {
    prev = start ? recede(start, start) : nullptr;
    node = start;
    parent = newParent;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::iterator::operator*() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return node->keyInfoPair;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::KeyInfoPair* AVLTree<Key, Info>::iterator::operator->() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return &node->keyInfoPair;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator& AVLTree<Key, Info>::iterator::operator++() {
    if (!node)
        throw std::logic_error("can't increment end iterator");

    prev = node;
    if (node) node = advance(node, node);

    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::iterator::operator++(int) {
    if (!node)
        throw std::logic_error("can't increment end iterator");

    iterator old = *this;
    ++(*this);
    return old;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::iterator::advance(Node* start, Node* current) {
    bool leftExists = current->left != nullptr;
    bool rightExists = current->right != nullptr;
    bool parentExists = current->parent != nullptr;

    //check left branch
    if (leftExists) if (current->left->keyInfoPair.key > start->keyInfoPair.key)
        return advance(start, current->left);

    //check this node
    if (current->keyInfoPair.key > start->keyInfoPair.key)
        return current;

    //check right branch
    if (rightExists) if (current->right->keyInfoPair.key > start->keyInfoPair.key)
        return advance(start, current->right);

    //check parent
    if (parentExists)
        return advance(start, current->parent);

    //if there's no parent, we've reached the end
    return nullptr;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator& AVLTree<Key, Info>::iterator::operator--() {
    if (!prev)
        throw std::logic_error("can't decrement begin iterator");

    node = prev;
    if (prev) prev = recede(prev, prev);

    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::iterator AVLTree<Key, Info>::iterator::operator--(int) {
    if (!prev)
        throw std::logic_error("can't decrement begin iterator");

    iterator old = *this;
    --(*this);
    return old;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::Node* AVLTree<Key, Info>::iterator::recede(Node* start, Node* current) {
    bool leftExists = current->left != nullptr;
    bool rightExists = current->right != nullptr;
    bool parentExists = current->parent != nullptr;

    //check right branch
    if (rightExists) if (current->right->keyInfoPair.key < start->keyInfoPair.key)
        return recede(start, current->right);

    //check this node
    if (current->keyInfoPair.key < start->keyInfoPair.key)
        return current;

    //check left branch
    if (leftExists) if (current->left->keyInfoPair.key < start->keyInfoPair.key)
        return recede(start, current->left);

    //check parent
    if (parentExists)
        return recede(start, current->parent);

    //if there's no parent, we've reached the end
    return nullptr;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::iterator::operator==(const iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::iterator::operator!=(const iterator& other) const {
    return other.node != node;
}

/*
*   ################################
*   SECTION: CONST_ITERATOR
*   ################################
*/

template <typename Key, typename Info>
AVLTree<Key, Info>::const_iterator::const_iterator() {
    prev = nullptr;
    node = nullptr;
    parent = nullptr;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::const_iterator::const_iterator(Node* start, const AVLTree* newParent) {
    iterator it(start, (AVLTree*)newParent); //discard const in good faith
    prev = it.prev;
    node = it.node;
    parent = it.parent;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::const_iterator::const_iterator(const iterator& other) {
    prev = other.prev;
    node = other.node;
    parent = other.parent;
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair& AVLTree<Key, Info>::const_iterator::operator*() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return node->keyInfoPair;
}

template <typename Key, typename Info>
const typename AVLTree<Key, Info>::KeyInfoPair* AVLTree<Key, Info>::const_iterator::operator->() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return &node->keyInfoPair;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator& AVLTree<Key, Info>::const_iterator::operator++() {
    iterator it;
    it.prev = prev;
    it.node = node;

    //use iterator's code
    ++it;

    prev = it.prev;
    node = it.node;

    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::const_iterator::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator& AVLTree<Key, Info>::const_iterator::operator--() {
    iterator it;
    it.prev = prev;
    it.node = node;

    //use iterator's code
    --it;

    prev = it.prev;
    node = it.node;

    return *this;
}

template <typename Key, typename Info>
typename AVLTree<Key, Info>::const_iterator AVLTree<Key, Info>::const_iterator::operator--(int) {
    const_iterator old = *this;
    --(*this);
    return old;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::const_iterator::operator==(const const_iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::const_iterator::operator!=(const const_iterator& other) const {
    return other.node != node;
}
