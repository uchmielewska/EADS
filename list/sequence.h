using namespace std;
#include <iostream>

template <typename Key, typename Info>
class Sequence{

    public:
        struct Element{
            Key key;
            Info info;
            Element *next;

            Element(const Key &key, const Info &info);                                          //element constructor
        };

    private:
        Element *head;
        int size;
    
    public:
    
        Sequence();                                                                             //sequence constructor
        ~Sequence();                                                                            //sequence destructor
        Sequence(const Sequence<Key, Info> &other);                                             //copy constructor

        Sequence<Key, Info> &operator=(const Sequence<Key, Info> &other);                       //operator of assignment
        bool operator==(const Sequence<Key, Info> &other);                                      //compares if two lists are equal to each other
        bool operator!=(const Sequence<Key, Info> &other);                                      //compares if two lists are different from each other 

        int Size();                                                                             //returns number of nodes of the list
        bool IsEmpty();                                                                         //checks if the list is empty
        bool Clear();                                                                           //deletes all elements
        void Print();                                                                           //displays all elements od the list
        Element *GetHead();                                                                     //returns head                                                    

        void AddFirst(const Key &key, const Info &info);                                        //adds an element on the top of the list                               
        bool AddAfter(const Key &key, const Info &info, const Key &after, int occurance);       //adds an element behins selected node
        void AddLast(const Key &key, const Info &info);                                         //adds an element to the end of the list

        bool RemoveFirst();                                                                     //removes an element from the top of the list
        bool RemoveLast();                                                                      //removes an element from the end of the list
        bool Remove(const Key &key, int occurance);                                             //removes an element from the middle
};

// CONSTRUCTORS AND DESTRUCTOR

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(){
    head = NULL;
    size = 0;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence(){
    Clear();
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info> &other){
        head = NULL;
        size = 0;
        *this = other;
}

template <typename Key, typename Info>
Sequence<Key, Info>::Element::Element(const Key &key, const Info &info){
    this->key = key;
    this->info = info;
}

//OPERATORS

template <typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator=(const Sequence<Key, Info> &other)
{
    Clear();
    
    Element *temp = other.head;
    while (temp != NULL){
        AddLast(temp->key, temp->info);
        temp = temp->next;
    }
    return *this;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info> &other)
{
    if (size != other.size)
        return false;

    Element *tempOther = other.head;
    Element *tempThis = head;
    while(tempThis != NULL){
        if ((tempThis->key != tempOther->key) || (tempThis->info != tempOther->info)){
            return false;
        }
        tempThis = tempThis->next;
        tempOther = tempOther->next;
    }

    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::operator!=(const Sequence<Key, Info> &other)
{
    return !operator==(other);
}

//OTHER METHODS

template<typename Key, typename Info>
int Sequence<Key, Info>::Size(){
    return size;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::IsEmpty(){
    if(size == 0)
        return true;
    else
        return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::Clear(){
    if(IsEmpty())
        return false;
    else{
        int iterations = size;
        for(int i = 0; i < iterations; i++){
                RemoveFirst();
        }
        return true;
    }
}

template<typename Key, typename Info>
void Sequence<Key, Info>::Print(){
    if(IsEmpty())
        cout << "The list is empty" <<endl;
    else{
        Element *temp = head;
        for(int i = 0; i < size; i++){
            cout << "KEY: " << temp->key << endl << "INFO: " << temp->info << endl << endl;
            temp = temp->next;
        }
    }
}

template<typename Key, typename Info>
typename Sequence<Key, Info>::Element *Sequence<Key, Info>::GetHead(){
    return head;
}

// ADD METHODS

template<typename Key, typename Info>
void Sequence<Key, Info>::AddFirst(const Key &key, const Info &info){
    if (head == NULL)
    {
        head = new Element(key, info);
        head->next = NULL;
        size++;
    }
    else
    {
        Element *temp = new Element(key, info);
        temp->next = head;
        head = temp;
        size++;
    }
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::AddAfter(const Key &key, const Info &info, const Key &after, int occurance){
    int counter = 0;
    Element *find = head;
    for(int i = 0; i < size; i++){
        if(after == find->key){
            counter++;
            if(occurance == counter){
                Element *temp = new Element(key, info);
                temp->next = find->next;
                find->next = temp;
                size++;
                return true;
            }
        }
        find = find->next;
    }
    return false;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::AddLast(const Key &key, const Info &info){

    if(head == NULL){
        head = new Element(key, info);
        head->next = NULL;
        size++;
    }
    else{
        Element *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new Element(key, info);
        temp->next->next = NULL;
        size++;
    }
}

// REMOVE METHODS

template<typename Key, typename Info>
bool Sequence<Key, Info>::RemoveFirst(){
    if (IsEmpty())
        return false;

    Element *temp = head;
    head = head->next;
    delete temp;
    size--;
    return true;
}


template <typename Key, typename Info>
bool Sequence<Key, Info>::Remove(const Key &key, int occurance){
    int counter = 0;
    Element *temp = head;
    Element *previous = NULL;
    for(int i = 0; i < size; i++){
        if(key == temp->key){
            counter++;
            if(occurance == counter){
                if(key == head->key && key == temp->key){
                    RemoveFirst();
                    return true;
                }
                else if(temp->next == NULL && key == temp->key){
                    RemoveLast();
                    return true;
                }
                else{
                    previous->next = temp->next;
                    delete temp;
                    size--;
                    return true;
                }
            }
            
        }
        previous = temp;
        temp = temp->next;
    }
    return false;
}


template <typename Key, typename Info>
bool Sequence<Key, Info>::RemoveLast(){
    if(IsEmpty()){
        return false;
    }
    else{
        Element *temp = head;
        while(temp->next->next != NULL){
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
        size--;
        return true;
    }
}
