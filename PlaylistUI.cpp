#include "PlaylistUI.h"
#include "ui_PlaylistUI.h"

new_playlist::new_playlist(QWidget *parent) : QWidget(parent), ui(new Ui::new_playlist)
{
    ui->setupUi(this);
}

new_playlist::~new_playlist()
{
    delete ui;
}
