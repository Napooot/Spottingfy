// Created by AlvinWong on 12/1/2023.

#pragma once

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include "nlohman/json.hpp"
#include "Song.h"

using json = nlohmann::json;

// Callback function to write the HTTP response to a string
size_t writeCallBack(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

std::string getAccessToken() {
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
        std::string post_data = "grant_type=client_credentials"; // Set the POST data
        post_data += "&client_id=" + std::string(client_id); //add client id
        post_data += "&client_secret=" + std::string(client_secret); //add client secret

        curl_easy_setopt(curlHandle, CURLOPT_URL, token_url); //set curlHandle url to token_url
        curl_easy_setopt(curlHandle, CURLOPT_POST, 1L); //set curlHandle access request to POST

        // Set the request body data
        curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, post_data.c_str());

        // Set the write callback to capture the response
        std::string responseData;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallBack);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseData);

        // Perform the request
        curlResponse = curl_easy_perform(curlHandle);

        // Check for errors
        if (curlResponse != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlResponse));
            curl_easy_cleanup(curlHandle);
            return("Error");
        } else {
            // Print the response data (JSON containing the access token)
//            std::cout << "Response: " << responseData << std::endl;
            try {
                json tracksAudioFeaturesJson = json::parse(responseData);
                responseData = tracksAudioFeaturesJson["access_token"];
                curl_easy_cleanup(curlHandle);
                return responseData;
            }  catch (const std::exception& e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }
        }
    }
    return "Error!";
}

//Request play list info using access token and playlist ID
std::vector<std::string> requestPlaylistInfo(const std::string& accessToken, const std::string& playListID, std::vector<std::string> &trackIds) {
    //initialize curlHandle
    CURL* curlHandle = curl_easy_init();

    //if curl initialization is okay
    if (curlHandle) {
        std::string apiUrl = "https://api.spotify.com/v1/playlists/" + playListID;
        std::string authHeader = "Authorization: Bearer " + accessToken; // Set the authorization header with the access token
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curlHandle, CURLOPT_URL, apiUrl.c_str()); // Set the URL for the cURL request
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers); // set the headers for cURL request

        // Set the callback function to handle the response
        std::string responseData;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallBack);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseData);

        // Perform the cURL request
        CURLcode res = curl_easy_perform(curlHandle);

        // Check for errors and cleanup
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                json playlistJson = json::parse(responseData);

                // Extract track IDs from the items array
                for (const auto& track : playlistJson["tracks"]["items"]) {
                    std::string trackId = track["track"]["id"];
//                    std::cout << trackId << std::endl; //print out trackIds for debugging
                    trackIds.push_back(trackId);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }
        }

        // Clean up the cURL handle and headers
        curl_easy_cleanup(curlHandle);
        curl_slist_free_all(headers);
        return trackIds;
    }
    return {};
}

std::vector<Song> getTracksAudioFeatures(const std::vector<std::string>& trackList, const std::string& accessToken, std::vector<Song>& userTrackList) {
    CURL* curlHandle = curl_easy_init();
    if(curlHandle) {
        std::string apiUrl = "https://api.spotify.com/v1/audio-features?ids="; //set API url for getting audio features

        for(const std::string& trackId: trackList) {
            apiUrl += trackId + ",";
        }
        apiUrl.pop_back();

        std::string authHeader = "Authorization: Bearer " + accessToken; //set authorization header

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, authHeader.c_str()); //add authorization header to header list

        curl_easy_setopt(curlHandle, CURLOPT_URL, apiUrl.c_str()); // Set the URL for the cURL handle
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers); // set the headers for cURL handle

        std::string responseData; //initialize string to hold response data
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallBack); //set callback function
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseData); //set responseData variable to be written to

        CURLcode curlResponse = curl_easy_perform(curlHandle); //perform curl request and get response

        //check if curl request was alright
        if (curlResponse != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curlResponse) << std::endl;
        } else {
            try {
                json tracksAudioFeaturesJson = json::parse(responseData);
                for(int i = 0; i < tracksAudioFeaturesJson["audio_features"].size(); i++) {
                    auto trackFeatures = tracksAudioFeaturesJson["audio_features"][i];
                    std::vector<std::string> audioFeatures;

                    audioFeatures.emplace_back("User Song #" + std::to_string(i+1));
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
            }  catch (const std::exception& e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }
        }
        curl_easy_cleanup(curlHandle);
        curl_slist_free_all(headers);
    }
    return userTrackList;
}

std::string extractPlaylistId(const std::string& playlistLink) {
    // Define a regular expression pattern to match Spotify playlist links
    std::regex pattern("https://open\\.spotify\\.com/playlist/([a-zA-Z0-9]+)");

    // Use std::smatch to store the match results
    std::smatch match;

    // Use std::regex_search to find the first match in the string
    if (std::regex_search(playlistLink, match, pattern)) {
        // Extract the playlist ID from the matched group
        std::string playlistId = match[1];
        return playlistId;
    } else {
        // Return an empty string if no match is found
        return "";
    }
}

