#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "ChatProtocol.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(ushort port = 4500, QObject *parent = nullptr);

    // Метод для уведомления других клиентов об изменении имени
    void notifyOtherClients(QString prevName, QString name);

public slots:
    // Слот для обработки сообщения для других клиентов
    void onTextForOtherClients(QString message, QString receiver, QString sender);
signals:
    // Сигнал о новом подключившемся клиенте
    void newClientConnected(QTcpSocket *client);

    // Сигнал об отключении клиента
    void clientDisconnected(QTcpSocket *client);
private slots:
    // Слот для обработки нового подключения клиента
    void newClientConnectionReceived();
    // Слот для обработки отключения клиента
    void onClientDisconnected();

private:
    QTcpServer *_server;
    QMap<QString, QTcpSocket *> _clients;
    ChatProtocol _protocol;
    void setupServer(ushort port);
};

#endif
