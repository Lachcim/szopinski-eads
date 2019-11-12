//default constructor
template <class Key, class Info>
Sequence<Key, Info>::Sequence() {
    this->head = 0;
    this->tail = 0;
    this->nodeCount = 0;
}
//copy constructor
template <class Key, class Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& other) {
    this->head = 0;
    this->tail = 0;
    this->nodeCount = 0;

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
    int otherSize = other.nodeCount;

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
    this->nodeCount = 0;
}
//sequence node constructor, creates a copy of its key and info
template <class Key, class Info>
Sequence<Key, Info>::SequenceNode::SequenceNode(const Key& key, const Info& info) {
    this->data.key = key;
    this->data.info = info;
    this->next = 0;
}


/*
//add element at end of list
template <class Key, class Info>
void Sequence<Key, Info>::add(const Key& key, const Info& info) {
    if (this->nodeCount != 0) {
        //add element at end of list, update tail
        this->tail->next = new SequenceNode(key, info);
        this->tail = this->tail->next;
    }
    else {
        //the list is empty, update head and tail
        this->head = new SequenceNode(key, info);
        this->tail = this->head;
    }

    this->nodeCount++;
}
template <class Key, class Info>
void Sequence<Key, Info>::add(const KeyInfoPair& data) {
    add(data.key, data.info);
}

//add element at given index
template <class Key, class Info>
bool Sequence<Key, Info>::add(const Key& key, const Info& info, int desiredIndex) {
    //prevent addition at illegal indices
    if (desiredIndex < 0 || desiredIndex > this->nodeCount)
        return false;

    //if index is equal to nodeCount or the list is empty, add at the end
    if (desiredIndex == this->nodeCount || this->nodeCount == 0) {
        this->add(key, info);
        return true;
    }

    //if index is 0, create new node and update head
    if (desiredIndex == 0) {
        SequenceNode* oldHead = this->head;
        this->head = createNode(key, info);
        this->head->next = oldHead;
        this->nodeCount++;

        return true;
    }

    //insert new node at given index
    SequenceNode* precedingElement = this->head;
    for (int i = 0; i < desiredIndex - 1; i++)
        precedingElement = precedingElement->next;

    SequenceNode* oldNext = precedingElement->next;
    precedingElement->next = createNode(key, info);
    precedingElement->next->next = oldNext;
    this->nodeCount++;

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

    return other.nodeCount > 0;
}

//remove last element
template <class Key, class Info>
bool Sequence<Key, Info>::remove() {
    //return false when the list is empty
    if (this->nodeCount == 0)
        return false;

    //handle single-element lists
    if (this->nodeCount == 1) {
        delete this->tail;

        this->head = 0;
        this->tail = 0;
        this->nodeCount = 0;

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
    this->nodeCount--;

    return true;
}

//remove element at given index
template <class Key, class Info>
bool Sequence<Key, Info>::remove(int index) {
    //handle illegal indices
    if (index < 0 || index >= this->nodeCount)
        return false;

    //handle special case: last index
    if (index == this->nodeCount - 1) {
        this->remove();
        return true;
    }

    //handle special case: first index
    if (index == 0) {
        SequenceNode* headNext = this->head->next;
        delete this->head;
        this->head = headNext;
        this->nodeCount--;

        return true;
    }

    SequenceNode* precedingElement = this->head;
    for (int i = 0; i < index - 1; i++)
        precedingElement = precedingElement->next;

    SequenceNode* oldNext = precedingElement->next->next;
    delete precedingElement->next;
    precedingElement->next = oldNext;
    this->nodeCount--;

    return true;
}
*/

//element access
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::getElement(const Key& key, int index) const {
    //obtain iterator for sublist
    iterator it = this.begin(key);

    //increment iterator to given index
    for (int i = 0; i < index; i++)
        ++it;

    return it->data;
}
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::getLastElement(const Key& key) const {
    //create empty iterator
    iterator lastElement;

    //obtain iterator for sublist, increment it until exhaustion
    for (iterator it = this->begin(key); it != this->end(); ++it)
        lastElement = it;

    return lastElement->data;
}
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::at(const Key& key, int index) {
    return getElement(key, index);
}
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::front(const Key& key) {
    return getElement(key, 0);
}
template <class Key, class Info>
const typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::front(const Key& key) const {
    return getElement(key, 0);
}
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::back(const Key& key) {
    return getLastElement(key);
}
template <class Key, class Info>
const typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::back(const Key& key) const {
    return getLastElement(key);
}

//capacity
template <class Key, class Info>
int Sequence<Key, Info>::size() const {
    return this->nodeCount;
}
template <class Key, class Info>
int Sequence<Key, Info>::size(const Key& key) const {
    int output = 0;

    for (iterator it = this->begin(key); it != this->end(); ++it)
        if (it->key == key)
            output++;

    return output;
}
template <class Key, class Info>
bool Sequence<Key, Info>::empty() const {
    return this->nodeCount == 0;
}
template <class Key, class Info>
bool Sequence<Key, Info>::empty(const Key& key) const {
    for (iterator it = this->begin(key); it != this->end(); ++it)
        if (it->key == key)
            return false;

    return true;
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
