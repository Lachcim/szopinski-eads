#include "ring.h"

template <typename Key, typename Info>
BiRing<Key, Info>::iterator::iterator(){
    node = nullptr;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::KeyInfoPair& BiRing<Key, Info>::iterator::operator*() {
    return node->keyAndInfo;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::KeyInfoPair* BiRing<Key, Info>::iterator::operator->() {
    return &node->keyAndInfo;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::iterator& BiRing<Key, Info>::iterator::operator++() {
    node = node->next;
    return *this;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::iterator::operator++(int) {
    iterator old = *this;
    node = node->next;
    return old;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::iterator& BiRing<Key, Info>::iterator::operator--() {
    node = node->prev;
    return *this;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::iterator::operator--(int) {
    iterator old = *this;
    node = node->prev;
    return old;
}

template <typename Key, typename Info>
bool BiRing<Key, Info>::iterator::operator==(const iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool BiRing<Key, Info>::iterator::operator!=(const iterator& other) const {
    return other.node != node;
}

// //////////////////////////////////////////////////////////////////////////

template <typename Key, typename Info>
BiRing<Key, Info>::const_iterator::const_iterator(){
    node = nullptr;
}

template <typename Key, typename Info>
BiRing<Key, Info>::const_iterator::const_iterator(const iterator& other){
    node = other.node;
}

template <typename Key, typename Info>
const typename BiRing<Key, Info>::KeyInfoPair& BiRing<Key, Info>::const_iterator::operator*() {
    return node->keyAndInfo;
}

template <typename Key, typename Info>
const typename BiRing<Key, Info>::KeyInfoPair* BiRing<Key, Info>::const_iterator::operator->() {
    return &node->keyAndInfo;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator& BiRing<Key, Info>::const_iterator::operator++() {
    node = node->next;
    return *this;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator BiRing<Key, Info>::const_iterator::operator++(int) {
    iterator old = *this;
    node = node->next;
    return old;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator& BiRing<Key, Info>::const_iterator::operator--() {
    node = node->prev;
    return *this;
}

template <typename Key, typename Info>
typename BiRing<Key, Info>::const_iterator BiRing<Key, Info>::const_iterator::operator--(int) {
    iterator old = *this;
    node = node->prev;
    return old;
}

template <typename Key, typename Info>
bool BiRing<Key, Info>::const_iterator::operator==(const const_iterator& other) const {
    return other.node == node;
}

template <typename Key, typename Info>
bool BiRing<Key, Info>::const_iterator::operator!=(const const_iterator& other) const {
    return other.node != node;
}
