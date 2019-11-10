//private constructor
template <class Key, class Info>
Sequence<Key, Info>::const_iterator::const_iterator(SequenceNode*) {
    this->node = node;
}

//dereference operator
template <class Key, class Info>
const typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::const_iterator::operator*() {
    return this->node->data;
}

//dereference operator 2
template <class Key, class Info>
const typename Sequence<Key, Info>::KeyInfoPair* Sequence<Key, Info>::const_iterator::operator->() {
    return &this->node->data;
}

//postfix incrementation operator
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::const_iterator::operator++() {
    this->node = this->node->next;
    return this;
}

//prefix incrementation operator
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::const_iterator::operator++(int) {
    const_iterator old = *this;
    this->nodd = this->node->next;
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
