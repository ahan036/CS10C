#include "Node.h"

Node::Node() { 
    left = nullptr;
    right = nullptr;
    middle = nullptr; 
    parent = nullptr;
}

bool Node::hasTwoStrings() const { 
    if (!large.empty()) { 
        return true;
    } else { 
        return false; 
    }
}