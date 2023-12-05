#include "curlFunctions.h"

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT); //initialize the libcurl functionality globally, only done once!!!

    std::string accessToken = getAccessToken();
//    std::cout << "Access Token: " << accessToken << std::endl;

    //Rachels Playlist: 6daOzCdZgqy2eUYTXGRXiA
    //Workout Playlist: 2TgkaMuRCcakvnS0GeC6Fm
    //Vancouver Playlist: 5yRfuPMl8y8hOEUp6gvWQF
    //Sad: 18eemOS00Cj0J5WCvpGb3t

    cout << "Please enter your spotify playlist link: ";
    string playListLink;
    cin >> playListLink;
    string playListID = extractPlaylistId(playListLink);

    std::vector<std::string> trackIds;
    trackIds = requestPlaylistInfo(accessToken,playListID,trackIds);

    std::vector<Song> userList;
    userList = getTracksAudioFeatures(trackIds,accessToken,userList);

    //opening dataBase
    vector<Song> dataBase = Song::createPlayList("Spottingfy_dataset.csv");
    std::cout << "DATA SET OPENED. Data Set Size: " << dataBase.size() <<  "\n\n";

    vector<string> newRecommendations;
    newRecommendations = Song::recommendPlayList(userList,dataBase,newRecommendations);

    cout << endl << "Your new song recommendations are: " << endl;
    for(const string& i : newRecommendations) {
        cout << i << endl;
    }

    curl_global_cleanup(); //clean up global curl state, done once too
    return 0;
}
