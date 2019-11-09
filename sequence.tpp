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
    for (SequenceNode* i = other.head; i != 0; i = i->next)
        add(i->key, i->info);
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
typename Sequence<Key, Info>::SequenceNode* Sequence<Key, Info>::createNode(const Key& key, const Info& info) {
    SequenceNode* output = new SequenceNode();
    output->key = new Key(key);
    output->info = new Info(info);
    output->next = 0;

    return output;
}

//addition operator
template <class Key, class Info>
Sequence<Key, Info> Sequence<Key, Info>::operator+(const Sequence<Key, Info>& other) {
    Sequence<Key, Info> output(*this);
    output.copyList(other);

    return output;
}

//addition assignment operator
template <class Key, class Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator+=(const Sequence<Key, Info>& other) {
    this->copyList(other);

    return this;
}

//add element at end of list
template <class Key, class Info>
void Sequence<Key, Info>::add(const Key& key, const Info& info) {
    if (this->size != 0) {
        //add element at end of list, ypdate tail
        this->tail->next = createNode(key, info);
        this->tail = this->tail->next;
    }
    else {
        //the list is empty, set element as head and tail
        this->head = createNode(key, info);
        this->tail = this->tail;
    }

    this->size++;
}

//add element at given index
template <class Key, class Info>
bool Sequence<Key, Info>::add(const Key& key, const Info& info, int desiredIndex) {
    //prevent addition at illegal indices
    if (desiredIndex < 0 || desiredIndex > this->size)
        return false;

    //if index is equal to size or the list is empty, add at the end
    if (desiredIndex == this->size || this->size == 0) {
        this->add(key, info);
        return true;
    }

    //if index is 0, create new node and update head
    if (desiredIndex == 0) {
        SequenceNode* oldHead = this->head;
        this->head = createNode(key, info);
        this->head->next = oldHead;
        this->size++;

        return true;
    }

    //insert new node at given index
    SequenceNode* precedingElement = this->head;
    for (int i = 0; i < desiredIndex - 1; i++)
        precedingElement = precedingElement->next;

    SequenceNode* oldNext = precedingElement->next;
    precedingElement->next = createNode(key, info);
    precedingElement->next->next = oldNext;
    this->size++;

    return true;
}

//add different sequence to sequence
template <class Key, class Info>
bool Sequence<Key, Info>::add(const Sequence<Key, Info>& other) {
    this->copyList(other);

    return other.size > 0;
}
