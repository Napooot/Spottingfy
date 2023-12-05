#include "SpotifyAPI.h"

QString SpotifyAPI::getAccessToken(){
    return this->accessToken;
}
void SpotifyAPI::setPlaylistID(QString id){
    this->playlistID = id;
}
QString SpotifyAPI::getPlaylistID(){
    return this->playlistID;
}

// clearing data for potential new spotify data
void SpotifyAPI::clearEverything(){
    playlistID.clear();
    songIds.clear();
    songsInPlaylist.clear();
}

void SpotifyAPI::requestAccessToken(const QString &clientId, const QString &clientSecret) {
    // Create a QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Set up the request
    QNetworkRequest request(QUrl("https://accounts.spotify.com/api/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Encode client ID and client secret for Authorization header
    QByteArray credentials = (clientId + ":" + clientSecret).toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + credentials);

    // Set up the request parameters
    QUrlQuery postData;
    postData.addQueryItem("grant_type", "client_credentials");

    // Make the POST request
    QNetworkReply *reply = manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    // Handle the response
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            handleAccessTokenResponse(responseData);
        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        // Clean up
        reply->deleteLater();
    });

    // Run the event loop
    // qApp->exec();
}

void SpotifyAPI::handleAccessTokenResponse(const QByteArray &responseData) {
    // Parse the JSON response
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();

        // Check if the access_token is present
        if (jsonObj.contains("access_token")) {
            accessToken = jsonObj.value("access_token").toString();
            qDebug() << "Access Token:" << accessToken;

            // Check if the token_type is present
            if (jsonObj.contains("token_type")) {
                QString tokenType = jsonObj.value("token_type").toString();
                qDebug() << "Token Type:" << tokenType;
            } else {
                qDebug() << "Error: Missing token_type in the response";
            }

            // Check if expires_in is present and convert it to seconds
            if (jsonObj.contains("expires_in")) {
                int expiresIn = jsonObj.value("expires_in").toInt();
                qDebug() << "Expires In:" << expiresIn << "seconds";
            } else {
                qDebug() << "Error: Missing expires_in in the response";
            }
        } else {
            qDebug() << "Error: Missing access_token in the response";
        }
    } else {
        qDebug() << "Error: Unable to parse JSON response";
    }
}

void SpotifyAPI::getPlaylist(const QString &accessToken, const QString &playlistID) {
    // Create a QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Set up the request
    QNetworkRequest request(QUrl("https://api.spotify.com/v1/playlists/" + playlistID));
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

    // Make the GET request
    QNetworkReply *reply = manager->get(request);

    // Handle the response
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            handlePlaylistResponse(responseData);

        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        // Clean up
        reply->deleteLater();
    });

}

// making sure we're only getting song id's in playlist
void SpotifyAPI::handlePlaylistResponse(const QByteArray &responseData) {
    // Parse the JSON response
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject playlistObj = jsonDoc.object();

        // Check if the playlist object contains the "tracks" field
        if (playlistObj.contains("tracks")) {
            QJsonObject tracksObj = playlistObj.value("tracks").toObject();

            // Check if the tracks object contains the "items" field
            if (tracksObj.contains("items")) {
                QJsonArray itemsArray = tracksObj.value("items").toArray();

                // Iterate through each item in the items array
                for (const QJsonValue &itemValue : itemsArray) {
                    QJsonObject trackObj = itemValue.toObject();

                    // Check if the track object contains the "id" field
                    if (trackObj.contains("track") && trackObj["track"].isObject()) {
                        QString trackId = trackObj["track"].toObject().value("id").toString();
                        songIds.push_back(trackId);
                        qDebug() << songIds;
                    } else {
                        qDebug() << "Error: Missing 'id' field in track object";
                    }
                }
            } else {
                qDebug() << "Error: Missing 'items' field in tracks object";
            }
        } else {
            qDebug() << "Error: Missing 'tracks' field in playlist object";
        }
    } else {
        qDebug() << "Error: Unable to parse JSON response or it is not an object";
    }
}


void SpotifyAPI::getTrackInfo(const QString &accessToken, const QString &trackId) {
    // Create a QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Set up the request
    QUrl url("https://api.spotify.com/v1/tracks/" + trackId);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

    // Make the GET request
    QNetworkReply *reply = manager->get(request);

    // Handle the response
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "Error:";
            handleTrackInfoResponse(responseData);
        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        // Clean up
        reply->deleteLater();

    });

}
void SpotifyAPI::handleTrackInfoResponse(const QByteArray &responseData) {
    // Parse the JSON response
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject trackObj = jsonDoc.object();

        // Extract the song artist and song name
        if (trackObj.contains("artists") && trackObj["artists"].isArray()) {
            QJsonArray artistsArray = trackObj["artists"].toArray();
            if (!artistsArray.isEmpty()) {
                QJsonObject artistObj = artistsArray.first().toObject();
                songArtist = artistObj.value("name").toString();
            }
        }

        if (trackObj.contains("name")) {
            songTitle = trackObj.value("name").toString();
        }

        // Print or save the extracted values
        qDebug() << "Song Artist:" << songArtist;
        qDebug() << "Song Name:" << songTitle;
    } else {
        qDebug() << "Error: Unable to parse JSON response or it is not an object";
    }
}

void SpotifyAPI::getAudioFeatures(const QString &accessToken, const QString &trackId) {
    // Create a QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Set up the request
    QUrl url("https://api.spotify.com/v1/audio-features/" + trackId);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

    // Make the GET request
    QNetworkReply *reply = manager->get(request);

    // Handle the response
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            handleAudioFeaturesResponse(responseData);
        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        // Clean up
        reply->deleteLater();
    });

}
void SpotifyAPI::handleAudioFeaturesResponse(const QByteArray &responseData) {
    // Parse the JSON response
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject featuresObj = jsonDoc.object();

        // Extract the components
        acousticness = QString::number(featuresObj.value("acousticness").toDouble());
        danceability = QString::number(featuresObj.value("danceability").toDouble());
        duration_ms = QString::number(featuresObj.value("duration_ms").toDouble());
        energy = QString::number(featuresObj.value("energy").toDouble());
        instrumentalness = QString::number(featuresObj.value("instrumentalness").toDouble());
        key = QString::number(featuresObj.value("key").toDouble());
        liveliness = QString::number(featuresObj.value("liveliness").toDouble());
        loudness = QString::number(featuresObj.value("loudness").toDouble());
        mode = QString::number(featuresObj.value("mode").toDouble());
        speechiness = QString::number(featuresObj.value("speechiness").toDouble());
        tempo = QString::number(featuresObj.value("tempo").toDouble());
        valence = QString::number(featuresObj.value("valence").toDouble());

        // Print the extracted values (you can replace this with saving them into variables)
        // qDebug() << "Acousticness:" << acousticness;
        // qDebug() << "Danceability:" << danceability;
        // qDebug() << "Duration (ms):" << duration_ms;
        // qDebug() << "Energy:" << energy;
        // qDebug() << "Instrumentalness:" << instrumentalness;
        // qDebug() << "Key:" << key;
        // qDebug() << "Liveliness:" << liveliness;
        // qDebug() << "Loudness:" << loudness;
        // qDebug() << "Mode:" << mode;
        // qDebug() << "Speechiness:" << speechiness;
        // qDebug() << "Tempo:" << tempo;
        // qDebug() << "Valence:" << valence;
    } else {
        qDebug() << "Error: Unable to parse JSON response or it is not an object";
    }
}

void SpotifyAPI::getSongEverything(const QString &accessToken, vector<QString>& songIds){
    for (int i = 0; i < songIds.size(); i++){
        getAudioFeatures(accessToken, songIds[i]);
        getTrackInfo(accessToken, songIds[i]);
        Song newSong(songArtist.toStdString(), songTitle.toStdString(), acousticness.toStdString(), danceability.toStdString(), duration_ms.toStdString(), energy.toStdString(), instrumentalness.toStdString(), key.toStdString(), liveliness.toStdString(), loudness.toStdString(), mode.toStdString(), speechiness.toStdString(), tempo.toStdString(), valence.toStdString());
        songsInPlaylist.push_back(newSong);
    }
    qDebug() << "Songs in Playlist size" << songsInPlaylist.size();
}