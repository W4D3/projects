#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// lib_info.cpp
// Mitchell Wade
// Sep. 8, 2014
// This program reads from a file and converts the contents of the file (if it is in the proper format)
// to a more readable version of the file. It will show also the total time of each album and artist
// while also printing a better output format of the file

class Song { 
    public:
        string title;
        int time;
        int track;
};

class Album {
    public:
        map <int, Song *> songs;
        string name;
        int time;
        int nsongs;
};

class Artist {
    public:
        map <string, Album *> albums;
        string name;
        int time;
        int nsongs;
};

// Changes all of the underscores in each line to a space
string Convert(string word) { 

    int i;

    for (i = 0; i < word.size(); i++) {
        if (word[i] == '_') {
            word[i] = ' ';
        }
    }

    return word;
};

// Changes the totalTime in seconds back into "hours:minutes"
string intToString(int totalTime) {

    int minutes, seconds;
    ostringstream ss;

    minutes = totalTime/60;
    seconds = totalTime%60;

    if (seconds < 10) {
        ss << minutes << ":0" << seconds;
    } else 
        ss <<  minutes << ":" << seconds;

    return ss.str();  //Put everything in the output stream into a string
};

int main(int argc, char **argv) {

    Song *ptr; // A pointer for instances of the Song class
    int time1 = 0, time2 = 0 , totalTime = 0, totalTime2, track = 0;
    char junk; // A junk variable for each colon in the time
    string title, artist, album, genre;
    ifstream fs;
    Artist *ptr2; // A pointer for instances of the Artist class
    Album *ptr3; // A pointer for instances of the Album class
    map<string, Artist *> artistMap; // A map to hold all of the Artist pointers
    map<string, Artist *>::iterator nit;
    map<string, Album  *>::iterator nit2;
    map<int, Song *>::iterator nit3;

    // Check for proper usage of command line arguments
    if (argc != 2) {
        cerr << "usage: libinfo file\n";
        exit(1);
    }

    fs.open(argv[1]); // Open the file

    // Reads in each line and then runs through the while loop
    while (fs >> title >> time1 >> junk >>time2 >> artist >> album >> genre >> track) {

        time1 = time1*60; // Converts the number of minutes into seconds
        totalTime = time1+time2; // Adds the number of minutes and seconds into total seconds

        // Change all text from underscores to spaces
        title = Convert(title);
        artist = Convert(artist);
        album = Convert(album);
        genre = Convert(genre);

        // After reading in each line of input create a new instance of each song
        ptr = new Song();
        ptr->title = title;
        ptr->time = totalTime;
        ptr->track = track;

        // Search for artits in the map and if it is not there add it to the map
        nit = artistMap.find(artist);
        if (nit == artistMap.end()) {
            ptr2 = new Artist;
            ptr2->name = artist;
            ptr2->time = totalTime;
            ptr2->nsongs = 1; 
            artistMap.insert(make_pair(artist, ptr2)); // Add the new artist to the map
        } else {
            ptr2 = nit->second; // Grab the artist instance
            ptr2->time += totalTime;
            ptr2->nsongs++;
        }

        // Search for albums in the map and if it is not there add it to the map
        nit2 = ptr2->albums.find(album);
        if (nit2 == ptr2->albums.end()) {
            ptr3 = new Album;
            ptr3->name = album;
            ptr3->time = totalTime;
            ptr3->nsongs = 1;
            ptr2->albums.insert(make_pair(album, ptr3)); // Add the new album to the map
        } else {
            ptr3 = nit2->second; // Grab the album instance
            ptr3->time += totalTime;
            ptr3->nsongs++;
        }
        
        ptr3->songs.insert(make_pair(track, ptr)); // Add the new song to the map
    }

    // Output
    for (nit = artistMap.begin(); nit != artistMap.end(); nit++) {

        ptr2 = nit->second;
        // Prints out the artist, number of songs of the artist, and the total time of all songs
        printf("%s: %d, %s\n", ptr2->name.c_str(), ptr2->nsongs, intToString(ptr2->time).c_str());

        for (nit2 = ptr2->albums.begin(); nit2 != ptr2->albums.end(); nit2++) {
            ptr3 = nit2->second;
            // Prints out the album, number of songs on the album, and the total time of the album
            printf("        %s: %d, %s\n", ptr3->name.c_str(), ptr3->nsongs, intToString(ptr3->time).c_str());
            
            for (nit3 = ptr3->songs.begin(); nit3 != ptr3->songs.end(); nit3++) {
                ptr = nit3->second;
                // Prints out the song track numner, song name, and the total time of the song
                printf("                %d. %s: %s\n", ptr->track, ptr->title.c_str(), intToString(ptr->time).c_str());
        
            }
        }
    }
    
    fs.close();
    fs.clear();
    
    return 0;
}
