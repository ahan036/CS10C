#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

//constructor, creates new node with a string inside aka name 
Node* newNode(string payload) {
    Node* createNode = new Node;
    //newNode -> next == nullptr; 
    createNode -> payload = payload; 
    
    return createNode; //return type is of Node do you must return a node
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) { //this creates the circular list 
        name = names.at(i);
        if (head == nullptr) { //if the list is empty...
            head = newNode(name); // initialize head specially
            prev = head; 
        } else { //if there is already a head...
            prev->next = newNode(name);
            prev = prev-> next; 
        }
    }

    if (prev != nullptr) { //not empty list... 
        /** fill in this code **/ // make circular
        prev -> next = head; 
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) { //once the current node reaches the start we exit 
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr -> next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
            prev = curr; 
            curr = curr -> next;

        }

        prev -> next = curr -> next; // delete kth node
        delete curr;
        curr = prev -> next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

