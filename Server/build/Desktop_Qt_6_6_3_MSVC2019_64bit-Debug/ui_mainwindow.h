/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
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
    QGroupBox *grbChats;
    QVBoxLayout *verticalLayout;
    QTabWidget *tbChats;
    QGroupBox *groupBox;
    QListWidget *lstClients;
    QPushButton *btnDisconnectAll;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1101, 413);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../Downloads/1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        grbChats = new QGroupBox(centralwidget);
        grbChats->setObjectName("grbChats");
        verticalLayout = new QVBoxLayout(grbChats);
        verticalLayout->setObjectName("verticalLayout");
        tbChats = new QTabWidget(grbChats);
        tbChats->setObjectName("tbChats");

        verticalLayout->addWidget(tbChats);


        horizontalLayout->addWidget(grbChats);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        lstClients = new QListWidget(groupBox);
        lstClients->setObjectName("lstClients");
        lstClients->setGeometry(QRect(10, 30, 251, 261));
        btnDisconnectAll = new QPushButton(groupBox);
        btnDisconnectAll->setObjectName("btnDisconnectAll");
        btnDisconnectAll->setGeometry(QRect(10, 300, 251, 29));

        horizontalLayout->addWidget(groupBox);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1101, 25));
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
        grbChats->setTitle(QCoreApplication::translate("MainWindow", "Chats", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        btnDisconnectAll->setText(QCoreApplication::translate("MainWindow", "DisconnectAll", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
