/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *newGameButton;
    QPushButton *gameMenuButton;
    QPushButton *recordsMenuButton;
    QStackedWidget *stackedWidget;
    QWidget *gamePage;
    QPushButton *checkButton;
    QLineEdit *inputField;
    QTextEdit *gameLog;
    QWidget *recordsPage;
    QListWidget *recordsList;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 781, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        newGameButton = new QPushButton(horizontalLayoutWidget);
        newGameButton->setObjectName("newGameButton");

        horizontalLayout->addWidget(newGameButton);

        gameMenuButton = new QPushButton(horizontalLayoutWidget);
        gameMenuButton->setObjectName("gameMenuButton");
        gameMenuButton->setCheckable(true);
        gameMenuButton->setChecked(true);

        horizontalLayout->addWidget(gameMenuButton);

        recordsMenuButton = new QPushButton(horizontalLayoutWidget);
        recordsMenuButton->setObjectName("recordsMenuButton");
        recordsMenuButton->setCheckable(true);
        recordsMenuButton->setChecked(true);

        horizontalLayout->addWidget(recordsMenuButton);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(19, 119, 771, 391));
        gamePage = new QWidget();
        gamePage->setObjectName("gamePage");
        checkButton = new QPushButton(gamePage);
        checkButton->setObjectName("checkButton");
        checkButton->setGeometry(QRect(580, 20, 161, 29));
        inputField = new QLineEdit(gamePage);
        inputField->setObjectName("inputField");
        inputField->setGeometry(QRect(20, 20, 541, 26));
        gameLog = new QTextEdit(gamePage);
        gameLog->setObjectName("gameLog");
        gameLog->setGeometry(QRect(3, 64, 751, 351));
        stackedWidget->addWidget(gamePage);
        recordsPage = new QWidget();
        recordsPage->setObjectName("recordsPage");
        recordsList = new QListWidget(recordsPage);
        recordsList->setObjectName("recordsList");
        recordsList->setGeometry(QRect(90, 20, 581, 351));
        stackedWidget->addWidget(recordsPage);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        newGameButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \320\270\320\263\321\200\320\260", nullptr));
        gameMenuButton->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216 \320\270\320\263\321\200\321\213", nullptr));
        recordsMenuButton->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216 \321\200\320\265\320\272\320\276\321\200\320\264\320\276\320\262", nullptr));
        checkButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
