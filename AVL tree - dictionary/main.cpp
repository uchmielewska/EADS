#include <iostream>
#include "dictionary.h"

using namespace std;

int main()
{
    //CONSTRUCTORS TEST
    {
        Dictionary<int, int> test;
        if(!test.is_empty())
            cerr << "default constructor error is_empty() == false\n";

        if(test.height())
            cerr << "default constructor error height() != 0\n";

        test.add(1, 1);
        Dictionary<int, int> test2(test);
        if(test2.is_empty())
            cerr << "copy constructor error is_empty() == true\n";

        if(test2.height())
            cerr << "copy constructor error height() != 1\n";
    }
    //no error message means that everything works properly :)

    //ADD METHOD TEST
    {
        Dictionary<int, int> test;
        test.add(1, 1);

        if(test.is_empty())
           cerr << "add method error is_empty() == true\n";
        if(test.height() != 0)
            cerr << "add method error height() != 0\n";
    }

    //FIND METHOD TEST
    {
        Dictionary<int, int> test;
        test.add(1, 1);

        if(!test.find(1))
            cerr << "find method error find(1) == false\n";
        if(!test.find(2)) //expected to obtain a message
            cerr << "Expected note, not an error: find(2) == false, no such node with key ==2\n";
    }

    //"operator=" TEST
    {
        cout<<"\nTesting operator= (tree should have nodes from 0 to 9):"<<endl<<endl;
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.add(i, i);

        Dictionary<int, int> test2;
        test2 = test;
        test2.print(cout);
    }

    //"Get_minimal_node" AND "Get_maximal_node" AND "get_info" METHODS TEST
    {
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.add(i, i);

        if(test.Get_maximal_node() != 9)
            cerr << "Get_maximal_node error returned != 9\n";
        if(test.Get_minimal_node() != 0)
            cerr << "Get_minimal_node error returned != 0\n";

        if(test.get_info(4) != 4)
            cerr << "get_info error\n";
    }

    //REMOVE METHOD TEST
    {
        cout<<"\nTesting remove method (there should be no node 3):"<<endl<<endl;
        Dictionary<int, int> test;
        test.add(1, 1);
        test.add(5, 1);
        test.add(8, 1);
        test.add(11, 1);
        test.add(2, 1);
        test.add(34, 1);
        test.add(0, 1);
        test.add(56, 1);
        test.add(10, 1);
        test.add(23, 1);
        test.add(3, 1);

        test.remove(3);
        test.print(cout);
        try{
            test.remove(3);
        }
        catch(Dictionary<int, int>::DictionaryException& ex){
            cout << ex.what() << '\n';
        }
    }

    //ITERATOR TEST
    {
        cout<<"\nTesting iterators:"<<endl<<endl;
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.add(i, i);
        test.print(cout);
        Dictionary<int, int>::Iterator it=test.ibegin();
        it.go_right();
        it.go_left();
        it.go_right();
        cout<<"Going: right left right, with iterator, and printing key and info: "<<it.show_key()<<"\t"<<it.show_info()<<endl;
    }

    //chmielewska
    return 0;
}
