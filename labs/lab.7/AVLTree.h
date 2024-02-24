#pragma once 
#include "Node.h"

#include <iostream> 
#include <string> 
#include <fstream>

using namespace std; 

class AVLTree { 
    public: 

    AVLTree();
    
    //insert an item to the binary search tree and perform rotation when needed
    void insert(const string &);

    //return the balance factor of a node 
    int balanceFactor(Node*);

    //traverse and print the tree in inorder notation, printing the string followed by balance factor in paraentheses followed by a , and space 
    void printBalanceFactors();

    //generate fotty file and visualize tree call this function before and after rotation
    void visualizeTree(const string &);
    
    Node *InSearch(const string &, Node*) const;

    private: 
    Node* root; 
    int findHeight (Node*) const; 

    //find and return the closeset unbalanced node (w/ balance factor of 2 or -2) to the inserted node 
    Node*  findUnbalancedNode(Node* ); 

    //implement 4 possible imbalance cases and update the parent for the given node 
    void rotate(Node*);

    //rotate subtree to the left at the given node and returns the new subroot 
    Node* rotateLeft(Node*); 

    //rotate the subtree to the right 
    Node* rotateRight(Node*); 


    //helper function for public functions 
    void printBalanceFactors(Node *);

    void visualizeTree(ofstream &, Node *);
    
};