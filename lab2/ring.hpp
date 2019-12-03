/*
*   ################################
*   SECTION: CONSTRUCTORS, DESTRUCTORS AND ASSIGNMENT OPERATORS
*   ################################
*/

//default KeyInfoPair constructor
template <typename Key, typename Info>
Ring<Key, Info>::Ring::KeyInfoPair::KeyInfoPair(Key newKey, Info newInfo): key(newKey), info(newInfo) {
    //assign key and info with initializer list
}

//default Node constructor
template <typename Key, typename Info>
Ring<Key, Info>::Ring::Node::Node(Key newKey, Info newInfo, Node* newNext, Node* newPrevious) : keyInfoPair(newKey, newInfo) {
    //create node, assign KIP with initializer list, link to other nodes
    next = newNext;
    previous = newPrevious;
}

//default constructor
template <typename Key, typename Info>
Ring<Key, Info>::Ring() {
    //create empty ring
    anchor = nullptr;
    nodeCount = 0;
}

//default destructor
template <typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    //deallocate all elements
    clear();
}

//copy constructor
template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& other) {
    //prevent self-copying
    if (&other == this)
        return;

    //copy nodes from the other ring
    anchor = nullptr;
    nodeCount = 0;
    copyNodes(other);
}

//move constructor
template <typename Key, typename Info>
Ring<Key, Info>::Ring(Ring<Key, Info>&& other) {
    //take over other ring's resources
    anchor = other.anchor;
    nodeCount = other.nodeCount;

    //mark other ring as empty
    other.anchor = nullptr;
    other.nodeCount = 0;
}

//copy assignment operator
template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info>& other) {
    //prevent self-assignment
    if (&other == this)
        return *this;

    //copy nodes from other ring
    clear();
    copyNodes(other);

    return *this;
}

//move assignment operator
template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(Ring<Key, Info>&& other) {
    //deallocate node list and take over other ring's resources
    clear();
    anchor = other.anchor;
    nodeCount = other.nodeCount;

    //mark other ring as empty
    other.anchor = nullptr;
    other.nodeCount = 0;

    return *this;
}

/*
*   ################################
*   SECTION: ITERATORS
*   ################################
*/

//return iterator to anchor or end() if empty
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin() {
    iterator it;
    it.node = anchor;
    return it;
}

//return abstract end iterator
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::end() {
    iterator it;
    it.node = nullptr;
    return it;
}

//return iterator to anchor or cend() if empty
template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cbegin() const {
    const_iterator it;
    it.node = anchor;
    return it;
}

//return abstract end iterator
template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cend() const {
    const_iterator it;
    it.node = nullptr;
    return it;
}

/*
*   ################################
*   SECTION: CONTAINER COMPARISON
*   ################################
*/

//compare two rings, account for all rotations
template <typename Key, typename Info>
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
            if (thisNode->keyInfoPair.key != otherNode->keyInfoPair.key
                || thisNode->keyInfoPair.info != otherNode->keyInfoPair.info) {
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

//complement of == operator
template <typename Key, typename Info>
bool Ring<Key, Info>::operator!=(const Ring<Key, Info>& other) const {
    return !(*this == other);
}

/*
*   ################################
*   SECTION: ELEMENT ACCESS
*   ################################
*/

//internal random access function
template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::internalAt(int index) const {
    //obtain iterator to first element
    const_iterator it = cbegin();

    //increment/decrement iterator as needed
    for (int i = index; i > 0; i--) ++it;
    for (int i = index; i < 0; i++) --it;

    //dereference iterator
    return *it;
}

//public interface of internalAt
template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::at(int index) {
    return (KeyInfoPair&)internalAt(index);
}

//const version of at
template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::at(int index) const {
    return internalAt(index);
}

//returns reference to anchor
template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::front() {
    return (KeyInfoPair&)internalAt(0);
}

//returns const reference to anchor
template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::front() const {
    return internalAt(0);
}

//returns reference to element before anchor
template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::back() {
    return (KeyInfoPair&)internalAt(-1);
}

//returns const reference to element before anchor
template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::back() const {
    return internalAt(-1);
}

//alias of at
template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::operator[](int index) {
    return (KeyInfoPair&)internalAt(index);
}

//const alias of at
template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::operator[](int index) const {
    return internalAt(index);
}

/*
*   ################################
*   SECTION: MODIFIERS
*   ################################
*/

//insert element before the given position, return reference to inserted element
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::insert(const KeyInfoPair& keyInfoPair, const iterator& position) {
    //if the ring is empty, use push_back's anchor insertion
    if (empty()) {
        push_back(keyInfoPair);
        return begin();
    }

    //create new node and update neighbors
    Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, position.node, position.node->previous);
    position.node->previous->next = newNode;
    position.node->previous = newNode;
    nodeCount++;

    //return iterator to newly created element
    iterator it;
    it.node = newNode;
    return it;
}

//alternative overload of insert
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::insert(const Key& key, const Info& info, const iterator& position) {
    return insert(KeyInfoPair(key, info), position);
}

//insert element before anchor
template <typename Key, typename Info>
void Ring<Key, Info>::push_back(const KeyInfoPair& keyInfoPair) {
    //if there's no anchor, create it
    if (!anchor) {
        //allocate new node with itself as predecessor and successor
        Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, nullptr, nullptr);
        newNode->next = newNode;
        newNode->previous = newNode;

        //mark new anchor
        anchor = newNode;
        nodeCount++;
        return;
    }

    //allocate new element before anchor
    Node* newNode = new Node(keyInfoPair.key, keyInfoPair.info, anchor, anchor->previous);

    //update anchor and the element before it
    anchor->previous->next = newNode;
    anchor->previous = newNode;
    nodeCount++;
}

//alternative overload of push_back
template <typename Key, typename Info>
void Ring<Key, Info>::push_back(const Key& key, const Info& info) {
    push_back(KeyInfoPair(key, info));
}

//erase element at given position, return iterator to next element
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::erase(const iterator& element) {
    //if there's only one element, use clear's anchor clearing
    if (nodeCount == 1) {
        clear();
        return end();
    }

    //unlink element in list
    element.node->previous->next = element.node->next;
    element.node->next->previous = element.node->previous;

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

//erase all elements
template <typename Key, typename Info>
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

//erase all instances of key
template <typename Key, typename Info>
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

//change anchor
template <typename Key, typename Info>
void Ring<Key, Info>::rotate(int amount) {
    //rotate to the left for positive arguments
    for (int i = amount; i > 0; i--)
        anchor = anchor->next;

    //rotate to the right for negative arguments
    for (int i = amount; i < 0; i++)
        anchor = anchor->previous;
}

/*
*   ################################
*   SECTION: LOOKUP
*   ################################
*/

//internal key lookup function
template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::internalFind(const Key& soughtKey, int index) const {
    //if the ring is empty, return end
    if (empty())
        return cend();

    //obtain iterator to first instance of key
    const_iterator it = cbegin();
    if (it->key != soughtKey)
        it = advance(it, soughtKey);

    //if key doesn't exist, return end
    if (it == cend())
        return cend();

    //advance iterator index times
    for(int i = 0; i < index; i++)
        it = advance(it, soughtKey);

    //return iterator
    return it;
}

//public interface of internalFind
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::find(const Key& soughtKey, int index) {
    iterator output;
    output.node = internalFind(soughtKey, index).node;
    return output;
}

//const version of find
template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::find(const Key& soughtKey, int index) const {
    return internalFind(soughtKey, index);
}

//internal iterator advancement function
template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::internalAdvance(const const_iterator& start, const Key& soughtKey) const {
    //move to element immediately following start
    const_iterator it = start;
    ++it;

    //iterate over ring until start is reached again
    do {
        if (it->key == soughtKey)
            return it;

        ++it;
    } while (it != start);

    //if start reached without finding key and start matches key, return start
    if (start->key == soughtKey)
        return start;

    //if no key found, return end iterator
    return cend();
}

//public interface of internalAdvance
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::advance(const iterator& start, const Key& soughtKey) {
    iterator output;
    output.node = internalAdvance(start, soughtKey).node;
    return output;
}

//const version of advance
template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::advance(const const_iterator& start, const Key& soughtKey) const {
    return internalAdvance(start, soughtKey);
}

/*
*   ################################
*   SECTION: CAPACITY
*   ################################
*/

//check if node count is zero
template <typename Key, typename Info>
bool Ring<Key, Info>::empty() const {
    return nodeCount == 0;
}

//check if there is an instance of key
template <typename Key, typename Info>
bool Ring<Key, Info>::empty(const Key& key) const {
    //find first instance of key
    const_iterator it = find(key, 0);

    //if no first instance found, there's no key
    return it == cend();
}

//return node count
template <typename Key, typename Info>
int Ring<Key, Info>::size() const {
    return nodeCount;
}

//return the amount of occurrences of key in ring
template <typename Key, typename Info>
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

/*
*   ################################
*   SECTION: HELPER FUNCTIONS
*   ################################
*/

//add nodes from other ring to the end of this ring
template <typename Key, typename Info>
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
