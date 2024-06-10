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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionExot;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lnClientName;
    QComboBox *cmbStatus;
    QListWidget *lstMessages;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lnMessage;
    QPushButton *btnSend;
    QPushButton *btnSendFile;
    QLabel *label_2;
    QComboBox *cmbDestination;
    QPushButton *btnShowHistory;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(363, 296);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName("actionConnect");
        actionExot = new QAction(MainWindow);
        actionExot->setObjectName("actionExot");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(false);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lnClientName = new QLineEdit(centralwidget);
        lnClientName->setObjectName("lnClientName");
        lnClientName->setEnabled(false);

        horizontalLayout_2->addWidget(lnClientName);

        cmbStatus = new QComboBox(centralwidget);
        cmbStatus->addItem(QString());
        cmbStatus->addItem(QString());
        cmbStatus->addItem(QString());
        cmbStatus->addItem(QString());
        cmbStatus->setObjectName("cmbStatus");
        cmbStatus->setEnabled(false);

        horizontalLayout_2->addWidget(cmbStatus);


        verticalLayout->addLayout(horizontalLayout_2);

        lstMessages = new QListWidget(centralwidget);
        lstMessages->setObjectName("lstMessages");
        lstMessages->setEnabled(false);

        verticalLayout->addWidget(lstMessages);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lnMessage = new QLineEdit(centralwidget);
        lnMessage->setObjectName("lnMessage");
        lnMessage->setEnabled(false);

        gridLayout->addWidget(lnMessage, 1, 1, 1, 2);

        btnSend = new QPushButton(centralwidget);
        btnSend->setObjectName("btnSend");
        btnSend->setEnabled(false);

        gridLayout->addWidget(btnSend, 1, 3, 1, 1);

        btnSendFile = new QPushButton(centralwidget);
        btnSendFile->setObjectName("btnSendFile");
        btnSendFile->setEnabled(false);
        btnSendFile->setMaximumSize(QSize(35, 16777215));

        gridLayout->addWidget(btnSendFile, 1, 4, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        cmbDestination = new QComboBox(centralwidget);
        cmbDestination->addItem(QString());
        cmbDestination->addItem(QString());
        cmbDestination->setObjectName("cmbDestination");
        cmbDestination->setEnabled(false);

        gridLayout->addWidget(cmbDestination, 0, 1, 1, 2);

        btnShowHistory = new QPushButton(centralwidget);
        btnShowHistory->setObjectName("btnShowHistory");

        gridLayout->addWidget(btnShowHistory, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 363, 25));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName("menuOptions");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOptions->menuAction());
        menuOptions->addAction(actionConnect);
        menuOptions->addSeparator();
        menuOptions->addAction(actionExot);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Client", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
        actionExot->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        lnClientName->setText(QString());
        lnClientName->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\262\320\276\320\265 \320\270\320\274\321\217. . .", nullptr));
        cmbStatus->setItemText(0, QCoreApplication::translate("MainWindow", "\320\235\320\265\321\202", nullptr));
        cmbStatus->setItemText(1, QCoreApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\321\203\320\277\320\265\320\275", nullptr));
        cmbStatus->setItemText(2, QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\321\210\320\265\320\273", nullptr));
        cmbStatus->setItemText(3, QCoreApplication::translate("MainWindow", "\320\235\320\265\320\264\320\276\321\201\321\202\321\203\320\277\320\265\320\275", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265:", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnSendFile->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\321\203:", nullptr));
        cmbDestination->setItemText(0, QCoreApplication::translate("MainWindow", "Server", nullptr));
        cmbDestination->setItemText(1, QCoreApplication::translate("MainWindow", "ALL", nullptr));

        btnShowHistory->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\202\320\276\321\200\320\270\321\217", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
