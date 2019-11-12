//default constructor
template <class Key, class Info>
Sequence<Key, Info>::iterator::iterator() {
    this->node = 0;
}

//private constructor
template <class Key, class Info>
Sequence<Key, Info>::iterator::iterator(SequenceNode* node) {
    this->node = node;
}

//dereference operator
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::iterator::operator*() {
    return this->node->data;
}

//structure pointer dereference operator
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair* Sequence<Key, Info>::iterator::operator->() {
    return &this->node->data;
}

//prefix incrementation operator
template <class Key, class Info>
typename Sequence<Key, Info>::iterator& Sequence<Key, Info>::iterator::operator++() {
    this->node = this->node->next;
    return *this;
}

//postfix incrementation operator
template <class Key, class Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::iterator::operator++(int) {
    iterator old = *this;
    this->node = this->node->next;
    return old;
}

//comparison operator
template <class Key, class Info>
bool Sequence<Key, Info>::iterator::operator==(const Sequence<Key, Info>::iterator& other) {
    return other.node == this->node;
}

//negated comparison operator
template <class Key, class Info>
bool Sequence<Key, Info>::iterator::operator!=(const Sequence<Key, Info>::iterator& other) {
    return other.node != this->node;
}

//default constructor
template <class Key, class Info>
Sequence<Key, Info>::const_iterator::const_iterator() {
    this->node = 0;
}

//private constructor
template <class Key, class Info>
Sequence<Key, Info>::const_iterator::const_iterator(SequenceNode* node) {
    this->node = node;
}

//conversion constructor
template <class Key, class Info>
Sequence<Key, Info>::const_iterator::const_iterator(const iterator& other) {
    this->node = other->node;
}

//dereference operator
template <class Key, class Info>
const typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::const_iterator::operator*() {
    return this->node->data;
}

//structure pointer dereference operator
template <class Key, class Info>
const typename Sequence<Key, Info>::KeyInfoPair* Sequence<Key, Info>::const_iterator::operator->() {
    return &this->node->data;
}

//prefix incrementation operator
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator& Sequence<Key, Info>::const_iterator::operator++() {
    this->node = this->node->next;
    return *this;
}

//postfix incrementation operator
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::const_iterator::operator++(int) {
    const_iterator old = *this;
    this->node = this->node->next;
    return old;
}

//comparison operator
template <class Key, class Info>
bool Sequence<Key, Info>::const_iterator::operator==(const Sequence<Key, Info>::const_iterator& other) {
    return other.node == this->node;
}

//negated comparison operator
template <class Key, class Info>
bool Sequence<Key, Info>::const_iterator::operator!=(const Sequence<Key, Info>::const_iterator& other) {
    return other.node != this->node;
}
