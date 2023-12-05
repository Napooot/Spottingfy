#ifndef SEARCHBARUI_H
#define SEARCHBARUI_H

#pragma once

#include "QtWidgets/qpushbutton.h"
#include <QWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


namespace Ui {
class search_bar;
}

class search_bar : public QWidget
{
    Q_OBJECT

public:
    // SpotifyAPI spotify_api;
    explicit search_bar(QWidget *parent = nullptr);
    QString searchPushButtonClicked(); // once the search button is clicked in the UI, this function will be called to check if the link provided is correct, then the playlistID will be stored for the api to use
    QPushButton *search_push_button;
    QPushButton *clear_button;
    QLineEdit *input_line;
    ~search_bar();

private:
    Ui::search_bar *ui;
};

#endif // SEARCH_BAR_H
