#ifndef PLAYLISTUI_H
#define PLAYLISTUI_H

#pragma once

#include <QWidget>
#include <QString>
#include <QListWidget>

using namespace std;

namespace Ui {
class new_playlist;
}

class new_playlist : public QWidget
{
    Q_OBJECT

public:
    explicit new_playlist(QWidget *parent = nullptr);
    QListWidget *list_new_recommendations;
    ~new_playlist();

private:
    Ui::new_playlist *ui;
    string playlist;
};

#endif // NEW_PLAYLIST_H
