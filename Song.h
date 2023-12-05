#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <fstream>
#include <sstream>
#include "csv.hpp"

using namespace std;

class Song {
    public:
        unordered_map<string, string> attributeVals;
        double inDegree;

    /*=============================CONSTRUCTORS======================================================*/
        Song(string songArtist, string songTitle, string acousticness, string danceability, string duration_ms,
             string energy, string instrumentalness, string key, string liveliness, string loudness,
             string mode, string speechiness, string tempo, string valence);
        Song(vector<string> variables);

    /*==================================MANIPULATORS (SORTING)========================================*/
        static vector<Song> mergeSort(vector<Song> &dataBase, const string& topic);
        static vector<Song> quickSort(vector<Song> &dataBase, const string& topic);
        static int binarySearch(vector<Song> &dataBase, const string &topic, const string& targetValue);

        static vector<Song> createPlayList(const string &fileName);
        static vector<string> recommendPlayList(vector<Song> &userList, vector<Song> &dataBase, vector<string> &newRecommendations);
        static void addEdges(Song &fromSong, const int &toSongEstimateIndex, vector<Song> &dataBase);
};
