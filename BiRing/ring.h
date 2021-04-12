#ifndef RING_H
#define RING_H

template<typename Key, typename Info>
class Ring{

    public:
    struct KeyInfoPair{
        Key key;
        Info info;

        KeyInfoPair() = default;
        KeyInfoPair(Key newKey, Info newInfo);
    };

    private:
    struct Node{
        KeyInfoPair keyAndInfo;
        Node* next;
        Node* prev;

        Node(); 
        Node(Key newKey, Info newInfo, Node* node, Node* prevNode); 
    };
    Node *any;
    int size;
    void copyAll(const Ring& other);

    public:

    Ring(); 
    ~Ring(); 
    Ring(const Ring &other);
    Ring(Ring&& other);

    class iterator;
    class const_iterator;
    Ring<Key, Info>& operator=(const Ring<Key, Info> &other); 
    Ring<Key, Info>& operator=(Ring<Key, Info>&& other);

    iterator begin(); 
    iterator end(); 
    const_iterator cbegin() const; 
    const_iterator cend() const; 

    void addEnd(const KeyInfoPair &pair);
    bool clear(); 
    bool isEmpty(); 
    int getSize() const;
    void print();

    bool remove(const KeyInfoPair &pair, int which);

};

#include "ring.hpp"
#include "iterators.h"

#endif