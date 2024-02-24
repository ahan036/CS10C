#include <iostream>
#include "IntList.h"

using namespace std;

int main () {
    //test constructor and bool 
    cout << "My List:" << endl;
    IntList myList;
    cout << myList.empty() << endl;

    //add values into list 
    cout << "test: push_front" << endl;
    myList.push_front(20);
    myList.push_front(67);
    cout << myList.empty() << endl; 
    
    cout << "test: push_back" << endl;
    myList.push_back(105);
    myList.push_back(1);
    cout << "List originally: "; 
    cout << myList << endl;
    cout << "List in reverse: ";
    myList.printReverse();
    cout << endl; 

    //remove values from list 
    cout << "test: pop_front" << endl;
    myList.pop_front();
    cout << myList << endl; 

    cout << "test: pop_back" << endl; 
    myList.pop_back(); 

    cout << "List in reverse:";
    myList.printReverse(); 
    cout << endl; 

    //test bool with nodes inside 
    cout << myList.empty() << endl; 




    return 0;
}
