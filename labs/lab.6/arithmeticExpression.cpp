#include <iostream> 
#include <ostream> 
#include <stack>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "arithmeticExpression.h"
using namespace std; 

arithmeticExpression::arithmeticExpression(const string &val) { 
    root = 0; 
    infixExpression = val;
}

void arithmeticExpression::buildTree() { 
    infixExpression = infix_to_postfix();
    stack <TreeNode*> tree; //create a stack
    
    for (unsigned i = 0; i < infixExpression.length(); i++) { 
        TreeNode* node = new TreeNode(infixExpression.at(i), 'a' + i);
        if (priority(infixExpression.at(i)) == 0) { 
            tree.push(node);
        } else { 
            node -> right = tree.top();
            tree.pop();
            node -> left = tree.top();
            tree.pop();
            tree.push(node);
        }
    }
    root = tree.top();
}

void arithmeticExpression::infix() { 
    infix(root);
}

void arithmeticExpression::infix(TreeNode *curr) { 
    if (curr != nullptr) {
        if (curr -> left != nullptr) {
            cout << '(';
        }
        
        //recursive calls to go through the left and right side of the tree. 
        infix(curr -> left);
        cout << curr -> data;
        infix(curr -> right);

        if (curr -> left != nullptr) {
            cout << ')';
        }
    }
}

void arithmeticExpression::prefix() { 
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode *curr){ 
    if (curr -> left != 0 && curr -> right != 0) { 
        cout << curr -> data;
        prefix(curr -> left);
        prefix (curr -> right); 
    } else { 
        cout << curr -> data;
    }
}

void arithmeticExpression::postfix() { 
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode *curr) { 
    if (curr -> left != 0 && curr -> right != 0) { 
        postfix(curr -> left);
        postfix(curr -> right);
        cout << curr -> data;
    } else { 
        cout << curr -> data; 
    }

}

void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode *curr) { 
    outFS << curr -> key << "[ label =" << "\"" << curr -> data << "\" ]" << endl;

    if (curr -> left != 0) { 
        outFS << curr -> key << "->" << curr -> left -> key << "[ label = \"" << curr -> left -> data << "\"]" << endl;
        visualizeTree(outFS, curr -> left);
    } 

    if (curr -> right != 0) { 
        outFS << curr -> key << " -> " << curr -> right -> key << "[ label = \"" << curr -> right -> data << "\"]" << endl;
        visualizeTree(outFS, curr -> right);
    }

    outFS << endl;
}


//provided code

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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