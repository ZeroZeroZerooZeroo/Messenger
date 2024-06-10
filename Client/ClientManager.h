#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "ChatProtocol.h"

#include <QObject>
#include <QTcpSocket>

class ClientManager : public QObject
{
    Q_OBJECT

public:
    // Конструктор класса с заданием IP-адреса и порта
    explicit ClientManager(QHostAddress ip = QHostAddress("192.168.0.12"), ushort port = 4500, QObject *parent = nullptr);

    // Метод для подключения к серверу
    void connectToServer();

    // Методы для отправки различных типов сообщений
    void sendMessage(QString message, QString receiver);
    void sendName(QString name);
    void sendStatus(ChatProtocol::Status status);
    void sendIsTyping();
    void sendInitSendingFile(QString fileName);
    void sendAcceptFile();
    void sendRejectFile();

signals:

    // Сигналы для различных событий
    void connected();
    void disconnected();
    void textMessageReceived(QString message);
    void isTyping();
    void nameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);
    void rejectReceivingFile();
    void initReceivingFile(QString clientName, QString fileName, qint64 fileSize);
    void connectionACK(QString myName, QStringList clientsName);
    void newClientConnectedToServer(QString clienName);
    void clientNameChanged(QString prevName, QString clientName);
    void clientDisconnected(QString clientName);

private slots:

    // Слот, вызываемый при получении данных
    void readyRead();

private:

    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;
    QString _tmpFileName;

    // Метод для настройки клиента
    void setupClient();

    // Метод для отправки файла
    void sendFile();
};

#endif
