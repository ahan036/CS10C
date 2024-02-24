#include "IntList.h"
#include <iostream>

//must set dummyHead and tail pointers or else the list will not be connected 
IntList::IntList() { 
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead -> next = dummyTail;
    dummyTail -> prev = dummyHead; 
}

//pop back will remove all nodes until dummyHead -> next points to dummyTail (just like constructor)
IntList::~IntList() { 
    while (dummyHead -> next != dummyTail) {
        pop_back();
    }
}

//rewire all node !DO NOT FORGET TEMP PREV AND NEXT 
void IntList::push_front(int value) {
    IntNode *temp = new IntNode(value);
    IntNode * node = dummyHead->next;
    temp -> next = node; 
    node -> prev = temp; 
    dummyHead -> next = temp;
    temp -> prev = dummyHead;

}

//can only use when there is nodes between dummyHead and tail REMEMBER THIS 
void IntList::pop_front() { 
    if (!empty()) { 
        IntNode *temp = dummyHead -> next;  
        dummyHead -> next = temp -> next; 
        temp -> next -> prev = dummyHead;
        delete temp;
    }
}

void IntList::push_back(int value) { 
    IntNode *node = new IntNode(value);
    IntNode *temp = dummyTail -> prev; 
    temp -> next = node; 
    dummyTail -> prev = node; 
    node -> prev = temp; 
    node -> next = dummyTail;
}

// remove node infront of dummyTail, dont forget to repoint the prev and next pointers 
void IntList::pop_back() { 
    if (!empty()) { 
        IntNode *temp = dummyTail -> prev; 
        dummyTail -> prev = temp -> prev;
        temp -> prev -> next = dummyTail;

        delete temp;
    } 
}

bool IntList::empty() const { 
    if (dummyHead -> next == dummyTail) {
        return true;
    } else {
        return false;
    }

}

ostream & operator<<(ostream &out, const IntList &rhs) {
    if(!rhs.empty()){
        IntNode *curr = rhs.dummyHead -> next; 
        while (curr -> next != rhs.dummyTail) {
            out << curr -> data << " ";
            curr = curr -> next; 
        }

        out << curr -> data; 
    }
    return out; 
}

//start at tail -> prev to get last node in list and progress 
void IntList::printReverse() const { 
    if(!empty()) {
        IntNode *curr = dummyTail -> prev;

        while (curr -> prev != dummyHead) {
            cout << curr -> data << " ";
            curr = curr -> prev;
        }

        cout << curr -> data;
    }
}