/********************************************************************************
** Form generated from reading UI file 'ClientChatWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTCHATWIDGET_H
#define UI_CLIENTCHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientChatWidget
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *lstMessages;
    QWidget *wdgSend;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lnMessage;
    QPushButton *btnSend;

    void setupUi(QWidget *ClientChatWidget)
    {
        if (ClientChatWidget->objectName().isEmpty())
            ClientChatWidget->setObjectName("ClientChatWidget");
        ClientChatWidget->resize(478, 345);
        verticalLayout = new QVBoxLayout(ClientChatWidget);
        verticalLayout->setObjectName("verticalLayout");
        lstMessages = new QListWidget(ClientChatWidget);
        lstMessages->setObjectName("lstMessages");

        verticalLayout->addWidget(lstMessages);

        wdgSend = new QWidget(ClientChatWidget);
        wdgSend->setObjectName("wdgSend");
        horizontalLayout = new QHBoxLayout(wdgSend);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(wdgSend);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lnMessage = new QLineEdit(wdgSend);
        lnMessage->setObjectName("lnMessage");

        horizontalLayout->addWidget(lnMessage);

        btnSend = new QPushButton(wdgSend);
        btnSend->setObjectName("btnSend");

        horizontalLayout->addWidget(btnSend);


        verticalLayout->addWidget(wdgSend);


        retranslateUi(ClientChatWidget);

        QMetaObject::connectSlotsByName(ClientChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientChatWidget)
    {
        ClientChatWidget->setWindowTitle(QCoreApplication::translate("ClientChatWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("ClientChatWidget", "Message:", nullptr));
        btnSend->setText(QCoreApplication::translate("ClientChatWidget", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientChatWidget: public Ui_ClientChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTCHATWIDGET_H
