#include "SearchBarUI.h"
#include "ui_SearchBarUI.h"

search_bar::search_bar(QWidget *parent) : QWidget(parent), ui(new Ui::search_bar)
{
    ui->setupUi(this);
    search_push_button = ui->search_push_button;
    input_line = ui->enter_playlist_input;
    clear_button = ui->clear_button;
}

search_bar::~search_bar()
{
    delete ui;
}

// once the search button is clicked in the UI, this function will be called to check if the link provided is correct, then the playlistID will be stored for the api to use
QString search_bar::searchPushButtonClicked() {
    if (input_line->text().isEmpty()) {
        QMessageBox::information(this, "Empty Search", "Your search is empty! Please provide us a link first.");
        return "false";

    } else if (input_line->hasAcceptableInput()) {
        QString userInputText = input_line->text();

        // Define a regular expression pattern to match the playlist ID
        QRegularExpression regex("https://open.spotify.com/playlist/([a-zA-Z0-9]+)");

        // Search for the pattern in the user input
        QRegularExpressionMatch match = regex.match(userInputText);

        if (match.hasMatch()) {
            // extract the playlist ID from the matched part
            QString playlistID = match.captured(1);
            return playlistID;
        }

        else {
            // No match found
            QMessageBox::information(this, "Invalid Link", "Hey, this isn't a Spotify link :-(");
            return "false";
        }
    }
}
