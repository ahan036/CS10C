#include "BSTree.h"

using namespace std; 


BSTree::BSTree() { 
    root = nullptr;  
}

BSTree::~BSTree() { 
    delete root; 
}

//print functions
void BSTree::preOrder(Node* curr) const { 
    if (curr != nullptr) { 
        cout << curr -> data << "(" << curr -> count << ")" << ", ";
        preOrder(curr -> left); //will print all the left until curr = null 
        preOrder(curr -> right); //then it will move here 
    }
}
void BSTree::preOrder() const { 
    preOrder(root);
    cout << endl; 
}

void BSTree::postOrder(Node* curr) const { 
    if (curr != nullptr) { 
        postOrder(curr -> left);
        postOrder (curr -> right);
        cout << curr -> data << "(" << curr -> count << ")" << ", ";
    }
}

void BSTree::postOrder() const { 
    postOrder(root);
    cout << endl;
}

void BSTree::inOrder(Node *curr) const { 
    if (curr != nullptr) { 
        inOrder(curr -> left); //move to left 
        cout << curr -> data << "(" << curr -> count << ")" << ", ";
        inOrder(curr -> right); //recursive call move to right 
    }

}

void BSTree::inOrder() const {
    inOrder(root);
    cout << endl;
}

// other functions 
// how would i make this recursie? helper function? 
void BSTree::insert(Node* node, const string &newString) { 
    Node* curr = node; //curr is used to track where we are
    Node* newNode = new Node(newString); 

    if (root == nullptr) { //case for empty tree
        root = newNode;
    } else if (newNode -> data < curr -> data) { //case to fill to the left if the node is smaller than root 
        if (curr -> left == nullptr) { //if left of curr is empty fill the node
            curr -> left = newNode; 
        } else { 
            //curr -> left = node -> left; 
            insert(node -> left, newString); //if not move to the left 
        }
    } else if (newNode -> data > curr -> data) { //if new node is greater than root or parent  
        if (curr -> right == nullptr) { //if right of curr is empty fill the node 
            curr -> right = newNode;
        } else {
            //curr -> right = node -> right;
            insert(node -> right, newString); //if not move down to the right 
            
        }
    } else if (newNode -> data == curr -> data) { //if new node is the same as parent 
        curr -> count = curr -> count + 1; //increase node count by 1
    }
}
void BSTree::insert(const string &newString) { 
    insert(root, newString);
}
bool BSTree::search(const string &key) const { 
    Node* curr = root; 

    while (curr && !(curr -> data == key)) { //move curr and repeat until curr is = key 
        if (curr -> data > key) { 
            curr = curr -> left;
        } else if (curr -> data < key) { 
            curr = curr -> right;
        }
    }

    return curr != nullptr; 
}

string BSTree::largest() const { 
//bs tree means the largest value is the right most value
    Node* curr = root;
    if (root == nullptr) { 
        return ""; 
    } else { 
       curr = findMax(root);
    }
    return curr -> data; 
}

Node* BSTree::findMax(Node *curr)const { //largest within subtree
    Node *max = curr;

    while(curr != nullptr) {
        max = curr;
        curr = curr -> right;
    }
    return max;
}

string BSTree::smallest() const { 
//bs tree means the smallest value is the left most value
    Node* curr = root; 
    if (root == nullptr) {
        return "";
    } else if (root != nullptr) { 
         while (curr -> left != nullptr) { 
            curr = curr -> left;
        }
    }

    return curr -> data;
}

Node* BSTree::findMin(Node *curr)const { //smallest within the subtree
    Node *min = curr;

    while(curr != nullptr) {
        min = curr;
        curr = curr -> left;
    }

    return min;
}

int BSTree::height(const string& key) const { 
    if(!search(key)) { // base case 
        return -1;
    }

    Node *curr = root;
    while(curr != nullptr && curr -> data != key) { 
        if(curr -> data > key) {
            curr = curr -> right;
        } else {
            curr = curr -> right;
        }
    }

    Node *currLhs = curr;
    Node *currRhs = curr;
    int leftCnt = 0;
    int rightCnt = 0;
    
    if(curr -> left) { 
        currLhs = currLhs -> left;
        ++leftCnt; 
        leftCnt += height(currLhs -> data); 
    }

    if(curr -> right) { 
        currRhs = currRhs -> right;
        ++rightCnt; 
        rightCnt += height(currRhs -> data); 
    }

    if(leftCnt >= rightCnt) { 
        return leftCnt;
    }

    return rightCnt;
}

//remove function 
void BSTree::remove(const string &key) {
    remove (root, key);
}

Node* BSTree::remove(Node* node, const string &key) { 
    if (node == nullptr) {
        return 0;
    }

    else if(key < node -> data) {
        node -> left = remove(node -> left, key);
    }

    else if(key > node->data) {
        node -> right = remove(node -> right, key);
    }

    else {
        if(node -> count > 1) {
            node -> count = node -> count - 1;
        } 

        else if(node -> left == nullptr && node -> right == nullptr) {
            if (root == node) {
              return root = nullptr;
            }

            delete node;
            return 0;
        } 

        else if(node -> left == nullptr) {
            Node *curr = findMin(node -> right);
            node -> data = curr -> data;
            node -> count = curr -> count;
            curr -> count = 0;

            node -> right = remove(node -> right, curr -> data);

            return node;
        } 

        else if (node -> right == nullptr) {
            Node *curr = findMax(node -> left);
            node -> data = curr -> data;
            node -> count = curr -> count;
            curr -> count = 0;

            node -> left = remove(node -> left, curr -> data);

            return node;
        }

        else {
          Node *curr = findMax(node -> left);
          node -> data = curr -> data;
          node -> count = curr -> count;
          curr -> count = 1;
          node -> left = remove(node -> left, curr -> data);
        }
    }

    return node;
}



// im not sure why this remove function i made isnt working i didnt do the deincrements YET but even when i
// add only one node when i try to remove it doesnt work so i gave up and just redid it :( 

// void BSTree::remove(const string &key) { 
//     remove(root, key);
// }



// Node* BSTree::remove(Node* node, const string &key) { //node cannot be const since we will be changing it 
//     Node* curr = nullptr;
//     if (node == nullptr) { 
//         return root; 
//     } else if (key < node -> data) { 
//         node -> left = remove(node -> left, key);
//     } else if (key > node -> data) { 
//         node -> right = remove (node -> right, key);
//     } else if (node -> right && node -> left) { 
//         curr = findMin(node -> right);
//         node -> data = curr -> data;
//         node -> right = remove(node -> right, node -> data);
//     } else { 
//         curr = node; 
//         if (node -> left == nullptr) { 
//             node = node -> right;
//         } else if (node -> right == nullptr) { 
//             node = node -> left;
//         }

//         delete curr; 
//     }

//     return node; 
// }