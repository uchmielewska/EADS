#pragma once
#include <iomanip>
using namespace std;

template <typename Key, typename Info>
class Dictionary
{
    //private member types
    struct Node;
    Node *first;

public:

    class DictionaryException;
    class Iterator;

    //constructors
    Dictionary() : first(nullptr)
    {}
    Dictionary(const Dictionary& source){
        first = copy(source.first);
    }
    Dictionary(Dictionary&& source) : first(move(first)){
        source.first = nullptr;
    }

    //operator
    Dictionary& operator=(const Dictionary& rhs);
    Dictionary& operator=(Dictionary&& rhs);

    //capacity
    bool is_empty() const{
        return first == nullptr;
    }

    //if first == NULL, 1.condition goes, if not 2. condition goes
    int height() const{
        return first ? first->height : 0;
    }

    //element access
    Key& Get_maximal_node(){
        return Get_maximal_node(first);
    }
    const Key& Get_maximal_node() const{
        return Get_maximal_node(first);
    }
    Key& Get_minimal_node(){
        return Get_minimal_node(first);
    }
    const Key& Get_minimal_node() const{
        return Get_minimal_node(first);
    }
    Info& get_info(const Key& key){
        return get_node(key, first)->info;
    }
    const Info& get_info(const Key& key) const{
        return get_node(key, first)->info;
    }

    //modifiers
    void add(const Key& new_Key, const Info& new_info);
    void clear();
    void remove(const Key& key);

    //operations
    void print(ostream& os) const{
        print_graph(os, 0, first);
    }
    bool find(const Key& key) const{
        return find(key, first);
    }

    //Iterator
        Iterator ibegin() const
        {
            Iterator it(first);
            return it;
        }
        const Iterator const_ibegin() const
        {
            Iterator it(first);
            return it;
        }


    ~Dictionary(){
        clear(first);
    }

private:
    //element access
    Key& Get_maximal_node(Node *start) const
    {
        if(!start->right)
        return start->key;

        return Get_maximal_node(start->right);
    };
    Key& Get_minimal_node(Node *start) const
    {
        if(!start->left)
        return start->key;

        return Get_minimal_node(start->left);
    }
    Node* get_node(const Key& key, Node *start) const;

    //modifiers
    Node* add(const Key& key, const Info& info, Node *start);
    Node* remove(const Key& key, Node* start);

    //updating nodes and tree functions
    void update(Node *node);
    Node* balance(Node *node);

    //rotations performed on tree
    Node* llrotation(Node *node); //left-left rotation
    Node* lrrotation(Node *node); //left-right rotation
    Node* rrrotation(Node *node); //right-right rotation
    Node* rlrotation(Node *node); //right-left rotation

    //single rotations
    Node* lrotation(Node *node); //left rotation
    Node* rrotation(Node *node); //right rotation

    //print function
    void print_graph(ostream& os, int width, Node *start) const;

    //more functions
    bool find(const Key& key, Node *start) const;
    Node* copy(Node *start);
    void clear(Node *start);
};

template <typename Key, typename Info>
class Dictionary<Key, Info>::Iterator
{
    friend class Dictionary<Key, Info>;
    private:
        Node *current;

    public:
        Iterator():current(nullptr){};
        ~Iterator(){
            current=nullptr;
        };
        Iterator(const Iterator& other)
        {
            this->current=other.current;
        };

        Iterator& operator=(const Iterator& other)
        {
            this->current=other.current;
            return *this;
        }
        bool operator==(const Iterator& source) const
        {
            if(this->current==source.current) return true;
            return false;
        }
        bool operator!=(const Iterator& source) const
        {
            return !(*this==source);
        }

        bool go_left()      //goes left and returns true if current is not null; otherwise does nothing and returns false
        {
            if(!current) return false;
            current=current->left;
            return true;
        }

        bool go_right()     //goes right and returns true if current is not null; otherwise does nothing and returns false
        {
            if(!current) return false;
            current=current->right;
            return true;
        }

        Key &show_key()
        {
            if(current) return current->key;
            //iterator is empty
            throw range_error( "Iterator is empty, cannot return key." );
        }

        Info &show_info()
        {
            if(current) return current->info;
            //iterator is empty
            throw range_error( "Iterator is empty, cannot return info." );
        }

        const Key &show_key() const
        {
            if(current) return current->key;
            //iterator is empty
            throw range_error( "Iterator is empty, cannot return key." );
        }

        const Info &show_info() const
        {
            if(current) return current->info;
            //iterator is empty
            throw range_error( "Iterator is empty, cannot return info." );
        }

        private:
        Iterator(Node *ptr):current(ptr){};
};

template <typename Key, typename Info>
struct Dictionary<Key, Info>::Node
{
    Key key;
    Info info;

    int bf;
    int height;
    Node *left;
    Node *right;
};

template <typename Key, typename Info>
class Dictionary<Key, Info>::DictionaryException : invalid_argument //exception class
{
    public :
        using invalid_argument::invalid_argument;
        using invalid_argument::what;
};

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(const Dictionary<Key, Info>& previous){
    clear();
    first = copy(previous.first);
    return *this;
}

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(Dictionary<Key, Info>&& previous){
    clear();
    first = move(previous.first);
    previous.first = nullptr;
    return *this;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::add(const Key& new_key, const Info& new_info){
    if(find(new_key, first))
        throw DictionaryException("Dictionary add : key already exists");

    first = add(new_key, new_info, first);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clear(){
    clear(first);
    first = nullptr;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::remove(const Key& key){
    if(!find(key))
        throw DictionaryException("Dictionary remove : key does not exist");

    first = remove(key, first);
}

//more functions

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::get_node(const Key& key, Node *start) const{
    if(!start)
        throw DictionaryException("Node with a given key does not exist");

    if(key > start->key)
        return get_node(key, start->right);
    else if(key < start->key)
        return get_node(key, start->left);

    return start;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::add(const Key& key, const Info& info, Node *start){
    if(!start)
        return new Node{key, info, 0, 0, nullptr, nullptr};

    if(key > start->key)
        start->right = add(key, info, start->right);
    else if(key < start->key)
        start->left = add(key, info, start->left);

    update(start);
    return balance(start);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clear(Node *start){
    if(!start)
        return;
    clear(start->left);
    clear(start->right);
    delete start;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::remove(const Key& key, Node* start){
    if(!start)
        return nullptr;

    if(key < start->key)
        start->left = remove(key, start->left);
    else if(key > start->key)
        start->right = remove(key, start->right);
    else{
        if(!start->left)
            return start->right;
        else if(!start->right)
            return start->left;
        else{
            if(start->left->height > start->right->height){
                Node *replace = get_node(Get_maximal_node(start->left), start->left);
                start->info = replace->info;
                start->key = replace->key;

                start->left = remove(replace->key, start->left);
                delete replace;
            }
            else{
                Node *replace = get_node(Get_minimal_node(start->right), start->right);
                start->info = replace->info;
                start->key = replace->key;

                start->right = remove(replace->key, start->right);
                delete replace;
            }
        }
    }
    update(start);
    return balance(start);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::update(Node *node){
    int left_height = node->left ? node->left->height : -1;
    int right_height = node->right ? node->right->height : -1;

    node->height = left_height > right_height ? 1 + left_height : 1 + right_height;
    node->bf = right_height - left_height;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::balance(Node *node){
    if(node->bf < -1){
        //left left
        if(node->left->bf <= 0)
            return llrotation(node);
        else    //left right
            return lrrotation(node);
    }
    else if(node->bf > 1){
        //right right
        if(node->right->bf >= 0)
            return rrrotation(node);
        else    //right left
            return rlrotation(node);
    }
    //balanced
    return node;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::llrotation(Node *node){
    return rrotation(node);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lrrotation(Node *node){
    node->left = lrotation(node->left);
    return rrotation(node);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rrrotation(Node *node){
    return lrotation(node);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rlrotation(Node *node){
    node->right = rrotation(node->right);
    return lrotation(node);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lrotation(Node *node){
    Node *new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rrotation(Node *node){
    Node *new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::print_graph(ostream& os, int width, Node *start) const{
    if(start){
        if(start->right)
            print_graph(os, width + 8, start->right);
        if(width > 0)
            os << setw(width) << ' ';
        if(start->right)
            os << '\n' << setw(width) << ' ';

        os << '[' << start->key << ',' << start->info << "]\n";
        if(start->left) {
            os << setw(width) << ' ' << "\n";
            print_graph(os, width + 8, start->left);
        }
    }
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::find(const Key& key, Node *start) const{
    if(!start)
        return false;

    if(key > start->key)
        return find(key, start->right);
    else if(key < start->key)
        return find(key, start->left);
    else
        return true;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::copy(Node *start){
    Node *copied = nullptr;
    if(start){
        copied = new Node{start->key, start->info, start->bf, start->height, nullptr, nullptr};
        copied->left = copy(start->left);
        copied->right = copy(start->right);
    }
    return copied;
}

//chmielewska
