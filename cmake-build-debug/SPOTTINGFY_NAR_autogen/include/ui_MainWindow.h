/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *header_widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *welcome_title_label;
    QLabel *title_label;
    QLabel *description_label;
    QSpacerItem *verticalSpacer;
    QPushButton *login_spotify;
    QSpacerItem *verticalSpacer_2;
    QLabel *DSA_group_label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(542, 426);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(120, 242, 152, 255), stop:0.512315 rgba(69, 172, 145, 255), stop:1 rgba(15, 104, 169, 255));\n"
"min-height: 100vh;\n"
"margin: 0;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        header_widget = new QWidget(centralwidget);
        header_widget->setObjectName("header_widget");
        header_widget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(header_widget->sizePolicy().hasHeightForWidth());
        header_widget->setSizePolicy(sizePolicy);
        header_widget->setMinimumSize(QSize(0, 0));
        header_widget->setMaximumSize(QSize(16777215, 225));
        header_widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(120, 242, 152, 255), stop:0.512315 rgba(69, 172, 145, 255), stop:1 rgba(15, 104, 169, 255));\n"
"border-radius: 15px;"));
        verticalLayout = new QVBoxLayout(header_widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(13, 13, 13, 13);
        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_3);

        welcome_title_label = new QLabel(header_widget);
        welcome_title_label->setObjectName("welcome_title_label");
        welcome_title_label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(253, 255, 255);\n"
"font: 500 13pt \"Product Sans Medium\";"));
        welcome_title_label->setMargin(0);

        verticalLayout->addWidget(welcome_title_label);

        title_label = new QLabel(header_widget);
        title_label->setObjectName("title_label");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(10);
        sizePolicy1.setHeightForWidth(title_label->sizePolicy().hasHeightForWidth());
        title_label->setSizePolicy(sizePolicy1);
        title_label->setStyleSheet(QString::fromUtf8("background-color: rgba(253, 255, 255, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 90pt \"Gotham\";\n"
""));
        title_label->setMargin(0);

        verticalLayout->addWidget(title_label);

        description_label = new QLabel(header_widget);
        description_label->setObjectName("description_label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Product Sans")});
        font.setPointSize(13);
        font.setWeight(QFont::Medium);
        font.setItalic(false);
        description_label->setFont(font);
        description_label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"font: 500 13pt \"Product Sans\";"));

        verticalLayout->addWidget(description_label);


        verticalLayout_2->addWidget(header_widget);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        login_spotify = new QPushButton(centralwidget);
        login_spotify->setObjectName("login_spotify");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(login_spotify->sizePolicy().hasHeightForWidth());
        login_spotify->setSizePolicy(sizePolicy2);
        login_spotify->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gotham")});
        font1.setPointSize(25);
        font1.setWeight(QFont::Medium);
        font1.setItalic(false);
        login_spotify->setFont(font1);
        login_spotify->setCursor(QCursor(Qt::OpenHandCursor));
        login_spotify->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 97);\n"
"font: 500 25pt \"Gotham\";\n"
"border-radius: 10px;\n"
"color: rgba(255, 255, 255, 185);"));

        verticalLayout_2->addWidget(login_spotify);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        DSA_group_label = new QLabel(centralwidget);
        DSA_group_label->setObjectName("DSA_group_label");
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(DSA_group_label->sizePolicy().hasHeightForWidth());
        DSA_group_label->setSizePolicy(sizePolicy3);
        DSA_group_label->setStyleSheet(QString::fromUtf8("background-color: rgba(239, 255, 208, 90);\n"
"font: 500 13pt \"Product Sans\";\n"
"border-radius: 10px;\n"
"color: rgba(235, 255, 235, 200);"));
        DSA_group_label->setMargin(4);

        verticalLayout_2->addWidget(DSA_group_label);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        login_spotify->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        welcome_title_label->setText(QCoreApplication::translate("MainWindow", "Welcome to", nullptr));
        title_label->setText(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Gotham'; font-size:64pt;\">Spottingfy</span></p></body></html>", nullptr));
        description_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:400; color:#caeec4;\">Spottingfy is a project utilizing algorithms and Spotify API to help users curate a <br/>new playlist for themselves</span></p></body></html>", nullptr));
        login_spotify->setText(QCoreApplication::translate("MainWindow", "Let's Start", nullptr));
        DSA_group_label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Project created by Napat Sammacheep, Alvin Wong, Rachel Pu</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
