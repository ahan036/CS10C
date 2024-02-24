#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std; 

class Node {  
    public: 
        string data; 
        int count; 
        int height;
        Node* left; 
        Node* right;
        Node* parent;  

        Node(string);
};


#endif