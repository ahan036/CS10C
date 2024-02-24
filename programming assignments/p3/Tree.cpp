#include "Node.h"
#include "Tree.h"
#include <iostream>

Tree::Tree() { 
    root = 0;
}

Tree::~Tree() { 
    delete remove(root);
}

Node *Tree::remove(Node *node) {
    if (node != nullptr) {
        delete remove(node->left);
        delete remove(node->middle);
        delete remove(node->right);
    }

    return node;
}

void Tree::remove(const string &str) {
    Node* searchNode = root;
    while (searchNode != nullptr) {
        // Compare small and (possibly) large
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str)) {
            break;
        }

        else { // Re-assign searchNode with possible children
            if (searchNode->small.compare(str) > 0) {
                // Go to the left
                searchNode = searchNode->left;
            }

            else {
                if (searchNode->hasTwoStrings() && searchNode->large.compare(str) < 0) {
                    // The string we're searching for is larger than both strings, go to right
                    searchNode = searchNode->right;
                }

                else {
                    // There is only one child or it's in-between two children, go to the middle (right)
                    searchNode = searchNode->middle;
                }
            }
        }
    }

    if (searchNode != nullptr) {
        if (searchNode->hasTwoStrings()) {
            if (str == searchNode->small) {
                searchNode->small = searchNode->large;
                searchNode->large = "";
            }

            else {
                searchNode->large = "";
            }
        }

        else {
            Node* parent = searchNode->parent;
            if (parent != nullptr) {
                if (str.compare(parent->small) < 0) {
                    parent->left = nullptr;
                    parent->large = parent->middle->small;
                    parent->middle = nullptr;
                } else {
                    parent->middle = nullptr;
                    parent->large = parent->small;
                    parent->small = parent->left->small;
                    parent->left = nullptr;
                }
            }

            else {
                Node* succNode = new Node();
                if (root->left != nullptr) {
                    succNode->small = root->left->small;
                    succNode->large = root->middle->small;
                    root = succNode;
                } 
                
                else {
                    root = nullptr;
                }
            }
        }
    }
}

void Tree::insert(const string &input) { 
    if (root == nullptr) { //base case for empty tree
        root = new Node();
        root -> small = input; 
    } else { 
        //will traverse down the tree until we reach the level of leafs
        Node* target = root;
        while (target -> left != nullptr) { 
            //first we get the order of the string relative to small and large to see where to insert the new node
            if (target -> hasTwoStrings()) { 
                if (target -> small.compare(input) > 0) { 
                    target = target -> left; 
                } else if (target -> large.compare(input) < 0) { 
                    target = target -> right;
                } else { 
                    target = target -> middle;
                }
            } else { 
                if (target -> small.compare(input) > 0) { 
                    target = target -> left;
                } else { 
                    target = target -> middle;
                }
            }
        }

        if (target -> hasTwoStrings()) { 
            string small; 
            string middle; 
            string large; 

            if (target -> small.compare(input) > 0) { 
                small = input; 
                middle = target -> small; 
                large = target -> large; 
            } else { 
                small = target -> small; 

                if (target -> large.compare(input) < 0) { 
                    middle = target -> large; 
                    large = input; 
                } else { 
                    middle = input; 
                    large = target -> large; 
                }
            }

            Node* smallNode = new Node();
            smallNode -> small = small;
            Node* largeNode = new Node();
            largeNode -> small = large;

            target -> small = middle;
            target -> large = ""; // assign empty
            target -> left = smallNode;
            target -> middle = largeNode;
            target -> right = nullptr; // might be redundant

            smallNode->parent = target;
            largeNode->parent = target;

            // shift to restore 2-3 properties
            shiftUp(target);
        } else { 
            // The node has 1 string in it, find if it should be inserted into the left or right
            if (target -> small.compare(input) > 0) {
                // Put input in the small area and bring small up to large
                target -> large = target -> small;
                target -> small = input;
            }

            else {
                // Put input in the large area
                target -> large = input;
            }
        }
    }
}

// shifts up node passed in accordingly 
void Tree::shiftUp(Node *node) {
    // The node provided in this function needs to be moved into its parent and ALWAYS has only 1 node
    // Therefore, if there is no parent, we shouldn't do anything
    // Only run if the parent is valid
    if (node->parent != nullptr) {
        Node* parent = node->parent;
        if (parent->hasTwoStrings()) { // This is our recursive case!
            // Three cases: the node's string is smaller, in the middle, or larger than the node's two strings
            if (parent->small.compare(node->small) > 0) { // Node is coming from the LEFT
                Node* newLarge = new Node();
                // newLarge takes the parent's middle and right children
                newLarge->left = parent->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                newLarge->small = parent->large;

                // Reset values of parent and insert the value from node
                parent->left = node; // The new small is the node itself, intact
                parent->middle = newLarge;
                parent->right = nullptr;
                // parent's small stays as parent's small
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newLarge's parent value up
                newLarge->parent = parent;
            }

            else if (parent->large.compare(node->small) < 0) { // Node is coming from the RIGHT
                Node* newSmall = new Node();
                // newSmall takes the parent's left and middle children
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = parent->middle;
                newSmall->middle->parent = newSmall;
                newSmall->small = parent->small;

                // Reset values of parent and insert the value from node
                parent->left = newSmall;
                parent->middle = node; // The new large is the node itself, intact
                parent->right = nullptr;
                parent->small = parent->large;
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newSmall's parent value up
                newSmall->parent = parent;
            }

            else { // Node is coming from the MIDDLE
                Node* newSmall = new Node();
                newSmall->small = parent->small;
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = node->left;
                newSmall->middle->parent = newSmall;

                Node* newLarge = new Node();
                newLarge->small = parent->large;
                newLarge->left = node->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->middle;
                newLarge->middle->parent = newLarge;

                // Reset values of parent and insert the value from node
                parent->left = newSmall;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->small = node->small;
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newSmall and newLarge's parent values up
                newSmall->parent = parent;
                newLarge->parent = parent;

                delete node; // Delete node as it is now unneeded
            }

            shiftUp(parent);
        }

        else { // Moving up into the same node, dealing with children (base case!)
            if (parent->small > node->small) { // node is coming from the left side
                parent->large = parent->small;
                parent->small = node->small;

                // Since the node's string is smaller, the node's left and middle are placed onto the parent's left and middle
                // The parent's middle is the remaining child that needs to be assigned onto the parent's right
                parent->left = node->left;
                parent->right = parent->middle;
                parent->middle = node->middle;
            }

            else { // node is coming from the middle (right)
                parent->large = node->small;

                // Since the node's string is larger, the node's left and middle are placed onto the parent's middle and right
                // The parent's left is the remaining child, and it doesn't need to be moved
                parent->middle = node->left;
                node->left->parent = parent;
                parent->right = node->middle;
                node->middle->parent = parent;
            }

            // Update both the parent pointers and delete the now useless node
            node->left->parent = parent;
            node->middle->parent = parent;
            delete node;
        }
    }
}


void Tree::preOrder() const {
    preOrder(root);
    cout << endl; 
}

void Tree::preOrder(Node *node) const {
    if (node != nullptr) {
        if (node -> hasTwoStrings()) {
            // SM LE LA MI RI
            cout << node -> small << ", ";
            preOrder(node -> left);
            cout << node -> large << ", ";
            preOrder(node -> middle);
            preOrder(node -> right);
        } else {
            cout << node -> small << ", ";
            preOrder(node -> left);
            preOrder(node -> middle);
        }
    }
}

void Tree::inOrder() const {
    inOrder(root);
    cout << endl; 
}

void Tree::inOrder(Node *node) const {
    if (node != nullptr) {
        inOrder(node -> left);
        cout << node -> small << ", ";
        inOrder(node -> middle);

        // There are two strings in the node
        if (node -> hasTwoStrings()) {
            cout << node -> large << ", ";
            inOrder(node -> right);
        }
    }
}

void Tree::postOrder() const {
    postOrder(root);
    cout << endl; 
}

void Tree::postOrder(Node *node) const {
    if (node != nullptr) {
        if (node -> hasTwoStrings()) {
            // LE MI SM RI LA
            postOrder(node -> left);
            postOrder(node -> middle);
            cout << node -> small << ", ";
            postOrder(node -> right);
            cout << node -> large << ", ";
        }

        else {
            postOrder(node -> left);
            postOrder(node -> middle);
            cout << node -> small << ", ";
        }
    }
} 