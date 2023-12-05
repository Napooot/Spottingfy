/********************************************************************************
** Form generated from reading UI file 'PlaylistUI.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYLISTUI_H
#define UI_PLAYLISTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_new_playlist
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *new_playlist_widget;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QFrame *line;
    QListWidget *list_new_recommendations;

    void setupUi(QWidget *new_playlist)
    {
        if (new_playlist->objectName().isEmpty())
            new_playlist->setObjectName("new_playlist");
        new_playlist->resize(446, 404);
        verticalLayout = new QVBoxLayout(new_playlist);
        verticalLayout->setObjectName("verticalLayout");
        new_playlist_widget = new QWidget(new_playlist);
        new_playlist_widget->setObjectName("new_playlist_widget");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(new_playlist_widget->sizePolicy().hasHeightForWidth());
        new_playlist_widget->setSizePolicy(sizePolicy);
        new_playlist_widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.497537, y1:1, x2:0.497537, y2:0, stop:0 rgba(30, 30, 30, 255), stop:0.605911 rgba(69, 69, 69, 255), stop:1 rgba(88, 88, 88, 255));\n"
"border-radius: 10px"));
        gridLayout_2 = new QGridLayout(new_playlist_widget);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(verticalSpacer_2, 0, 0, 1, 1);

        label_3 = new QLabel(new_playlist_widget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 500 13pt \"Gotham\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        line = new QFrame(new_playlist_widget);
        line->setObjectName("line");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(1, 1));
        line->setMaximumSize(QSize(16777215, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: rgba(104, 105, 105, 144);"));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(0);
        line->setMidLineWidth(1);
        line->setFrameShape(QFrame::HLine);

        gridLayout_2->addWidget(line, 2, 0, 2, 1);

        list_new_recommendations = new QListWidget(new_playlist_widget);
        list_new_recommendations->setObjectName("list_new_recommendations");
        list_new_recommendations->setStyleSheet(QString::fromUtf8("font: 500 13pt \"Product Sans Medium\";"));

        gridLayout_2->addWidget(list_new_recommendations, 4, 0, 1, 1);


        verticalLayout->addWidget(new_playlist_widget);


        retranslateUi(new_playlist);

        QMetaObject::connectSlotsByName(new_playlist);
    } // setupUi

    void retranslateUi(QWidget *new_playlist)
    {
        new_playlist->setWindowTitle(QCoreApplication::translate("new_playlist", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("new_playlist", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt;\">Here's your new playlist:</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class new_playlist: public Ui_new_playlist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYLISTUI_H
