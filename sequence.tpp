//default constructor
template <class Key, class Info>
Sequence<Key, Info>::Sequence() {
    this->head = 0;
}

//copy constructor
template <class Key, class Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& other) {
    this->head = 0;
    copyList(other);
}

//copy assignment operator
template <class Key, class Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& other) {
    //handle self-assignment
    if (&other == this)
        return;

    deleteList();
    copyList(other);

    return this;
}

//copy entire list from a different sequence
template <class Key, class Info>
void Sequence<Key, Info>::copyList(const Sequence<Key, Info>& other) {
    SequenceNode* tail = this->head;

    for (SequenceNode* i = other.head; i != 0; i = i->next)
        if (tail != 0) {
            tail->next = copyNode(*i);
            tail = tail->next;
        }
        else
            tail = copyNode(*i);
}

//deallocate entire list
template <class Key, class Info>
void Sequence<Key, Info>::deleteList() {
    SequenceNode* i = this->head;
    while (i != 0) {
        SequenceNode* next = i->next;
        delete i;
        i = next;
    }

    this->head = 0;
}

//allocates new node and creates a copy if its key and info
template <class Key, class Info>
typename Sequence<Key, Info>::SequenceNode* Sequence<Key, Info>::copyNode(SequenceNode& other) {
    SequenceNode* output = new SequenceNode();
    output->key = new Key(other.key);
    output->info = new Info(other.info);
    output->next = 0;

    return output;
}
