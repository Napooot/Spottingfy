// Created by AlvinWong on 12/1/2023.

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
#include <curl/curl.h>
#include <regex>
#include "nlohman/json.hpp"
#include "Song.h"

using json = nlohmann::json;

//callback function to write to output
size_t writeCallBack(void* contents, size_t size, size_t nmemb, string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

//get access token function
string getAccessToken() {
    //need to use C strings for libcurl so set as char *. NORMALLY DO NOT STORE CLIENT ID AND SECRET HERE!!
    const char* client_id = "d3b1a47b58584bae9bd76a5735837725";
    const char* client_secret = "04d4a3d09da847b78254e47e1e7d10e9";
    const char* token_url = "https://accounts.spotify.com/api/token";
    CURL* curlHandle;
    CURLcode curlResponse;

    // Initialize curl handle
    curlHandle = curl_easy_init();

    //if curl initialization is okay
    if (curlHandle) {
        string post_data = "grant_type=client_credentials"; // Set the POST data
        post_data += "&client_id=" + string(client_id); //add client id
        post_data += "&client_secret=" + string(client_secret); //add client secret

        curl_easy_setopt(curlHandle, CURLOPT_URL, token_url); //set curlHandle url to token_url
        curl_easy_setopt(curlHandle, CURLOPT_POST, 1L); //set curlHandle access request to POST

        curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, post_data.c_str()); //set request post data

        string responseData;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallBack); //set writeCallBack function
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseData); //set responsedata var to be written to

        curlResponse = curl_easy_perform(curlHandle); //perform the request

        // Check for errors
        if (curlResponse != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlResponse));
            curl_easy_cleanup(curlHandle);
            return("Error");
        } else {
            //parse response using json lib
            try {
                json tracksAudioFeaturesJson = json::parse(responseData);
                responseData = tracksAudioFeaturesJson["access_token"];
                curl_easy_cleanup(curlHandle);
                return responseData;
            }  catch (const exception& e) {
                cerr << "Error parsing JSON: " << e.what() << endl;
            }
        }
    }
    return "Error!";
}

//Request play list info using access token and playlist ID
vector<string> requestPlaylistInfo(const string& accessToken, const string& playListID, vector<string> &trackIds) {
    CURL* curlHandle = curl_easy_init(); //init curl handle

    //if curl initialization is okay
    if (curlHandle) {
        string apiUrl = "https://api.spotify.com/v1/playlists/" + playListID;
        string authHeader = "Authorization: Bearer " + accessToken; // set authorization header with the access token
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curlHandle, CURLOPT_URL, apiUrl.c_str()); //set the URL for the cURL request
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers); //set the headers for cURL request

        string responseData;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallBack); //set callback
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseData); //set responseData var to be written to

        //perform the cURL request
        CURLcode res = curl_easy_perform(curlHandle);

        //if no errors
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            try {
                json playlistJson = json::parse(responseData);
                // Extract track IDs from the items array
                for (const auto& track : playlistJson["tracks"]["items"]) {
                    string trackId = track["track"]["id"];
                    trackIds.push_back(trackId);
                }
            } catch (const exception& e) {
                cerr << "Error parsing JSON: " << e.what() << endl;
            }
        }

        //clean up the cURL handle and headers
        curl_easy_cleanup(curlHandle);
        curl_slist_free_all(headers);
        return trackIds;
    }
    return {};
}

//get track audio features function
vector<Song> getTracksAudioFeatures(const vector<string>& trackList, const string& accessToken, vector<Song>& userTrackList) {
    CURL* curlHandle = curl_easy_init();
    if(curlHandle) {
        string apiUrl = "https://api.spotify.com/v1/audio-features?ids="; //set api url for getting audio features

        for(const string& trackId: trackList) {
            apiUrl += trackId + ",";
        }
        apiUrl.pop_back();

        string authHeader = "Authorization: Bearer " + accessToken; //set authorization header

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, authHeader.c_str()); //add authorization header to header list

        curl_easy_setopt(curlHandle, CURLOPT_URL, apiUrl.c_str()); //set the URL for the cURL handle
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers); //set the headers for cURL handle

        string responseData; //initialize string to hold response data
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallBack); //set callback function
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseData); //set responseData variable to be written to

        CURLcode curlResponse = curl_easy_perform(curlHandle); //perform curl request and get response

        //check if curl request was alright
        if (curlResponse != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curlResponse) << endl;
        } else { //parse into song objects and send them back
            try {
                json tracksAudioFeaturesJson = json::parse(responseData);
                for(int i = 0; i < tracksAudioFeaturesJson["audio_features"].size(); i++) {
                    auto trackFeatures = tracksAudioFeaturesJson["audio_features"][i];
                    vector<string> audioFeatures;

                    audioFeatures.emplace_back("User Song #" + to_string(i+1));
                    audioFeatures.emplace_back("Unknown Artist");
                    audioFeatures.emplace_back(to_string(trackFeatures["acousticness"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["danceability"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["duration_ms"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["energy"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["instrumentalness"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["key"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["liveness"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["loudness"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["mode"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["speechiness"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["tempo"]));
                    audioFeatures.emplace_back(to_string(trackFeatures["valence"]));

                    Song newSong(audioFeatures);
                    userTrackList.push_back(newSong);
                }
            }  catch (const exception& e) {
                cerr << "Error parsing JSON: " << e.what() << endl;
            }
        }
        curl_easy_cleanup(curlHandle);
        curl_slist_free_all(headers);
    }
    return userTrackList;
}

//extract playlist ID from playlist link
string extractPlaylistId(const string& playlistLink) {
    regex pattern("https://open\\.spotify\\.com/playlist/([a-zA-Z0-9]+)");
    smatch match;

    //use regex_search to find the first match in the string
    if (regex_search(playlistLink, match, pattern)) {
        //extract playlist ID
        string playlistId = match[1];
        return playlistId;
    } else { //should never come here
        return "";
    }
}

