//default constructor
template <class Key, class Info>
Sequence<Key, Info>::Sequence() {
    this->head = 0;
    this->tail = 0;
    this->size = 0;
}

//copy constructor
template <class Key, class Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& other) {
    this->head = 0;
    this->tail = 0;
    this->size = 0;

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

//copy entire list from a different sequence and add it to the end of this list
template <class Key, class Info>
void Sequence<Key, Info>::copyList(const Sequence<Key, Info>& other) {
    for (SequenceNode* i = other.head; i != 0; i = i->next) {
        if (this->tail != 0) {
            //add element at end of list
            this->tail->next = copyNode(*i);
            this->tail = this->tail->next;
        }
        else {
            //the list is empty, set element as head and tail
            this->head = copyNode(*i);
            this->tail = this->tail;
        }

        this->size++;
    }
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
    this->tail = 0;
    this->size = 0;
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
