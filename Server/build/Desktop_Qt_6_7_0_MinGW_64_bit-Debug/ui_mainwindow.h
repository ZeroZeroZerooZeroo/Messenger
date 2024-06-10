/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *grpChats;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tbClientsChat;
    QGroupBox *grpClients;
    QVBoxLayout *verticalLayout;
    QListWidget *lstClients;
    QPushButton *btnDisconnectAll;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(629, 346);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        grpChats = new QGroupBox(centralwidget);
        grpChats->setObjectName("grpChats");
        grpChats->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(grpChats);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tbClientsChat = new QTabWidget(grpChats);
        tbClientsChat->setObjectName("tbClientsChat");
        tbClientsChat->setTabsClosable(true);

        verticalLayout_2->addWidget(tbClientsChat);


        horizontalLayout->addWidget(grpChats);

        grpClients = new QGroupBox(centralwidget);
        grpClients->setObjectName("grpClients");
        verticalLayout = new QVBoxLayout(grpClients);
        verticalLayout->setObjectName("verticalLayout");
        lstClients = new QListWidget(grpClients);
        lstClients->setObjectName("lstClients");

        verticalLayout->addWidget(lstClients);

        btnDisconnectAll = new QPushButton(grpClients);
        btnDisconnectAll->setObjectName("btnDisconnectAll");

        verticalLayout->addWidget(btnDisconnectAll);


        horizontalLayout->addWidget(grpClients);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 629, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Server", nullptr));
        grpChats->setTitle(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\202\321\213", nullptr));
        grpClients->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\273\320\270\320\265\320\275\321\202\321\213", nullptr));
        btnDisconnectAll->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\262\321\201\320\265\321\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
