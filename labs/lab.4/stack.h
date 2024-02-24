#ifndef STACK_H
#define STACK_H
#define MAX_SIZE 20

#include <iostream> 

using namespace std; 

template <typename T>
class stack { 
    private: 
    T data [MAX_SIZE]; //array will always be able to allocate 20 elements
    int size; //keeps track of how many elements are in the array

    public: 
    //constructs an empty stack
    stack() : size(0) {}

    //inserts new element into the stack, include overflow message no return 
    void push(T val);

    //removes last element from the data no return 
    void pop();

    //pops two elements from the stack no return 
    void pop_two();

    //returns top element in the stack (what was last pushed on)
    T top();

    //return whether stack is empty or not 
    bool empty(); 


};

#endif

template <typename T> 
void stack<T>::push(T val) { 
    if (size == 20) { //20 is the max so once it reaches 20 elements throw exception
        throw overflow_error ("Called push on full stack.");
    } else { 
        size++; //increment the size so that it shows there is 1 value 
        data[size] = val; //allocate element into array
    }
}

template <typename T> 
void stack<T>::pop() { 
    if (!empty()) { //if it is not empty then delete the val at the size
        size--; //deincrement to reflect the change 
    } else { 
        throw out_of_range ("Called pop on empty stack.");
    }
}

template <typename T> 
void stack<T>::pop_two() { 
    if(!empty() && size != 1) { 
        size--;
        size--;
    } else if (size == 1) {
        throw out_of_range("Called pop_two on a stack of size 1.");
    } else { 
        throw out_of_range("Called pop_two on empty stack.");
    }
}

template <typename T>
T stack<T>::top() { 
    if (!empty()) { 
        return data[size];
    } else { 
        throw underflow_error("Called top on empty stack.");
    }
}

template <typename T> 
bool stack<T>::empty() { 
    if (size != 0) { //if size is not 0 there is something in the stack 
        return false;
    } else { 
        return true; 
    }
}