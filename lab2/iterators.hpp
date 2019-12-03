/*
*   ################################
*   SECTION: ITERATOR
*   ################################
*/

template <typename Key, typename Info>
Ring<Key, Info>::iterator::iterator() {
    node = nullptr;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::iterator::operator*() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return node->keyInfoPair;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair* Ring<Key, Info>::iterator::operator->() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return &node->keyInfoPair;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator++() {
    if (!node)
        throw std::logic_error("can't increment end iterator");

    node = node->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator++(int) {
    if (!node)
        throw std::logic_error("can't increment end iterator");

    iterator old = *this;
    node = node->next;
    return old;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator--() {
    if (!node)
        throw std::logic_error("can't decrement end iterator of a ring");

    node = node->previous;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator--(int) {
    if (!node)
        throw std::logic_error("can't decrement end iterator of a ring");

    iterator old = *this;
    node = node->previous;
    return old;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator==(const iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator!=(const iterator& other) const {
    return other.node != node;
}

/*
*   ################################
*   SECTION: CONST_ITERATOR
*   ################################
*/

template <typename Key, typename Info>
Ring<Key, Info>::const_iterator::const_iterator() {
    node = nullptr;
}

template <typename Key, typename Info>
Ring<Key, Info>::const_iterator::const_iterator(const iterator& other) {
    node = other.node;
}

template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::const_iterator::operator*() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return node->keyInfoPair;
}

template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair* Ring<Key, Info>::const_iterator::operator->() const {
    if (!node)
        throw std::logic_error("can't dereference end iterator");

    return &node->keyInfoPair;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator& Ring<Key, Info>::const_iterator::operator++() {
    if (!node)
        throw std::logic_error("can't increment end iterator");

    node = node->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_iterator::operator++(int) {
    if (!node)
        throw std::logic_error("can't increment end iterator");

    const_iterator old = *this;
    node = node->next;
    return old;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator& Ring<Key, Info>::const_iterator::operator--() {
    if (!node)
        throw std::logic_error("can't decrement end iterator of a ring");

    node = node->previous;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_iterator::operator--(int) {
    if (!node)
        throw std::logic_error("can't decrement end iterator of a ring");

    const_iterator old = *this;
    node = node->previous;
    return old;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::const_iterator::operator==(const const_iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::const_iterator::operator!=(const const_iterator& other) const {
    return other.node != node;
}
