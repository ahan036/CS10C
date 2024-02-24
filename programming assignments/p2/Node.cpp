#include "Node.h"

Node::Node(string newData) { 
    data = newData;
    count = 1; 
    left = nullptr;
    right = nullptr; 
}