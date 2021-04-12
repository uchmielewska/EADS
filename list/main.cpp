#include "split.h"

int main(){
    system("clear");

    cout << "====================== ADD TEST =====================" << endl << endl; 

    Sequence<int, const char*> list;
    list.AddFirst(1, "4");
    list.AddLast(2, "4");
    list.AddLast(4, "5");
    list.AddLast(4, "6");
    list.AddLast(6, "7");
    list.AddAfter(6, "8", 2, 1);
    list.AddAfter(7, "9", 2, 2);                //there is no such element after which it should be added 
    list.AddAfter(7, "9", 3, 2);                //there is no such element after which it should be added

    list.Print();

    Sequence<int, const char*> list22(list);
    cout << "====================== COPY CONSTRUCTOR TEST =====================" << endl << endl; 
    list22.Print();

    cout << "==================== REMOVE TEST ====================" << endl << endl;

    list.RemoveFirst();
    list.RemoveLast();
    list.Remove(4 , 2);                         //proper element to delete
    list.Remove(200, 1);                        //no such element - nothing happens
    list.Print();

    cout << "=================== OPERATORS TEST ===================" << endl << endl;

    Sequence<int, const char*> list1;
    list1.AddLast(6, "4");
    list1.AddLast(9, "5");
    list1.AddLast(2, "6");

    cout << "===COMPARISON OPERATOR====" << endl << endl;
    list1 == list;

    cout << "===NOT EQUAL OPERATOR====" << endl << endl;
    list1 != list;

    cout << "===ASSIGNMENT OPERATOR====" << endl << endl;
    list1 = list;
    cout << "FIRST LIST" << endl << endl;  
    list1.Print();
    cout << "SECOND LIST" << endl << endl;
    list.Print();

    cout << "============== SPLIT FUNCTIONS TEST (main seq short) ==============" << endl << endl;
    list.AddFirst(7, "4");
    list.AddLast(2, "4");
    list.AddLast(9, "5");
    list.AddLast(10, "6");
    list.AddFirst(66, "4");
    list.AddLast(2, "1");
    list.AddLast(99, "2");
    list.AddLast(15, "20");
    Sequence<int, const char*> list2;
    Sequence<int, const char*> list3;

    Split(list, 8, list2, 2, 3, list3, 3, 1);


    cout << "========================== 1 LIST ============================" << endl << endl;
    list2.Print();
    cout << "========================== 2 LIST ============================" << endl << endl;
    list3.Print();

    list2.Clear();
    list3.Clear();

    cout << "============== SPLIT FUNCTIONS TEST (main seq long) ==============" << endl << endl;
    Split(list, 1, list2, 2, 3, list3, 3, 1);

    cout << "========================== 1 LIST ============================" << endl << endl;
    list2.Print();
    cout << "========================== 2 LIST ============================" << endl << endl;
    list3.Print();

    return 0;
}
