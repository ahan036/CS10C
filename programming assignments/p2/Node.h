#ifndef NODE_H
#define NODE_H

#include <iostream> 
#include <string> 

using namespace std; 

class Node { 
    friend class BSTree;
    public:
    Node(string);
    private: 
    string data; 
    int count; 
    Node* right; 
    Node* left; 
};

#endif