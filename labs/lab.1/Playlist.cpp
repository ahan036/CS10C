#include "Playlist.h"

#include <string>
#include <iostream>


using namespace std;

//define in .h file 
PlaylistNode::PlaylistNode(string ID, string song, string artist, int length) { 
    uniqueID = ID;
    artistName = artist;
    songName = song;
    songLength = length;
    nextNodePtr = nullptr;
}

//append basically, check zybooks if stuck 
void PlaylistNode::InsertAfter(PlaylistNode *node) { 
    PlaylistNode *prev = nullptr;

    prev = this -> nextNodePtr;
    this -> nextNodePtr = node; 
    node -> nextNodePtr = prev;  
}


void PlaylistNode::PrintPlaylistNode() { 
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}


//playlist class functions 

void Playlist::add(PlaylistNode* currSong) { 
    if (head == nullptr) { //empty list
        head = currSong;
        tail = currSong;
    } else if (head != nullptr && head -> GetNext() == nullptr) { //for only 1 node in the list
        head -> SetNext(currSong);
        tail = currSong; 
    } else { 
        tail -> SetNext(currSong); //for every other case
        tail = currSong; 
    }
}

void Playlist::remove(string songID) {
    PlaylistNode* prev = nullptr; //the node in front of our current 
    PlaylistNode* curr = head;  
    string songName = " "; 

    if (head == nullptr) { 
        cout << "Playlist is empty" << endl; //zybooks doesnt test for this case 
    } else if (head -> GetID() == songID) { //if you remove head node 
        songName = head ->GetSongName(); //dont forget to get the song name BEFORE switching nodes around, this had me stuck 
        curr = head -> GetNext(); 
        head = curr;  
        delete head; //dont forget to delete the data !!!
        cout << '"' << songName << '"' << " removed." << endl << endl;  
    } else {
        while (curr -> GetNext() != nullptr && curr -> GetID() != songID) {  //works if node is not head nor tail 
            prev = curr; //increment it so that prev is always one behind curr 
            curr = curr -> GetNext(); 
        }

        if (curr == tail) { //once while loop breaks meaning, it has traversed through the list to the point it has found the song, it will check whether its tail or not and then remove accordingly
            songName = tail -> GetSongName();
            tail = prev; 
            tail -> SetNext(nullptr); //no dangling pointers
            delete curr; 
            cout << '"' << songName << '"' << " removed." << endl << endl;
        } else { 
            songName = curr ->GetSongName();
            prev -> SetNext(curr -> GetNext()); 
            delete curr; 
            cout << '"' << songName << '"' << " removed." << endl << endl;
        }   
    }
}
 
//im sorry but i give up im so confused
void Playlist::changePosition(int currPos, int newPos) const {
    PlaylistNode* current = nullptr; 
    int cnt = 1;

    for(current = head; cnt != currPos; current = current ->GetNext()) { //once cnt matches we will move the node

    }

    cout << '"' << current -> GetSongName() << '"' << " moved to position " << newPos;


}

void Playlist::artistSong (string name) const { 
    int position = 1;  
    for (PlaylistNode* node = head; node != nullptr; node = node -> GetNext()) {  //traverse through the list 
        if (node -> GetArtistName() == name) { 
            cout << position << '.' << endl; 
            node -> PrintPlaylistNode(); //print node info when you find the song name in the node, keep searching til end of list
            cout << endl;

            position++;
        } else {
            position++; //increment position, doesnt matter if it part of the artist list or not 
                        //position will always be incremented
        }
    }
}

void Playlist::totalTime() const { 
    int total = 0;
    for (PlaylistNode* node = head; node != nullptr; node = node -> GetNext()) { 
        total = total + node -> GetSongLength();
    }
    cout << total << " seconds" << endl << endl; 
}

void Playlist::Print() const { 
    int position = 1; 
    if (head == nullptr) { 
        cout << "Playlist is empty" << endl << endl; 
    } else {
        for(PlaylistNode* curr = head; curr != nullptr; curr = curr -> GetNext()) { //traverse through the list
            cout << position << "." << endl; 
            curr -> PrintPlaylistNode();
            cout << endl; 
            position++;
        }
    }
}