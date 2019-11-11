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

    this->copyList(other);
}

//destructor
template <class Key, class Info>
Sequence<Key, Info>::~Sequence() {
    this->deleteList();
}

//copy assignment operator
template <class Key, class Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& other) {
    //handle self-assignment
    if (&other == this)
        return *this;

    this->deleteList();
    this->copyList(other);

    return *this;
}

//copy entire list from a different sequence and add it to the end of this list
template <class Key, class Info>
void Sequence<Key, Info>::copyList(const Sequence<Key, Info>& other) {
    //probe size once to allow self-copying
    int otherSize = other.size;

    SequenceNode* otherNode = other.head;
    for (int i = 0; i < otherSize; i++) {
        this->add(otherNode->data);
        otherNode = otherNode->next;
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
typename Sequence<Key, Info>::SequenceNode* Sequence<Key, Info>::createNode(const Key& key, const Info& info) {
    SequenceNode* output = new SequenceNode();
    output->data.key = key;
    output->data.info = info;
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

    return *this;
}

//add element at end of list
template <class Key, class Info>
void Sequence<Key, Info>::add(const Key& key, const Info& info) {
    if (this->size != 0) {
        //add element at end of list, update tail
        this->tail->next = createNode(key, info);
        this->tail = this->tail->next;
    }
    else {
        //the list is empty, update head and tail
        this->head = createNode(key, info);
        this->tail = this->head;
    }

    this->size++;
}
template <class Key, class Info>
void Sequence<Key, Info>::add(const KeyInfoPair& data) {
    add(data.key, data.info);
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
template <class Key, class Info>
bool Sequence<Key, Info>::add(const KeyInfoPair& data, int desiredIndex) {
    return add(data.key, data.info, desiredIndex);
}

//add different sequence to sequence
template <class Key, class Info>
bool Sequence<Key, Info>::add(const Sequence<Key, Info>& other) {
    this->copyList(other);

    return other.size > 0;
}

//remove last element
template <class Key, class Info>
bool Sequence<Key, Info>::remove() {
    //return false when the list is empty
    if (this->size == 0)
        return false;

    //handle single-element lists
    if (this->size == 1) {
        delete this->tail;

        this->head = 0;
        this->tail = 0;
        this->size = 0;

        return true;
    }

    //find new tail
    SequenceNode* penultimateElement;
    for (SequenceNode* i = this->head; i->next != 0; i = i->next)
        penultimateElement = i;

    //perform removal
    delete this->tail;
    this->tail = penultimateElement;
    this->tail->next = 0;
    this->size--;

    return true;
}

//get element at the given index
template <class Key, class Info>
bool Sequence<Key, Info>::get(int index, Key& outputKey, Info& outputInfo) const {
    //handle illegal indices
    if (index < 0 || index >= this->size)
        return false;

    //optimize for tail
    if (index == this->size - 1) {
        outputKey = this->tail->data.key;
        outputInfo = this->tail->data.info;
        return true;
    }

    SequenceNode* element = this->head;
    for (int i = 0; i < index; i++)
        element = element->next;

    outputKey = element->data.key;
    outputInfo = element->data.info;

    return true;
}
template <class Key, class Info>
bool Sequence<Key, Info>::get(int index, KeyInfoPair& outputData) const {
    return get(index, outputData.key, outputData.info);
}

//remove element at given index
template <class Key, class Info>
bool Sequence<Key, Info>::remove(int index) {
    //handle illegal indices
    if (index < 0 || index >= this->size)
        return false;

    //handle special case: last index
    if (index == this->size - 1) {
        this->remove();
        return true;
    }

    //handle special case: first index
    if (index == 0) {
        SequenceNode* headNext = this->head->next;
        delete this->head;
        this->head = headNext;
        this->size--;

        return true;
    }

    SequenceNode* precedingElement = this->head;
    for (int i = 0; i < index - 1; i++)
        precedingElement = precedingElement->next;

    SequenceNode* oldNext = precedingElement->next->next;
    delete precedingElement->next;
    precedingElement->next = oldNext;
    this->size--;

    return true;
}

//get size
template <class Key, class Info>
int Sequence<Key, Info>::getSize() const {
    return this->size;
}

//iterators
template <class Key, class Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::begin() {
    return iterator(this->head);
}
template <class Key, class Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::end() {
    return iterator(0);
}
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::cbegin() const {
    return const_iterator(this->head);
}
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::cend() const {
    return const_iterator(0);
}
