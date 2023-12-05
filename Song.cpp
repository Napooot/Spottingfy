#include "Song.h"

Song::Song(string songTitle, string songArtist, string acousticness, string danceability, string duration_ms,
           string energy, string instrumentalness, string key, string liveliness, string loudness,
           string mode, string speechiness, string tempo, string valence) {
    this->songTitle = songTitle;
    attributeVals["songArtist"] = songArtist;
    attributeVals["songTitle"] = songTitle;
    attributeVals["acousticness"] = acousticness;
    attributeVals["danceability"] = danceability;
    attributeVals["duration_ms"] = duration_ms;
    attributeVals["energy"] = energy;
    attributeVals["instrumentalness"] = instrumentalness;
    attributeVals["key"] = key;
    attributeVals["liveliness"] = liveliness;
    attributeVals["loudness"] = loudness;
    attributeVals["mode"] = mode;
    attributeVals["speechiness"] = speechiness;
    attributeVals["tempo"] = tempo;
    attributeVals["valence"] = valence;
    inDegree = 0;
}

Song::Song(vector<string> variables) {
    attributeVals["songTitle"] = variables[0];
    attributeVals["songArtist"] = variables[1];
    attributeVals["acousticness"] = variables[2];
    attributeVals["danceability"] = variables[3];
    attributeVals["duration_ms"] = variables[4];
    attributeVals["energy"] = variables[5];
    attributeVals["instrumentalness"] = variables[6];
    attributeVals["key"] = variables[7];
    attributeVals["liveliness"] = variables[8];
    attributeVals["loudness"] = variables[9];
    attributeVals["mode"] = variables[10];
    attributeVals["speechiness"] = variables[11];
    attributeVals["tempo"] = variables[12];
    attributeVals["valence"] = variables[13];
    inDegree = 0;
}

/*=============================SORTING FUNCTION IMPLEMENTATIONS===================================*/
vector<Song> Song::mergeSort(vector<Song> &dataBase, const string& topic) {
    if (dataBase.size() <= 1) {
        return dataBase;
    }

    int mid = dataBase.size() / 2;
    vector<Song> left(dataBase.begin(), dataBase.begin() + mid);
    vector<Song> right(dataBase.begin() + mid, dataBase.end());

    left = mergeSort(left, topic);
    right = mergeSort(right, topic);

    // Merge the sorted left and right vectors
    vector<Song> result;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (stod(left[i].attributeVals.at(topic)) < stod(right[j].attributeVals.at(topic))) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

vector<Song> Song::quickSort(vector<Song> &dataBase, const string& topic) {
    if (dataBase.size() <= 1) {
        return dataBase;
    }

    int pivotIndex = dataBase.size() / 2;
    Song pivot = dataBase[pivotIndex];
    dataBase.erase(dataBase.begin() + pivotIndex);

    vector<Song> left, right;
    for (const auto &song : dataBase) {
        if (stod(song.attributeVals.at(topic)) < stod(pivot.attributeVals.at(topic))) {
            left.push_back(song);
        } else {
            right.push_back(song);
        }
    }

    // Recursively sort the left and right partitions
    vector<Song> sortedSongs;
    sortedSongs = quickSort(left, topic);
    sortedSongs.push_back(pivot);
    vector<Song> rightSorted = quickSort(right, topic);
    sortedSongs.insert(sortedSongs.end(), rightSorted.begin(), rightSorted.end());

    return sortedSongs;
}



/*=============================PLAYLIST FUNCTION IMPLEMENTATION====================================*/
//vector<Song> Song::createPlayList(const string &fileName) {
//    vector<Song> dataBase;
//    std::vector<Song> songs;
//    csv::CSVReader csv_reader(fileName);
//
//    for (auto &row: csv_reader) {
//        vector<string> attributes;
//
//        attributes.push_back(row["track"].get<string>());
//        attributes.push_back(row["artist"].get<string>());
//        attributes.push_back(row["acousticness"].get<string>());
//        attributes.push_back(row["danceability"].get<string>());
//        attributes.push_back(row["duration_ms"].get<string>());
//        attributes.push_back(row["energy"].get<string>());
//        attributes.push_back(row["instrumentalness"].get<string>());
//        attributes.push_back(row["key"].get<string>());
//        attributes.push_back(row["liveness"].get<string>());
//        attributes.push_back(row["loudness"].get<string>());
//        attributes.push_back(row["mode"].get<string>());
//        attributes.push_back(row["speechiness"].get<string>());
//        attributes.push_back(row["tempo"].get<string>());
//        attributes.push_back(row["valence"].get<string>());
//
//        Song mySong(attributes);
//        dataBase.push_back(mySong);
//    }
//
//    return dataBase;
//}

//returns index of song
int Song::binarySearch(vector<Song> &dataBase, const string &topic, const string& targetValue) {
    int low = 0;
    int high = dataBase.size()-1;
    const double newTargetValue = stod(targetValue);

    double epsilon = 1e-9;
    while(low <= high) {
        int mid = low + (high-low) / 2;
        if( abs(stod(dataBase[mid].attributeVals[topic]) - newTargetValue) < epsilon) {
            int lowIndex = mid;
            int highIndex = mid;
            while(highIndex + 1 < dataBase.size() && stod(dataBase[highIndex+1].attributeVals[topic]) == newTargetValue) {
                highIndex++;
            }
            while(lowIndex - 1 >= 0 && stod(dataBase[lowIndex-1].attributeVals[topic]) == newTargetValue) {
                lowIndex--;
            }
            int randNum = rand()%(highIndex-lowIndex + 1) + lowIndex;
            return randNum;
        } else if (stod(dataBase[mid].attributeVals[topic]) < newTargetValue ) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    try {
        if( abs(stod(targetValue) - stod(dataBase[low].attributeVals[topic])) < abs(stod(targetValue) - stod(dataBase[high].attributeVals[topic]))) {
            return low;
        } else {
            return high;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument error: " << e.what() <<  " Values: " << targetValue << ", " << dataBase[low].attributeVals[topic] << ", " <<  dataBase[high].attributeVals[topic] << endl;
        return low;
    }
}

void Song::addEdges(Song &fromSong, const int &toSongEstimateIndex, vector<Song> &dataBase) {
    const int spread = 50; //increase spread to make song recommendations more varied and decrease for vice versa

    for(int i = toSongEstimateIndex; i <= toSongEstimateIndex+spread && i < dataBase.size(); i++) {
        dataBase[i].inDegree++;
    }

    for(int i = toSongEstimateIndex; i >= toSongEstimateIndex-spread && i > 0; i--) {
        dataBase[i].inDegree++;
    }
}

vector<string> Song::recommendPlayList(vector<Song> &userList, vector<Song> &dataBase, vector<string> &newRecommendations) {
    vector<std::string> topics = {"acousticness", "danceability", "duration_ms",
                                  "energy", "instrumentalness", "key", "liveliness", "loudness", "speechiness", "tempo", "valence"};

    for(string& topic : topics) {
        auto start = chrono::high_resolution_clock::now();
        cout << topic << " Sort started. " ;
        //        dataBase = Song::quickSort(dataBase,topic);
        sort(dataBase.begin(), dataBase.end(), [topic](const Song& lhs, const Song& rhs) {
            double lhsValue = stod(lhs.attributeVals.at(topic));
            double rhsValue = stod(rhs.attributeVals.at(topic));
            return lhsValue < rhsValue;
        });
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Sort finished. Time taken in seconds: " << duration.count()/1000000.0 << endl;

        for (Song &mySong: userList) {
            int songIndex = Song::binarySearch(dataBase, topic, mySong.attributeVals[topic]);
            Song::addEdges(mySong, songIndex, dataBase);
        }
    }

    sort(dataBase.begin(), dataBase.end(), [](const Song& lhs, const Song& rhs) {
        return lhs.inDegree < rhs.inDegree;
    });

    int newPlaylistSize;
    if(userList.size() < 10) {
        newPlaylistSize = userList.size();
    } else {
        newPlaylistSize = userList.size() - userList.size()%5;
    }

    for(int i = dataBase.size()-1; i > dataBase.size()-newPlaylistSize; i--) {
        newRecommendations.push_back(dataBase[i].attributeVals["songTitle"] + " by " + dataBase[i].attributeVals["songArtist"]);
    }
    return newRecommendations;
}
