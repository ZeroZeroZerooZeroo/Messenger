#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include "ClientManager.h"

#include <QWidget>
#include <QTcpSocket>
#include <qdir.h>
namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *client,QWidget *parent = nullptr);
    ~ClientChatWidget();

private slots:

    void on_btnSend_clicked();
    void clientDisconnected();

    void textMessageReceived(QString message);
    void onTyping();

    void onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize);
    void onFileSaved(QString path);
    void on_lblOpenFolder_linkActivated(const QString &link);


    void onClientNameChanged(QString name);
signals:
    void clientNameChanged(QString name);
    void isTyping(QString message);
    void statusChanged(ChatProtocol::Status status);

private:
    Ui::ClientChatWidget *ui;
    ClientManager *_client;
    QDir dir;
};

#endif // CLIENTCHATWIDGET_H
