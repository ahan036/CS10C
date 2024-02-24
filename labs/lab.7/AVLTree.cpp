#include "AVLTree.h"
#include "Node.h"

#include <iostream> 

using namespace std; 

AVLTree::AVLTree() { 
    root = nullptr; 
}

void AVLTree::insert(const string &data) { 
    if (root == nullptr) { //if empty AVL tree
        root = new Node(data);
        return;
    }

    Node* par = InSearch(data, root);
    Node* child = new Node(data);
    child -> parent = par; 

    if (data.compare(par -> data) < 0) { //if data is less than parent insert to the left
        par -> left = child;

    } else if (data.compare(par -> data) > 0) { //if data is greater than parent then insert to the right
        par -> right = child; 
    } else { 
        return; //if they are the same do nothing quit insert
    }

    Node* curr = findUnbalancedNode(child); //rebalance tree
    if (curr != nullptr) { 
        rotate (curr);
    }

}

Node* AVLTree::InSearch(const string &val, Node* node) const {
    if (node->data == val) { //if we find a match
        return node;
    }
    if (val.compare(node->data) < 0) { //to the left of current node
        if (node->left != nullptr) { //if there is a left node
            return InSearch(val, node->left);
        }
        else { //otherwise parent found
            return node;
        }
    }
    else {
        if (node->right != nullptr) { //if there is a child to the right
            return InSearch(val, node->right);
        }
        return node; //parent found
    }
}

int AVLTree::balanceFactor(Node* curr) {
    if (curr == nullptr) { 
        return 0;
    }

    int leftHeight = findHeight(curr -> left); 
    int rightHeight = findHeight(curr -> right);

    return leftHeight - rightHeight; //balance factor is basically difference in height of a subtree 
}


int AVLTree::findHeight(Node* curr) const { 
    int total = 0; 

    if (curr != nullptr) { 
        int leftHeight = findHeight(curr -> left);
        int rightHeight = findHeight(curr -> right);

        if (leftHeight > rightHeight) { 
            total += leftHeight + 1;

        } else { 
            total += rightHeight + 1; 
        }
    }

    return total; 
}

Node* AVLTree::findUnbalancedNode(Node* curr) { 
    if (curr == nullptr) { 
        return 0; 
    }

    int balanced = 0; 
    balanced = balanceFactor(curr);

    if (balanced == -2 || balanced == 2) { 
        return curr;
    } else { 
        return findUnbalancedNode(curr -> parent);
    }
} 

void AVLTree::rotate(Node* node) { 
    while (findUnbalancedNode(node) != 0) {
            int bFactor = balanceFactor(node);
    int childBFactor1 = balanceFactor(node->left);
    int childBFactor2 = balanceFactor(node->right);
    if (bFactor == 2) { 
        if (childBFactor1 == 1 || childBFactor2 == 1) { 
            rotateRight(node); 
        }
        else {
            rotateLeft(node->left); 
            rotateRight(node); 
        }
    }
    else {
        if (childBFactor1 == -1 || childBFactor2 == -1) { 
            rotateLeft(node); 
        }
        else {
            rotateRight(node->right); 
            rotateLeft(node); 
        }
    }
	}
}

Node* AVLTree::rotateLeft(Node* node) { 
    Node* curr = nullptr;

    curr = node -> right;
    node -> right = curr -> left;

    if (node != root) {
        if (node -> parent -> left == node) {
            node -> parent -> left = curr;
        }

        if (node -> parent -> right == node) {
            node -> parent -> right = curr;
        }
    }

    curr -> parent = node -> parent;
    node -> parent = curr;
    curr -> left = node;

    if (node == root) {
        root = curr;
    }

    return curr;
}

Node* AVLTree::rotateRight(Node* node) { 
    Node* curr = nullptr;

    curr = node -> left;
    node -> left = curr -> right;

    if (node != root) {
        if (node -> parent -> left == node) {
            node -> parent -> left = curr ;
        }

        if (node -> parent -> right == node) {
            node -> parent -> right = curr;
        }
    }

    curr -> parent = node -> parent;
    node -> parent = curr;
    curr -> right = node;

    if (node == root) {
        root = curr;
    }

    return curr;
}

void AVLTree::printBalanceFactors() { 
    printBalanceFactors(root);
    cout << endl; 
}

void AVLTree:: printBalanceFactors(Node* curr) { 
    if (curr != nullptr) {
    printBalanceFactors(curr -> left);
    cout << curr -> data << "(" << balanceFactor(curr) << "), ";
    printBalanceFactors(curr -> right);
    }
}

//provided code 
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}