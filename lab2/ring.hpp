template <typename Key, typename Info>
Ring<Key, Info>::Ring::Node::Node(Key newKey, Info newInfo, Node* newNext, Node* newPrev) {
    keyAndInfo = KeyInfoPair(newKey, newInfo);
    next = newNext;
    prev = newPrev;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring::Node::Node() {
    next = nullptr;
    prev = nullptr;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring::KeyInfoPair::KeyInfoPair(Key newKey, Info newInfo) {
    key = newKey;
    info = newInfo;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring() {
    anchor = nullptr;
    nodeCount = 0;
}

template  <typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    clear();
}

template  <typename Key, typename Info>
void Ring<Key, Info>::copyNodes(const Ring<Key, Info>& other) {
    Node* temp = other.anchor;

    while (true) {
        push_back(temp->keyAndInfo);

        temp = temp->next;
        if (temp == other.anchor)
            break;
    }
}

template  <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& other) {
    clear();
    copyNodes(other);
}

template  <typename Key, typename Info>
Ring<Key, Info>::Ring(Ring<Key, Info>&& other) {
    clear();
    anchor = other.anchor;
    nodeCount = other.nodeCount;
    other.anchor = nullptr;
    other.nodeCount = 0;
}

template  <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info>& other) {
    clear();
    copyNodes(other);
}

template  <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(Ring<Key, Info>&& other) {
    clear();
    anchor = other.anchor;
    nodeCount = other.nodeCount;
    other.anchor = nullptr;
    other.nodeCount = 0;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin() {
    iterator it;
    it.node = anchor;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::end() {
    iterator it;
    it.node = nullptr;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cbegin() const {
    const_iterator it;
    it.node = anchor;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cend() const {
    const_iterator it;
    it.node = nullptr;
    return it;
}

template  <typename Key, typename Info>
void Ring<Key, Info>::clear() {
    Node* it = anchor;

    for (int i = 0; i < nodeCount; i++) {
        Node* next = it->next;
        delete it;
        it = next;
    }

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
    return internalAdvance(start, seekedKey);
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::internalAdvance(const const_iterator& start, const Key& seekedKey) const {
    const_iterator it = start;
    ++it;

    do {
        if (it->key == seekedKey)
            return it;

        ++it;
    } while (it != start);

    if (start->key == seekedKey)
        return start;

    return cend();
}

template  <typename Key, typename Info>
void Ring<Key, Info>::push_back(const KeyInfoPair& keyInfoPair) {
    if (!anchor) {
        Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, nullptr, nullptr);
        newNode->next = newNode;
        newNode->prev = newNode;

        anchor = newNode;
        nodeCount++;
        return;
    }

    Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, anchor, anchor->prev);

    anchor->prev->next = newNode;
    anchor->prev = newNode;
    nodeCount++;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::insert(const KeyInfoPair& keyInfoPair, iterator& position) {
    if (empty()) {
        push_back(keyInfoPair);
        return begin();
    }

    Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, position.node, position.node->prev);
    position.node->prev->next = newNode;
    position.node->prev = newNode;
    nodeCount++;

    iterator it;
    it.node = newNode;
    return it;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::erase(const iterator& element) {
    if (nodeCount == 1) {
        clear();
        return end();
    }

    element.node->prev->next = element.node->next;
    element.node->next->prev = element.node->prev;

    if (element.node == anchor) {
        anchor = element.node->next;
    }

    iterator nextElement;
    nextElement.node = element.node->next;

    delete element.node;
    nodeCount--;

    return nextElement;
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::find(const Key& seekedKey, int index) {
    return internalFind(seekedKey, index);
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::find(const Key& seekedKey, int index) const {
    return internalFind(seekedKey, index);
}

template  <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::internalFind(const Key& seekedKey, int index) const {
    if (empty())
        return cend();

    const_iterator it = cbegin();
    if (it->key != seekedKey)
        advance(seekedKey, it);

    if (it == cend())
        return cend();

    for(int i = 0; i < index; i++)
        advance(seekedKey, it);

    return it;
}

template  <typename Key, typename Info>
int Ring<Key, Info>::size(const Key& key) const {
    const_iterator it = cbegin();
    int occurrences = 0;

    while (true) {
        if (it->key == key)
            occurrences++;

        ++it;
        if (it == cbegin()) break;
    }

    return occurrences;
}

template  <typename Key, typename Info>
bool Ring<Key, Info>::operator==(const Ring<Key, Info>& other) const {
    if (nodeCount != other.nodeCount)
        return false;

    //todo
}

template  <typename Key, typename Info>
bool Ring<Key, Info>::operator!=(const Ring<Key, Info>& other) const {
    return !(*this == other);
}

template  <typename Key, typename Info>
void Ring<Key, Info>::clear(const Key& key) {
    iterator it = begin();

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
    const_iterator it = find(key, 0);
    return it == cend();
}
