#pragma once

#include "QtWidgets/qboxlayout.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "SearchBarUI.h"
#include "PlaylistUI.h"
#include "Song.h"
#include "SpotifyAPI.h"
#include <QDesktopServices>
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void spotifyAuthorization();
    void callSpotifyAPI();
    void clearSpotifyPlaylist();
    void checkInputLine(const QString &text);

private:
    Ui::MainWindow *ui;
    SpotifyAPI spotifyAPI;
    QWidget *widgets_layout;
    search_bar *searchBarWidget; // to add the searchBar into widgets layout
    new_playlist *newPlaylistWidget;
    QVBoxLayout *mainLayout;
    QString CLIENT_ID = "d13f67f2fc5c4bd9ad96bfadc2f2e9bc";
    QString CLIENT_SECRET = "9006a972a96c4441bafe1b5385376375";
    string ACCESS_TOKEN;
//    vector<Song> newSongList;

};
#endif // MAINWINDOW_H
