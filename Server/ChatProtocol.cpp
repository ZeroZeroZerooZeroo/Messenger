#include "ChatProtocol.h"

#include <QFileInfo>
#include <QIODevice>

ChatProtocol::ChatProtocol() {}

QByteArray ChatProtocol::textMessage(QString message)
{
    return getData(Text,message);
}

QByteArray ChatProtocol::isTypingMessage()
{
    return getData(IsTyping,"");
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
    out<<SetStatus<<status;
    return ba;
}

QByteArray ChatProtocol::setInitSendingFileMessage(QString fileName)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    QFileInfo info(fileName);
    out<<InitSendingFile<<info.fileName()<<info.size();
    return ba;
}

QByteArray ChatProtocol::setAcceptFileMessage()
{
    return getData(AcceptSendingFile,"");

}

QByteArray ChatProtocol::setRejectFileMessage()
{
    return getData(RejectSendingFile,"");

}

QByteArray ChatProtocol::setFileMessage(QString fileName)
{
    QByteArray ba;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream out(&ba, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_0);
        QFileInfo info(fileName);
        out<<SendFile<<info.fileName()<<info.size()<<file.readAll();
        file.close();
    }

    return ba;
}

void ChatProtocol::loadData(QByteArray data)
{
    QDataStream in(&data,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in>>_type;
    switch (_type) {
    case Text:
        in>>_message;
        break;
    case SetName:
        in>>_name;
        break;
    case SetStatus:
        in>>_status;
        break;
    case InitSendingFile:
        in>>_fileName>>_fileSize;
        break;
    case SendFile:
        in>>_fileName>>_fileData;
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
    out<<type<<data;
    return ba;
}

QByteArray ChatProtocol::fileData() const
{
    return _fileData;
}

qint64 ChatProtocol::fileSize() const
{
    return _fileSize;
}

QString ChatProtocol::fileName() const
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

QString ChatProtocol::name() const
{
    return _name;
}

QString ChatProtocol::message() const
{
    return _message;
}

//void ChatProtocol::setMessage(const QString &newMessage)
//{
//    if (_message == newMessage)
//        return;
//    _message = newMessage;
//   emit messageChanged();
//}

//void ChatProtocol::resetMessage()
//{
//    setMessage({}); // TODO: Adapt to use your actual default value
//}
