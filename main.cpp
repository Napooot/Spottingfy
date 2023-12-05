#include "curlFunctions.h"

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT); //initialize the libcurl functionality globally, only done once!!!

    std::string accessToken = getAccessToken();

    //get user spotify playlist ID from command line interface
    cout << "Please enter your spotify playlist link: ";
    string playListLink;
    cin >> playListLink;
    string playListID = extractPlaylistId(playListLink);

    //get the track ids from the user playlist
    std::vector<std::string> trackIds;
    trackIds = requestPlaylistInfo(accessToken,playListID,trackIds);

    //parse all user playlist song attributes into song objects
    std::vector<Song> userList;
    userList = getTracksAudioFeatures(trackIds,accessToken,userList);

    //parse dataset csv into song objects
    vector<Song> dataBase = Song::createPlayList("Spottingfy_dataset.csv");
    std::cout << "DATA SET OPENED. Data Set Size: " << dataBase.size() <<  "\n\n";

    //create vector to hold new recommendations
    vector<string> newRecommendations;
    newRecommendations = Song::recommendPlayList(userList,dataBase,newRecommendations);

    //print them out in command line for user
    cout << endl << "Your new song recommendations are: " << endl;
    for(const string& i : newRecommendations) {
        cout << i << endl;
    }

    curl_global_cleanup(); //clean up global curl state, done once too
    return 0;
}
