#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include "ClientManager.h"

#include <QDir>
#include <QTcpSocket>
#include <QWidget>

namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *client, QWidget *parent = nullptr);
    void disconnect(); // Метод для отключения клиента
    ~ClientChatWidget();
private slots:
    // Слоты , которые вызываются в ответ на сигналы
    void clientDisconnected();
    void on_btnSend_clicked();
    void textMessageReceived(QString message, QString receiver);
    void onTyping();
    void onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize);
    void onFileSaved(QString path);
    void on_lblOpenFolder_linkActivated(const QString &link);
    void onClientNameChanged(QString prevName, QString name);
signals:
    // Сигналы, для оповещения других частей программы о происходящих событиях
    void clientNameChanged(QString prevName, QString name);
    void isTyping(QString message);
    void statusChanged(ChatProtocol::Status status);
    void textForOtherClients(QString message, QString receiver, QString sender);
private:
    Ui::ClientChatWidget *ui;
    ClientManager *_client;
    QDir dir;
};

#endif
