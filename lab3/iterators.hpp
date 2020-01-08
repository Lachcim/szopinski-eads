/*
*   ################################
*   SECTION: ITERATOR
*   ################################
*/

template <typename Key, typename Info>
AVLTree<Key, Info>::iterator::iterator() {
    node = nullptr;
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
    node = nullptr;
}

template <typename Key, typename Info>
AVLTree<Key, Info>::const_iterator::const_iterator(const iterator& other) {
    node = other.node;
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
bool AVLTree<Key, Info>::const_iterator::operator==(const const_iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool AVLTree<Key, Info>::const_iterator::operator!=(const const_iterator& other) const {
    return other.node != node;
}
