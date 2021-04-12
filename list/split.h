using namespace std;
#include <iostream>
#include "sequence.h"

template <typename Key, typename Info>
void Split(Sequence<Key, Info> &source, int start, 
                          Sequence<Key, Info> &result1, int step1, int rep1, 
                          Sequence<Key, Info> &result2, int step2, int rep2){

    if (source.IsEmpty()){
        return;
    }

    typename Sequence<Key, Info>::Element *temp = source.GetHead();
    
 
    int begin = 0;
    while(begin < start && temp != NULL){                       //setting starting node, from which function starts copying elements into 2 smaller lists
        temp = temp->next;
        ++begin;
    }

    int loop = 0;                       
    while(loop < rep1 && loop < rep2 && temp != NULL){          //1 case where nodes are copied into 2 lists
        for(int i = 0; i < step1; i++){
            result1.AddLast(temp->key, temp->info);
            if(temp->next != NULL)
                temp = temp->next;
            else
                return;
        }
        for(int i = 0; i<step2; i++){
            result2.AddLast(temp->key, temp->info);
            if(temp->next != NULL)
                temp = temp->next;
            else
                return;
        }
        ++loop;
    }
    while(loop <rep1 && loop >= rep2 && temp != NULL){          //2 case where nodes are copied only into the first list
        for(int i = 0; i < step1; i++){
            result1.AddLast(temp->key, temp->info);
            if(temp->next != NULL)
                temp = temp->next;
            else
                return;
        }
        ++loop;
    }
    while(loop <rep2 && loop >= rep1 && temp != NULL){          //3 case where nodes are copied only into the second list
        for(int i = 0; i < step2; i++){
            result2.AddLast(temp->key, temp->info);
            if(temp->next != NULL)
                temp = temp->next;
            else
                return;
        }
        ++loop;
    }
    return;
}
