#include "ring.h"

/////////////ITERATOR//////////////

template <typename Key, typename Info>
Ring<Key, Info>::iterator::iterator(){
    node = NULL;
}

template <typename Key, typename Info>
Ring<Key, Info>::iterator::iterator(const const_iterator& other){
    node = other.node;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::iterator::operator*() const{
    return node->keyAndInfo;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::KeyInfoPair* Ring<Key, Info>::iterator::operator->() const{
    return &node->keyAndInfo;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator++(){
    node = node->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator++(int){
    iterator old = *this;
    node = node->next;
    return old;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator& Ring<Key, Info>::iterator::operator--(){
    node = node->prev;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator--(int){
    iterator old = *this;
    node = node->prev;
    return old;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator==(const iterator& other) const{
    return other.node == node;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator!=(const iterator& other) const{
    return other.node != node;
}

//////////////////CONST ITERATOR/////////////////////

template <typename Key, typename Info>
Ring<Key, Info>::const_iterator::const_iterator(){
    node = NULL;
}

template <typename Key, typename Info>
Ring<Key, Info>::const_iterator::const_iterator(const iterator& other){
    node = other.node;
}

template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair& Ring<Key, Info>::const_iterator::operator*(){
    return node->keyAndInfo;
}

template <typename Key, typename Info>
const typename Ring<Key, Info>::KeyInfoPair* Ring<Key, Info>::const_iterator::operator->(){
    return &node->keyAndInfo;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator& Ring<Key, Info>::const_iterator::operator++(){
    node = node->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_iterator::operator++(int){
    iterator old = *this;
    node = node->next;
    return old;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator& Ring<Key, Info>::const_iterator::operator--(){
    node = node->prev;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_iterator::operator--(int){
    iterator old = *this;
    node = node->prev;
    return old;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::const_iterator::operator==(const const_iterator& other) const{
    return other.node == node;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::const_iterator::operator!=(const const_iterator& other) const{
    return other.node != node;
}