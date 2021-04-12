#include "ring.h"
#include "iterators.h"
#include <iostream>
using namespace std;

template <typename Key, typename Info>
Ring<Key, Info> shuffle(const Ring<Key, Info>& s1, int cnt1, const Ring<Key, Info>& s2, int cnt2, int rep){
    Ring<Key, Info> finalring;
    //empty
    if(s1.getSize() == 0 || s2.getSize() == 0)
        return finalring;

    typename Ring<Key, Info>::const_iterator it1;
    typename Ring<Key, Info>::const_iterator it2;
    it1 = s1.cbegin();
    it2 = s2.cbegin();

    for(int i = 0; i < rep; i++){
        for(int i1 = 0; i1 < cnt1; i1++){
            Key key1 = it1->key;
            Info info1 = it1->info;
            finalring.addEnd(typename Ring<Key, Info>::KeyInfoPair(key1, info1));
            ++it1;
        }
        for(int i2 = 0; i2 < cnt2; i2++){
            Key key2 = it2->key;
            Info info2 = it2->info;
            finalring.addEnd(typename Ring<Key, Info>::KeyInfoPair(key2, info2));
            ++it2;
        }
    }

    return finalring;
}

int main(){

    Ring<int, int> ring1;

    ring1.addEnd(Ring<int, int>::KeyInfoPair(1, 0));
    ring1.addEnd(Ring<int, int>::KeyInfoPair(2, 0));
    ring1.addEnd(Ring<int, int>::KeyInfoPair(3, 0));
    ring1.addEnd(Ring<int, int>::KeyInfoPair(4, 0));
    ring1.addEnd(Ring<int, int>::KeyInfoPair(5, 0));
    ring1.addEnd(Ring<int, int>::KeyInfoPair(6, 0));
    ring1.addEnd(Ring<int, int>::KeyInfoPair(7, 0));
    ring1.addEnd(Ring<int, int>::KeyInfoPair(8, 0));
    cout << "FIRST RING" << endl;
    //ring1.print();

    ring1.remove(Ring<int, int>::KeyInfoPair(1,0), 1);
    ring1.print();
}