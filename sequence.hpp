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
        this->push_back(otherNode->data);
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

//modifiers
template <class Key, class Info>
void Sequence<Key, Info>::push_back(const Key& key, const Info& info) {
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
void Sequence<Key, Info>::push_back(const KeyInfoPair& data) {
    this->push_back(data.key, data.info);
}
template <class Key, class Info>
void Sequence<Key, Info>::pop_back(const Key& key) {
    SequenceNode* lastNodePredecessor = 0;
    SequenceNode* lastNode = 0;

    //find last instance of key and its predecessor
    SequenceNode* previousNode = 0;
    for (SequenceNode* i = this->head; i != 0; i = i->next) {
        if (i->data.key == key) {
            lastNode = i;
            lastNodePredecessor = previousNode;
        }

        previousNode = i;
    }

    //update head and tail if needed
    bool isHead = lastNode == this->head;
    bool isTail = lastNode == this->tail;

    if (isHead && isTail) {
        this->head = 0;
        this->tail = 0;
    }
    else if (isHead) {
        this->head = this->head->next;
    }
    else if (isTail) {
        this->tail = lastNodePredecessor;
        this->tail->next = 0;
    }
    else
        lastNodePredecessor->next = lastNode->next;

    delete lastNode; //undefined behavior if lastNode == 0
    this->nodeCount--;
}
template <class Key, class Info>
void Sequence<Key, Info>::clear() {
    deleteList();
}
template <class Key, class Info>
void Sequence<Key, Info>::clear(const Key& key) {
    //find every instance of key and remove it
    SequenceNode* previousNode = 0;
    for (SequenceNode* i = this->head; i != 0; i = i->next) {
        if (i->data.key == key) {
            //update head and tail if needed
            bool isHead = i == this->head;
            bool isTail = i == this->tail;

            if (isHead && isTail) {
                this->head = 0;
                this->tail = 0;
            }
            else if (isHead) {
                this->head = this->head->next;
            }
            else if (isTail) {
                this->tail = previousNode;
                this->tail->next = 0;
            }
            else
                previousNode->next = i->next;

            //delete this node and back up by one node
            delete i;
            this->nodeCount--;

            if (previousNode != 0) i = previousNode;
            else i = this->head;
        }

        previousNode = i;
    }
}
template <class Key, class Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::insert(iterator position, const Info& info) {
    //optimize for tail insertion
    if (position == this->end()) {
        this->push_back();

        //return identical iterator with new tail
        iterator output(position);
        output.node = this->tail;
        return output;
    }

    //find predecessor
    SequenceNode* predecessor = 0;
    for (SequenceNode* i = this->head; i != 0; i = i->next)
        if (i->next == position.node) {
            predecessor = i;
            break;
        }

    //create new node
    SequenceNode* newNode = new SequenceNode(position.getKey(), info);

    //no predecessor, update head
    if (predecessor == 0) {
        newNode->next = this->head;
        this->head = newNode;

        //return identical iterator with new head
        iterator output(position);
        output.node = newNode;
        return output;
    }

    //predecessor found, establish link
    SequenceNode* oldNext = predecessor->next;
    predecessor->next = newNode;
    newNode->next = oldNext;

    iterator output(position);
    output.node = newNode;
    return output;
}

//element access
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::getElement(const Key& key, int index) const {
    //obtain iterator for sublist
    iterator it = this.begin(key);

    //increment iterator to given index
    for (int i = 0; i < index; i++)
        ++it;

    return it->data; //undefined behavior if no key found
}
template <class Key, class Info>
typename Sequence<Key, Info>::KeyInfoPair& Sequence<Key, Info>::getLastElement(const Key& key) const {
    //create empty iterator
    iterator lastElement;

    //obtain iterator for sublist, increment it until exhaustion
    for (iterator it = this->begin(key); it != this->end(); ++it)
        lastElement = it;

    return lastElement->data; //undefined behavior if no key found
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
    iterator output;
    output.node = this->head;
    return output;
}
template <class Key, class Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::begin(const Key& key) {
    iterator output;
    output.keyed = true;
    output.key = key;

    //set iterator node to first instance of key, if none present, let it stay at 0
    for (SequenceNode* i = this->head; i != 0; i = i->next)
        if (i->data.key == key) {
            output.node = i;
            break;
        }

    return output;
}
template <class Key, class Info>
typename Sequence<Key, Info>::iterator Sequence<Key, Info>::end() {
    return iterator();
}
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::cbegin() const {
    const_iterator output;
    output.node = this->head;
    return output;
}
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::cbegin(const Key& key) const {
    return const_iterator(this->begin());
}
template <class Key, class Info>
typename Sequence<Key, Info>::const_iterator Sequence<Key, Info>::cend() const {
    return const_iterator();
}
