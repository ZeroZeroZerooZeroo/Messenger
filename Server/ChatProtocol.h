#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QByteArray>
#include <QString>


class ChatProtocol
{
public:

    enum MessageType{
        Text,
        IsTyping,
        SetName,
        SetStatus,
        InitSendingFile,
        AcceptSendingFile,
        RejectSendingFile,
        SendFile
    };

    enum Status{
        None,
        Available,
        Away,
        Busy
    };

    ChatProtocol();

    QByteArray textMessage(QString message);
    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString name);
    QByteArray setStatusMessage(Status status);
    QByteArray setInitSendingFileMessage(QString fileName);
    QByteArray setAcceptFileMessage();
    QByteArray setRejectFileMessage();
    QByteArray setFileMessage(QString fileName);

    void loadData(QByteArray data);
    QString message() const;
    void setMessage(const QString &newMessage);
    void resetMessage();

    QString name() const;

    Status status() const;




    MessageType type() const;

    QString fileName() const;

    qint64 fileSize() const;

    QByteArray fileData() const;

signals:
    void messageChanged();

private:
    QByteArray getData(MessageType type,QString data);

    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
    QString _fileName;
    qint64 _fileSize;
    QByteArray _fileData;
    Q_PROPERTY(QString message READ message WRITE setMessage RESET resetMessage NOTIFY messageChanged FINAL)
};

#endif // CHATPROTOCOL_H
