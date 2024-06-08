#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "ChatProtocol.h"

#include <QObject>
#include <QTcpSocket>

class ClientManager : public QObject
{
    Q_OBJECT
public:
    // Конструктор с параметрами IP и порта для нового подключения клиента
    explicit ClientManager(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
     // Конструктор с параметром сокета для использования уже существующего подключения
    explicit ClientManager(QTcpSocket *client, QObject *parent = nullptr);

    // Метод для подключения к серверу
    void connectToServer();
    // Метод для отключения от сервера
    void disconnectFromHost();
    // Метод для отправки текстового сообщения
    void sendMessage(QString message);
     // Метод для отправки имени клиента
    void sendName(QString name);
    // Метод для отправки статуса клиента
    void sendStatus(ChatProtocol::Status status);
    // Метод для получения имени клиента
    QString name() const;
    // Метод для отправки уведомления о наборе текста
    void sendIsTyping();
    // Метод для инициализации отправки файла
    void sendInitSendingFile(QString fileName);
    // Метод для отправки подтверждения приема файла
    void sendAcceptFile();
    // Метод для отправки отклонения приема файла
    void sendRejectFile();

signals:
    // Сигнал об успешном подключении к серверу
    void connected();

    // Сигнал об отключении от сервера
    void disconnected();

    // Сигнал о получении текстового сообщения
    void textMessageReceived(const QString message, QString receiver);

    // Сигнал о наборе текста клиентом
    void isTyping();

    // Сигнал об изменении имени клиента
    void nameChanged(QString prevName, QString name);

    // Сигнал об изменении статуса клиента
    void statusChanged(ChatProtocol::Status status);

    // Сигнал об отклонении приема файла
    void rejectReceivingFile();

    // Сигнал о начале приема файла
    void initReceivingFile(QString clientName, QString fileName, qint64 fileSize);

    // Сигнал о сохранении файла
    void fileSaved(QString path);
private slots:
    // Слот для обработки данных, готовых для чтения
    void readyRead();

private:
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;
    QString _tmpFileName;
    void setupClient();
    void sendFile();
    void saveFile();
};

#endif
