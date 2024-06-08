#include "ChatProtocol.h"

#include <QFileInfo>
#include <QIODevice>

ChatProtocol::ChatProtocol()
{

}

QByteArray ChatProtocol::textMessage(QString message, QString receiver)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    // Записывается тип сообщения, получателя и само сообщение
    out << Text << receiver << message;
    return ba;
}

QByteArray ChatProtocol::isTypingMessage()
{
    return getData(IsTyping, "");
}

QByteArray ChatProtocol::setNameMessage(QString name)
{
    return getData(SetName, name);
}

QByteArray ChatProtocol::setStatusMessage(Status status)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    // Записывается тип сообщения и статус
    out << SetStatus << status;
    return ba;
}

QByteArray ChatProtocol::setInitSendingFileMessage(QString fileName)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    QFileInfo info(fileName);  // Получкние информации о файле
    // Записывается тип сообщения, имя файла и размер файла
    out << InitSendingFile << info.fileName() << info.size();
    return ba;
}

QByteArray ChatProtocol::setAcceptFileMessage()
{
    return getData(AcceptSendingFile, "");
}

QByteArray ChatProtocol::setRejectFileMessage()
{
    return getData(RejectSendingFile, "");
}


QByteArray ChatProtocol::setFileMessage(QString fileName)
{
    QByteArray ba;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream out(&ba, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_0);
        QFileInfo info(fileName); // Получение информации о файле
        // Записывается тип сообщения, имя файла, размер файла и данные файла
        out << SendFile << info.fileName() << info.size() << file.readAll();
        file.close(); // Закрытие файла
    }
    return ba;
}

void ChatProtocol::loadData(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in >> _type; // Считывание типа сообщения
    switch (_type) {
    case Text:
        in >> _receiver >> _message; // Считывание получателя и сообщения
        break;
    case SetName:
        in >> _name; // Считывание имени
        break;
    case SetStatus:
        in >> _status; // Считывание статуса
        break;
    case InitSendingFile:
        in >> _fileName >> _fileSize; // Считывание имение и размера файла
        break;
    case SendFile:
        in >> _fileName >> _fileSize >> _fileData; // Считывание имени файла, размера файла и данных файла
        break;
    case ClientName:
        in >> _prevName >> _clientName; // Считывание предыдущего и нового имени клиента
        break;
    case NewClient:
    case ClientDisconnected:
        in >> _clientName; // Считывание имени отключенного клиента
        break;
    case ConnectionACK:
        in >> _myName >> _clientsName; // Считывание своего имени и списка имён клиентов
        break;
    default:
        break;
    }
}

QByteArray ChatProtocol::getData(MessageType type, QString data)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << type << data; // Записывается тип сообщения и данные
    return ba;
}

// Реализации геттеров
const QString &ChatProtocol::myName() const
{
    return _myName;
}

const QStringList &ChatProtocol::clientsName() const
{
    return _clientsName;
}

const QString &ChatProtocol::prevName() const
{
    return _prevName;
}

const QString &ChatProtocol::clientName() const
{
    return _clientName;
}

QString ChatProtocol::receiver() const
{
    return _receiver;
}

const QByteArray &ChatProtocol::fileData() const
{
    return _fileData;
}

qint64 ChatProtocol::fileSize() const
{
    return _fileSize;
}

const QString &ChatProtocol::fileName() const
{
    return _fileName;
}

ChatProtocol::MessageType ChatProtocol::type() const
{
    return _type;
}

ChatProtocol::Status ChatProtocol::status() const
{
    return _status;
}

const QString &ChatProtocol::name() const
{
    return _name;
}

const QString &ChatProtocol::message() const
{
    return _message;
}
