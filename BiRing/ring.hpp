using namespace std;
#include <iostream>

template <typename Key, typename Info>
Ring<Key, Info>::Ring::Node::Node(Key newKey, Info newInfo, Node* node, Node* prevNode){
    keyAndInfo = KeyInfoPair(newKey, newInfo);
    next = node;
    prev = prevNode;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring::Node::Node(){
    next = NULL;
    prev = NULL;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring::KeyInfoPair::KeyInfoPair(Key newKey, Info newInfo){
    key = newKey;
    info = newInfo;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(){
    any = NULL;
    size = 0;
}

template <typename Key, typename Info>
Ring<Key, Info>::~Ring(){
    clear();
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& other){
    if(&other == this)
        return;
    any = NULL;
    size = 0;
    *this = other; 
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(Ring<Key, Info>&& other){
    any = other.any;
    size = other.size;
    other.any = NULL;
    other.size = 0;
}

template <typename Key, typename Info>
void Ring<Key, Info>::copyAll(const Ring<Key, Info>& other){
    Node* temp = other.any;
    while(true){
        addEnd(temp->keyAndInfo);
        temp = temp->next;
        if(temp == other.any)
            break;
    }
}

template <typename Key, typename Info>
Ring<Key, Info> &Ring<Key, Info>::operator=(const Ring<Key, Info>& other){
    if(other.any == NULL)
        return *this;
    clear();
    copyAll(other);
    return *this;
}

template <typename Key, typename Info>
Ring<Key, Info> &Ring<Key, Info>::operator=(Ring<Key, Info>&& other){
    clear();
    any = other.any;
    size = other.size;
    other.any = NULL;
    other.size = 0;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin(){
    iterator it;
    it.node = any;
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::end(){
    iterator it;
    it.node = NULL;
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cbegin() const{
    const_iterator it;
    it.node = any;
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::cend() const{
    const_iterator it;
    it.node = NULL;
    return it;
}

template <typename Key, typename Info>
void Ring<Key, Info>::addEnd(const KeyInfoPair& pair){
    if(any == NULL){
        Node* temp = new Node(pair.key, pair.info, NULL, NULL);
        temp->next = temp;
        temp->prev = temp;
        any = temp;
        size++;
        return;
    }
    Node* temp = new Node(pair.key, pair.info, NULL, NULL);
    any->prev->next = temp;
    any->prev = temp;
    size++;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::remove(const KeyInfoPair &pair, int which){
    if(any == NULL){
        return false;
    }

    Node *curr = any;
    int count = 0;

    do{
        if(curr->keyAndInfo.key == pair.key){
            Node *temp = curr;
            curr->prev = curr->prev->prev;
            curr->next->next->prev = curr;
            //curr->prev->prev->next = curr;
            //curr->next = curr->next->next;
            delete temp->prev;
            delete temp->next;
            return true;
        }
        else
            curr = curr->next;
    }while(curr != any);
    
    return false;
    
}


template <typename Key, typename Info>
bool Ring<Key, Info>::clear(){
    if(isEmpty())
        return false;
    Node *temp = any;
    for(int i = 0; i < size; i++){
        any = any->next;
        delete temp;
        temp = any;
        size--;
    }
    any = NULL;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isEmpty(){
    if(getSize() == 0)
        return true;
    else
        return false;
}

template <typename Key, typename Info>
int Ring<Key, Info>::getSize() const{
    return size;
}

template <typename Key, typename Info>
void Ring<Key, Info>::print(){
    if(isEmpty())
        cout << "The ring is empty" << endl;
    const_iterator it = cbegin();
    for(int i = 0; i < getSize(); i++){
        cout << "KEY:" <<it->key << endl << "INFO:" << it->info << endl << endl;
        ++it;
    }
}
