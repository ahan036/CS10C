#include "Node.h"
#include <iostream>
#include <string>

using namespace std; 

Node::Node(string newData) { 
    data = newData; 
    left = nullptr;
    right = nullptr;
    count = 0;
    height = 0; 
    parent = nullptr;
}