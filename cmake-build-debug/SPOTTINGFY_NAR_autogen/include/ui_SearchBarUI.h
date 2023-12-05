/********************************************************************************
** Form generated from reading UI file 'SearchBarUI.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHBARUI_H
#define UI_SEARCHBARUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_search_bar
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *welcome_user_layout;
    QLabel *context_label;
    QWidget *search_widget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *clear_button;
    QLineEdit *enter_playlist_input;
    QPushButton *search_push_button;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *search_bar)
    {
        if (search_bar->objectName().isEmpty())
            search_bar->setObjectName("search_bar");
        search_bar->resize(687, 174);
        search_bar->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        verticalLayout = new QVBoxLayout(search_bar);
        verticalLayout->setObjectName("verticalLayout");
        welcome_user_layout = new QHBoxLayout();
        welcome_user_layout->setObjectName("welcome_user_layout");

        verticalLayout->addLayout(welcome_user_layout);

        context_label = new QLabel(search_bar);
        context_label->setObjectName("context_label");
        context_label->setStyleSheet(QString::fromUtf8("font: 500 13pt \"Product Sans Medium\";"));

        verticalLayout->addWidget(context_label);

        search_widget = new QWidget(search_bar);
        search_widget->setObjectName("search_widget");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(search_widget->sizePolicy().hasHeightForWidth());
        search_widget->setSizePolicy(sizePolicy);
        search_widget->setMinimumSize(QSize(0, 0));
        horizontalLayout_5 = new QHBoxLayout(search_widget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_2 = new QSpacerItem(60, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        clear_button = new QPushButton(search_widget);
        clear_button->setObjectName("clear_button");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(clear_button->sizePolicy().hasHeightForWidth());
        clear_button->setSizePolicy(sizePolicy1);
        clear_button->setCursor(QCursor(Qt::PointingHandCursor));
        clear_button->setContextMenuPolicy(Qt::DefaultContextMenu);
        clear_button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(clear_button);

        enter_playlist_input = new QLineEdit(search_widget);
        enter_playlist_input->setObjectName("enter_playlist_input");
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(50);
        sizePolicy2.setVerticalStretch(50);
        sizePolicy2.setHeightForWidth(enter_playlist_input->sizePolicy().hasHeightForWidth());
        enter_playlist_input->setSizePolicy(sizePolicy2);
        enter_playlist_input->setMinimumSize(QSize(0, 0));
        enter_playlist_input->setStyleSheet(QString::fromUtf8("background-color:rgb(57, 101, 89);\n"
"border-radius: 10px;\n"
"font: 500 13pt \"Product Sans Medium\";"));
        enter_playlist_input->setInputMethodHints(Qt::ImhNone);
        enter_playlist_input->setFrame(true);
        enter_playlist_input->setEchoMode(QLineEdit::Normal);
        enter_playlist_input->setAlignment(Qt::AlignCenter);
        enter_playlist_input->setClearButtonEnabled(false);

        horizontalLayout_5->addWidget(enter_playlist_input);

        search_push_button = new QPushButton(search_widget);
        search_push_button->setObjectName("search_push_button");
        sizePolicy1.setHeightForWidth(search_push_button->sizePolicy().hasHeightForWidth());
        search_push_button->setSizePolicy(sizePolicy1);
        search_push_button->setMinimumSize(QSize(1, 2));
        search_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        search_push_button->setMouseTracking(false);
        search_push_button->setIconSize(QSize(16, 16));

        horizontalLayout_5->addWidget(search_push_button);

        horizontalSpacer_3 = new QSpacerItem(60, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(search_widget);


        retranslateUi(search_bar);

        search_push_button->setDefault(false);


        QMetaObject::connectSlotsByName(search_bar);
    } // setupUi

    void retranslateUi(QWidget *search_bar)
    {
        search_bar->setWindowTitle(QCoreApplication::translate("search_bar", "Form", nullptr));
        context_label->setText(QCoreApplication::translate("search_bar", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:400; color:#eaeaea;\">Please only provide public playlists with a max of 100 songs</span></p></body></html>", nullptr));
        clear_button->setText(QCoreApplication::translate("search_bar", "\342\206\272", nullptr));
        enter_playlist_input->setInputMask(QString());
        enter_playlist_input->setText(QString());
        enter_playlist_input->setPlaceholderText(QCoreApplication::translate("search_bar", "Copy playlist link here...", nullptr));
        search_push_button->setText(QCoreApplication::translate("search_bar", "\360\237\224\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class search_bar: public Ui_search_bar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHBARUI_H
