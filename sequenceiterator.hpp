//default constructor
template <class Key, class Info>
Sequence<Key, Info>::iterator::iterator() {
    this->node = 0;
    this->keyed = false;
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
//incrementation operators
template <class Key, class Info>
typename Sequence<Key, Info>::iterator& Sequence<Key, Info>::iterator::operator++() {
    //if node isn't keyed, just go to next node
    if (!this->keyed) {
        this->node = this->node->next;
        return *this;
    }

    //default this to end() if search for next node fails
    SequenceNode* start = this->node;
    this->node = 0;

    //search for next node
    for (SequenceNode* i = start; i != 0; i = i->next)
        if (i->data.key == this->key) {
            this->node = i;
            break;
        }

    return *this;
}
template <class Key, class Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
}
//comparison operators
template <class Key, class Info>
bool Sequence<Key, Info>::iterator::operator==(const Sequence<Key, Info>::iterator& other) {
    return other.node == this->node;
}
template <class Key, class Info>
bool Sequence<Key, Info>::iterator::operator!=(const Sequence<Key, Info>::iterator& other) {
    return other.node != this->node;
}
//private field getters
template <class Key, class Info>
bool Sequence<Key, Info>::iterator::isKeyed() const {
    return this->keyed;
}
template <class Key, class Info>
Key Sequence<Key, Info>::iterator::getKey() const {
    if (this->keyed)
        return this->key;
    else
        return this->node->data.key;
}

//default constructor
template <class Key, class Info>
Sequence<Key, Info>::const_iterator::const_iterator() {
    this->node = 0;
    this->keyed = false;
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
//incrementation operators
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator& Sequence<Key, Info>::const_iterator::operator++() {
    //create ordinary iterator and use its code to advance to next node
    iterator master;
    master.node = this->node;
    master.keyed = this->keyed;
    master.key = this->key;
    ++master;

    this->node = master.node;
    return *this;
}
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::const_iterator::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}
//comparison operators
template <class Key, class Info>
bool Sequence<Key, Info>::const_iterator::operator==(const Sequence<Key, Info>::const_iterator& other) {
    return other.node == this->node;
}
template <class Key, class Info>
bool Sequence<Key, Info>::const_iterator::operator!=(const Sequence<Key, Info>::const_iterator& other) {
    return other.node != this->node;
}
//private field getters
template <class Key, class Info>
bool Sequence<Key, Info>::const_iterator::isKeyed() const {
    return this->keyed;
}
template <class Key, class Info>
Key Sequence<Key, Info>::const_iterator::getKey() const {
    if (this->keyed)
        return this->key;
    else
        return this->node->data.key;
}
