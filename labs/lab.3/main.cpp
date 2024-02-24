#include <iostream> 
#include <cstdlib>
#include <string> 
#include <stdexcept>
#include <vector> 

using namespace std; 

//find the minimum val or string inside the vector 
template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned min = 0; 
    for (unsigned int i = index; i < vals; i++) { 
        if (vals.at(i) < min) { 
            min = vals.at(i);
        }
    }
    return min; 
}

//selection sort algo from zybooks
template <typename T>
void selection_sort (vector<T> &vals) { 
    int start = 0; //reset this variable or else it wont work!!!! 
    for (int i = vals.size() - 1; i > 0; i--) { 
        start = 0;
        for (int j = 1; j <= i; j++) { 
            if (vals.at(j) > vals.at(start)) { 
                start = j;
            }
        }
        swap (vals.at(start), vals.at(i));
    }
}

//get the item in the vector, throw out of range if index > vector size
template <typename T>
T getElement(vector<T> vals, int index) { 
    unsigned idx = index;
    if (idx >= vals.size()) { 
        throw out_of_range("out of range exception occured");
    } else { 
        return vals.at(index);
    }
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main() { 
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0) {
        cout << "Enter a number: " << endl;
        cin >> index;
        curChar = getElement(vals,index);
        cout << "Element located at " << index << ": is " << curChar << endl;
    }

    return 0; 
}
