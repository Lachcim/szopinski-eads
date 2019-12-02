template <typename Key, typename Info>
Ring<Key, Info>::Ring::Node::Node(Key newKey, Info newInfo, Node* newNext, Node* newPrev) : keyAndInfo(newKey, newInfo) {
    //create node, assign KIP with initializer list, link to other nodes
    next = newNext;
    prev = newPrev;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring::KeyInfoPair::KeyInfoPair(Key newKey, Info newInfo): key(newKey), info(newInfo) {
    //assign key and info with initializer list
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring() {
    //create empty ring
    anchor = nullptr;
    nodeCount = 0;
}

template  <typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    //deallocate all elements
    clear();
}

template  <typename Key, typename Info>
void Ring<Key, Info>::copyNodes(const Ring<Key, Info>& other) {
    //obtain iterator over other ring
    const_iterator it = other.cbegin();

    //probe size once to allow self-copying
    int otherNodeCount = other.nodeCount;

    //iterate over other ring, add all its nodes
    for (int i = 0; i < otherNodeCount; i++) {
        push_back(*it);
        ++it;
    }
}

template  <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& other) {
    //prevent self-copying
    if (&other == this)
        return;

    //destroy all nodes and copy them from the other ring
    clear();
    copyNodes(other);
}

template  <typename Key, typename Info>
Ring<Key, Info>::Ring(Ring<Key, Info>&& other) {
    //take over other ring's resources
    clear();
    anchor = other.anchor;
    nodeCount = other.nodeCount;

    //mark other ring as empty
    other.anchor = nullptr;
    other.nodeCount = 0;
}

template  <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info>& other) {
    //prevent self-assignment
    if (&other == this)
        return *this;

    //copy nodes from other ring
    clear();
    copyNodes(other);

    return *this;
}

template  <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(Ring<Key, Info>&& other) {
    //take over other ring's resources
    clear();
    anchor = other.anchor;
    nodeCount = other.nodeCount;

    //mark other ring as empty
    other.anchor = nullptr;
    other.nodeCount = 0;

    return *this;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin() {
    //return iterator to anchor or end() if empty
    iterator it;
    it.node = anchor;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::end() {
    //return abstract end iterator
    iterator it;
    it.node = nullptr;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cbegin() const {
    //return iterator to anchor or cend() if empty
    const_iterator it;
    it.node = anchor;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cend() const {
    //return abstract end iterator
    const_iterator it;
    it.node = nullptr;
    return it;
}

template  <typename Key, typename Info>
void Ring<Key, Info>::clear() {
    //obtain pointer to anchor
    Node* it = anchor;

    //deallocate nodeCount consecutive nodes
    for (int i = 0; i < nodeCount; i++) {
        Node* next = it->next;
        delete it;
        it = next;
    }

    //mark ring as empty
    nodeCount = 0;
    anchor = nullptr;
}

template  <typename Key, typename Info>
bool Ring<Key, Info>::empty() const {
    return nodeCount == 0;
}

template  <typename Key, typename Info>
int Ring<Key, Info>::size() const {
    return nodeCount;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::advance(const const_iterator& start, const Key& seekedKey) const {
    return internalAdvance(start, seekedKey);
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::advance(const iterator& start, const Key& seekedKey) {
    iterator output;
    output.node = internalAdvance(start, seekedKey).node;
    return output;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::internalAdvance(const const_iterator& start, const Key& seekedKey) const {
    //move to element immediately following start
    const_iterator it = start;
    ++it;

    //iterate over ring until start is reached again
    do {
        if (it->key == seekedKey)
            return it;

        ++it;
    } while (it != start);

    //if start reached without finding key and start matches key, return start
    if (start->key == seekedKey)
        return start;

    //if no key found, return end iterator
    return cend();
}

template  <typename Key, typename Info>
void Ring<Key, Info>::push_back(const KeyInfoPair& keyInfoPair) {
    //if there's no anchor, create it
    if (!anchor) {
        //allocate new node with itself as predecessor and successor
        Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, nullptr, nullptr);
        newNode->next = newNode;
        newNode->prev = newNode;

        //mark new anchor
        anchor = newNode;
        nodeCount++;
        return;
    }

    //allocate new element before anchor
    Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, anchor, anchor->prev);

    //update anchor and the element before it
    anchor->prev->next = newNode;
    anchor->prev = newNode;
    nodeCount++;
}

template  <typename Key, typename Info>
void Ring<Key, Info>::push_back(const Key& key, const Info& info) {
    push_back(KeyInfoPair(key, info));
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::insert(const KeyInfoPair& keyInfoPair, iterator& position) {
    //if the ring is empty, use push_back's anchor insertion
    if (empty()) {
        push_back(keyInfoPair);
        return begin();
    }

    //create new node and update neighbors
    Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, position.node, position.node->prev);
    position.node->prev->next = newNode;
    position.node->prev = newNode;
    nodeCount++;

    //return iterator to newly created element
    iterator it;
    it.node = newNode;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::insert(const Key& key, const Info& info, iterator& position) {
    return insert(KeyInfoPair(key, info), position);
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::erase(const iterator& element) {
    //if there's only one element, use clear's anchor clearing
    if (nodeCount == 1) {
        clear();
        return end();
    }

    //unlink element in list
    element.node->prev->next = element.node->next;
    element.node->next->prev = element.node->prev;

    //update anchor if necessary
    if (element.node == anchor) {
        anchor = element.node->next;
    }

    //obtain iterator to next element
    iterator nextElement;
    nextElement.node = element.node->next;

    //delete this element
    delete element.node;
    nodeCount--;

    //return iterator
    return nextElement;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::find(const Key& seekedKey, int index) {
    iterator output;
    output.node = internalFind(seekedKey, index).node;
    return output;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::find(const Key& seekedKey, int index) const {
    return internalFind(seekedKey, index);
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::internalFind(const Key& seekedKey, int index) const {
    //if the ring is empty, return end
    if (empty())
        return cend();

    //obtain iterator to first instance of key
    const_iterator it = cbegin();
    if (it->key != seekedKey)
        it = advance(it, seekedKey);

    //if key doesn't exist, return end
    if (it == cend())
        return cend();

    //advance iterator index times
    for(int i = 0; i < index; i++)
        it = advance(it, seekedKey);

    //return iterator
    return it;
}

template  <typename Key, typename Info>
int Ring<Key, Info>::size(const Key& key) const {
    //obtain iterator to first element
    const_iterator it = cbegin();

    //iterate over ring and count occurrences
    int occurrences = 0;
    do {
        if (it->key == key)
            occurrences++;

        ++it;
    } while (it != cbegin());

    //return the number of found occurrences
    return occurrences;
}

template  <typename Key, typename Info>
bool Ring<Key, Info>::operator==(const Ring<Key, Info>& other) const {
    //return false on node count mismatch
    if (nodeCount != other.nodeCount)
        return false;

    //check all rotations of other
    Node* otherAnchor = other.anchor;
    do {
        //start comparison at respective anchors
        Node* thisNode = anchor;
        Node* otherNode = otherAnchor;

        bool mismatch = false;
        do {
            if (thisNode->keyAndInfo.key != otherNode->keyAndInfo.key
                || thisNode->keyAndInfo.info != otherNode->keyAndInfo.info) {
                //on element mismatch, set flag and stop rotation comparison
                mismatch = true;
                break;
            }

            //check next pair of elements
            thisNode = thisNode->next;
            otherNode = otherNode->next;
        } while (thisNode != anchor);

        //if there was no mismatch during rotation comparison, return true
        if (!mismatch)
            return true;

        //rotate other anchor
        otherAnchor = otherAnchor->next;
    } while(otherAnchor != other.anchor);

    //if no rotation was equal, return false
    return false;
}

template  <typename Key, typename Info>
bool Ring<Key, Info>::operator!=(const Ring<Key, Info>& other) const {
    return !(*this == other);
}

template  <typename Key, typename Info>
void Ring<Key, Info>::clear(const Key& key) {
    //obtain iterator to first element
    iterator it = begin();

    //iterate over entire ring and remove all instances of key
    for (int i = 0; i < nodeCount; i++){
        if (it->key == key) {
            it = erase(it);
            i--;
        }

        ++it;
    }
}

template  <typename Key, typename Info>
bool Ring<Key, Info>::empty(const Key& key) const {
    //find first instance of key
    const_iterator it = find(key, 0);

    //if no first instance found, there's no key
    return it == cend();
}
