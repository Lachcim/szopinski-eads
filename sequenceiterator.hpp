template <class Key, class Info>
class Sequence<Key, Info>::const_iterator {
    friend class Sequence;

    private:
        const_iterator();
        const_iterator(SequenceNode*);
    protected:
        SequenceNode* node;
    public:
        const KeyInfoPair& operator*();
        const KeyInfoPair* operator->();
        const_iterator operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator&);
        bool operator!=(const const_iterator&);
};

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

template <class Key, class Info>
class Sequence<Key, Info>::iterator : public const_iterator {
    public:
        KeyInfoPair& operator*();
        KeyInfoPair* operator->();
        KeyInfoPair& operator=(const KeyInfoPair&);
        iterator operator++();
        iterator operator++(int);
};
