#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void preOrder(Node*) const; 
  void inOrder(Node*) const; 
  void postOrder(Node*) const; 

  Node* remove(Node*);
  //shift nodes up to follow 2-3 tree rules
  void shiftUp(Node*);
    
};

#endif