#include <iostream> 
#include <string> 

#include "Playlist.h"


void PrintMenu(string playlistName) {
    cout << playlistName << " PLAYLIST MENU" << endl; 
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:" << endl;
}


int main() { 
    Playlist list;
    string playListName = "";

    cout << "Enter playlist's title:" << endl << endl; 
    getline(cin,playListName);

    PrintMenu(playListName);

    char option = ' ';

    string ID = "";
    string song = ""; 
    string artist = "";
    int length = 0;
 
    while (option != 'q') { //continues as long as input isnt q
        cin >> option;

        if (option == 'a') { 
            cout << "ADD SONG" << endl; 
            cout << "Enter song's unique ID:" << endl; 
            cin >> ID;
            cin.ignore();

            cout << "Enter song's name:" << endl; 
            getline(cin, song);

            cout << "Enter artist's name:" << endl; 
            getline(cin, artist);

            cout << "Enter song's length (in seconds):" << endl << endl;
            cin >> length; 

            PlaylistNode* currSong = new PlaylistNode(ID, song, artist, length); //create node bc u are adding

            list.add(currSong);
            PrintMenu(playListName);

        } else if (option == 'd') { 
            cout << "REMOVE SONG" << endl; 
            cout << "Enter song's unique ID:" << endl; 

            cin >> ID; 

            list.remove(ID); 
            PrintMenu(playListName);

        } else if (option == 'c') { 
            int currPos = 0; 
            int newPos = 0; 

            cout << "CHANGE POSITION OF SONG" << endl; 
            cout << "Enter songs current position:" << endl; 
            cin >> currPos; 

            cout << "Enter new position for song:" << endl; 
            cin >> newPos; 
            
        } else if (option == 's') { 
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl; 
            cout << "Enter artist's name:" << endl << endl;
            string name = " ";

            cin.ignore();
            getline(cin, name);

            list.artistSong(name);
            PrintMenu(playListName);

        } else if (option == 't') { 
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl; 
            cout << "Total time: ";

            list.totalTime();
            PrintMenu(playListName);

        } else if (option == 'o') { 
            cout << playListName << " - OUTPUT FULL PLAYLIST" << endl;

            list.Print();
            PrintMenu(playListName);
        }
    }

    return 0;
}