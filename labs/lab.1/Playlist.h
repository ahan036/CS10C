#pragma once //replace ifndef and makes sure file is only included once 
#include <string>
using namespace std;

//REMEMBER THIS IS FOR SINGLY LINKED LIST THE POINTER ONLY POINT TO THE FOLLOWING NODE

class PlaylistNode { 
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode *nextNodePtr;

    public: //use these helper functions in playlist class in order to add songs etc. and manipulate the playlist 
    //no parameters for default
        PlaylistNode() : uniqueID("none"),
                         songName("none"),
                         artistName("none"),
                         songLength(0),
                         nextNodePtr(nullptr) {}

        PlaylistNode(string, string, string, int); //paramaterized constructor

        void InsertAfter(PlaylistNode* node);

        void SetNext(PlaylistNode *node) { 
            nextNodePtr = node; 
        }

        //2nd const makes sure nothing inside will alter uniqueID, by reference bc we don't want to make a copy
        //theres no need to 
        const string& GetID() const { 
            return uniqueID;
        }

        const string& GetSongName() const { 
            return songName;
        }

        const string& GetArtistName() const {
            return artistName;
        }

        int GetSongLength() const { 
            return songLength;
        }

        //no const bc ptr is going to change, we do not want to return the nullptr we set it as 
        PlaylistNode* GetNext() { 
            return nextNodePtr;
        }

        void PrintPlaylistNode();
};

//playlist class is going to use the node class, the node class only creates individual songs in a list 
//all menu functions will be coded within this class 
class Playlist { 
    private: 
    PlaylistNode* head;
    PlaylistNode* tail; 

    public: 
    //constructor 
    Playlist(): head(nullptr), tail(nullptr) {}

    //traverse through list created in playlistnode
    void Print() const; 

    //traverse through the list to find the current position first, use new variables to find the 2 nodes to swap 
    // then swap their positions and consider the next node ptr 
    void changePosition(int currPos, int newPos) const;

    //you can use the insertafter func to help, dont forget to code for if there is nothing in the list
    void add(PlaylistNode* );

    //basic remove function, do not over complicate this 
    void remove(string);

    //find song by one artist, traverse through the list and document the position number please
    void artistSong (string) const;

    //traverse through the list and use the getter to add to a total time 
    void totalTime() const; 

};
