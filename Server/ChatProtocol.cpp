#include "ChatProtocol.h"

ChatProtocol::ChatProtocol()
{

}

QByteArray ChatProtocol::textMessage(QString message, QString receiver)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << Text << receiver << message; // Запись типа сообщения, получателя и текста сообщения
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
    out << SetStatus << status; // Запись типа сообщения и статуса
    return ba;
}

QByteArray ChatProtocol::setInitSendingFileMessage(QString fileName)
{
    QByteArray ba;
    QFileInfo info(fileName);
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << InitSendingFile << info.fileName() << info.size(); // Запись типа сообщения, имени файла и его размера
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
        QFileInfo info(fileName);
        QDataStream out(&ba, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_0);
        out << SendFile << info.fileName() << info.size() << file.readAll(); // Запись типа сообщения, имени файла, его размера и данных
        file.close();
    }
    return ba;
}

QByteArray ChatProtocol::setClientNameMessage(QString prevName, QString name)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << ClientName << prevName << name; // Запись типа сообщения, предыдущего и нового имени
    return ba;
}

QByteArray ChatProtocol::setConnectionACKMessage(QString clientName, QStringList otherClients)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << ConnectionACK << clientName << otherClients; // Запись типа сообщения, имени клиента и списка других клиентов
    return ba;
}

QByteArray ChatProtocol::setNewClientMessage(QString clientName)
{
    return getData(NewClient, clientName);
}

QByteArray ChatProtocol::setClinetDisconnectedMessage(QString clientName)
{
    return getData(ClientDisconnected, clientName);
}

void ChatProtocol::loadData(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in >> _type; // Чтение типа сообщения
    switch (_type) { // Переключение по типу сообщения
    case Text:
        in >> _receiver >> _message; // Чтение получателя и текста сообщения
        break;
    case SetName:
        in >> _name; // Чтение имени
        break;
    case SetStatus:
        in >> _status; // Чтение статуса
        break;
    case InitSendingFile:
        in >> _fileName >> _fileSize; // Чтение имени файла и его размера
        break;
    case SendFile:
        in >> _fileName >> _fileSize >> _fileData; // Чтение имени файла, его размера и данных
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
    out << type << data; // Запись типа сообщения и данных
    return ba;
}

//Реализации геттеров
const QString &ChatProtocol::receiver() const
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
