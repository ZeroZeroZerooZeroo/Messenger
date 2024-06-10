#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QByteArray>
#include <QString>
#include <QFileInfo>
#include <QIODevice>

class ChatProtocol
{
public:

    // Перечисление типов сообщений
    enum MessageType {
        Text, // Текстовое сообщение
        IsTyping, // Сообщение о наборе текста
        SetName, // Сообщение для установки имени
        SetStatus, // Сообщение для установки статуса
        InitSendingFile, // Инициализация отправки файла
        AcceptSendingFile, // Принятие отправки файла
        RejectSendingFile, // Отклонение отправки файла
        SendFile, // Отправка файла
        ClientName, // Имя клиента
        ConnectionACK, // Подтверждение подключения
        NewClient, // Новый клиент
        ClientDisconnected // Отключение клиента
    };

    // Перечисление статусов
    enum Status {
        None, // Нет статуса
        Available, // Доступен
        Away, // Нет на месте
        Busy // Занят
    };

    ChatProtocol();

    // Методы для различных сообщений
    QByteArray textMessage(QString message, QString receiver);
    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString name);
    QByteArray setStatusMessage(Status status);
    QByteArray setInitSendingFileMessage(QString fileName);
    QByteArray setAcceptFileMessage();
    QByteArray setRejectFileMessage();
    QByteArray setFileMessage(QString fileName);
    QByteArray setClientNameMessage(QString prevName, QString name);
    QByteArray setConnectionACKMessage(QString clientName, QStringList otherClients);
    QByteArray setNewClientMessage(QString clientName);
    QByteArray setClinetDisconnectedMessage(QString clientName);

    // Метод загрузки данных
    void loadData(QByteArray data);

    // Геттеры для полей класса
    const QString &message() const;
    const QString &name() const;
    Status status() const;
    MessageType type() const;
    const QString &fileName() const;
    qint64 fileSize() const;
    const QByteArray &fileData() const;
    const QString &receiver() const;

private:
    // Метод для сериализации данных
    QByteArray getData(MessageType type, QString data);

    // Поля класса для хранения данных сообщений
    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
    QString _fileName;
    qint64 _fileSize;
    QByteArray _fileData;
    QString _receiver;
};

#endif
