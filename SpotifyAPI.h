#ifndef SPOTIFYAPI_H
#define SPOTIFYAPI_H

#pragma once
#include "QtCore/qjsonarray.h"
#include "QtCore/qjsondocument.h"
#include "QtCore/qjsonobject.h"
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QByteArray>
#include <QDebug>
#include "Song.h"

using namespace std;

class SpotifyAPI : public QObject
{
    Q_OBJECT

public:
    SpotifyAPI(QObject *parent = nullptr) : QObject(parent) {}

    QString accessToken;
    QString playlistID;
    QVector<QString> songIds;
    vector<Song> songsInPlaylist;

    QString getAccessToken();
    QString getPlaylistID();
    void setPlaylistID(QString id);

    QString songArtist; QString songTitle; QString acousticness; QString danceability; QString duration_ms;
    QString energy; QString instrumentalness; QString key; QString liveliness; QString loudness;
    QString mode; QString speechiness; QString tempo; QString valence;

    void requestAccessToken(const QString &clientId, const QString &clientSecret);

    void getPlaylist(const QString &accessToken, const QString &playlistID);
    void getTrackInfo(const QString &accessToken, const QString &trackId);
    void getAudioFeatures(const QString &accessToken, const QString &trackId);
    void getSongEverything(const QString &accessToken, QVector<QString>&songIds);
//    void getSongEverything(const QString &accessToken, const QVector<QString> &songIds);

    // helper functions for handling responses
    void handleAccessTokenResponse(const QByteArray &responseData);
    void handlePlaylistResponse(const QByteArray &responseData);
    void handleTrackInfoResponse(const QByteArray &responseData);
    void handleAudioFeaturesResponse(const QByteArray &responseData);

    void clearEverything(); // clearing data for potential new spotify data



#endif // SPOTIFYAPI_H
};
