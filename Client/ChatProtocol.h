#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QByteArray>
#include <QString>
#include <QStringList>


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

    // Конструктор
    ChatProtocol();

    // Методы для создания сообщений различных типов
    QByteArray textMessage(QString message, QString receiver);
    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString name);
    QByteArray setStatusMessage(Status status);
    QByteArray setInitSendingFileMessage(QString fileName);
    QByteArray setAcceptFileMessage();
    QByteArray setRejectFileMessage();
    QByteArray setFileMessage(QString fileName);

    // Метод для загрузки данных
    void loadData(QByteArray data);

    // Геттеры для различных данных
    const QString &message() const;
    const QString &name() const;
    Status status() const;
    MessageType type() const;
    const QString &fileName() const;
    qint64 fileSize() const;
    const QByteArray &fileData() const;
    QString receiver() const;
    const QString &clientName() const;
    const QString &prevName() const;
    const QStringList &clientsName() const;
    const QString &myName() const;

private:

    // Метод для сериализации данных
    QByteArray getData(MessageType type, QString data);

    // Поля для хранения данных
    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
    QString _fileName;
    qint64 _fileSize;
    QByteArray _fileData;
    QString _receiver;
    QString _clientName;
    QString _prevName;
    QStringList _clientsName;
    QString _myName;

};

#endif
