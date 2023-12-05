#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // initializing variables
    ui->setupUi(this);
    searchBarWidget = new search_bar(this); // initializing search bar widget
    newPlaylistWidget = new new_playlist(this); // initializing playlist widget
    widgets_layout = ui->centralwidget;
    mainLayout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());

    // other
    searchBarWidget->hide(); // hiding search bar first until spotifyLogin is successful
    newPlaylistWidget->hide(); // hiding until after search

    connect(ui->login_spotify, &QPushButton::clicked, this, &MainWindow::spotifyAuthorization); // when the login_spotify button clicked, then function spotifyAuthorization will occur
    connect(searchBarWidget->search_push_button, &QPushButton::clicked, this, &MainWindow::callSpotifyAPI); // when the search button is pushed, function callSpotifyAPI is called
    connect(searchBarWidget->input_line, &QLineEdit::returnPressed, this, &MainWindow::callSpotifyAPI); // if user presses return, function callSpotifyAPI is called
    connect(searchBarWidget->clear_button, &QPushButton::clicked, this, &MainWindow::clearSpotifyPlaylist); // if clear button is pushed, current spotifyAPI variables will be cleared
    connect(searchBarWidget->input_line, &QLineEdit::textChanged, this, &MainWindow::checkInputLine); // if user clears input line, then spotifyAPI variables will be cleared

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::spotifyAuthorization(){
    spotifyAPI.requestAccessToken(CLIENT_ID, CLIENT_SECRET);
    ui->login_spotify->hide(); // hiding login spotify button
    mainLayout->insertWidget(1, searchBarWidget); // will place the search widget at 1st index of widgets in mainLayout (so right below header widget)
    searchBarWidget->show();
    searchBarWidget->setMinimumSize(500,115);
}

void MainWindow::callSpotifyAPI(){
    // if the push button clicked is successfully, proceed (may change later...)
    if (searchBarWidget->searchPushButtonClicked() != "false"){
        spotifyAPI.setPlaylistID(searchBarWidget->searchPushButtonClicked());
        spotifyAPI.getPlaylist(spotifyAPI.getAccessToken(), spotifyAPI.getPlaylistID());

        // calling the algorithms
//        vector<Song> dataBase = Song::createPlayList("../Spottingfy_dataset.csv");
//        std::cout << "FILES OPENED. Data Base Size: " << dataBase.size() <<  "\n\n";
//        vector<string> newRecommendations;
//        newRecommendations = Song::recommendPlayList(spotifyAPI.songsInPlaylist,dataBase,newRecommendations);
//
//        for(string i : newRecommendations) {
//            cout << i << endl;
//        }

        // showing newPlaylist widget
        mainLayout->insertWidget(2, newPlaylistWidget);
        newPlaylistWidget->show();
        newPlaylistWidget->setMinimumSize(500,375);
    }
}

void MainWindow::clearSpotifyPlaylist(){
    searchBarWidget->input_line->clear();
    spotifyAPI.clearEverything();
}

void MainWindow::checkInputLine(const QString &text){
    if (text.isEmpty()){
        spotifyAPI.clearEverything();
    }
}