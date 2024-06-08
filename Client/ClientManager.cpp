#include "ClientManager.h"

ClientManager::ClientManager(QHostAddress ip, ushort port, QObject *parent)
    : QObject{parent},
      _ip(ip),
      _port(port)
{
    setupClient();
}

void ClientManager::connectToServer()
{
    // Подключение к серверу по заданному IP-адресу и порту
    _socket->connectToHost(_ip, _port);
}

void ClientManager::sendMessage(QString message, QString receiver)
{
    // Отправка текстового сообщения серверу через сокет
    _socket->write(_protocol.textMessage(message, receiver));
}

void ClientManager::sendName(QString name)
{
    // Отправка сообщения об изменении имени
    _socket->write(_protocol.setNameMessage(name));
}

void ClientManager::sendStatus(ChatProtocol::Status status)
{
    // Отправка сообщения об изменении статуса
    _socket->write(_protocol.setStatusMessage(status));
}

void ClientManager::sendIsTyping()
{
    // Отправка сообщения о наборе текста
    _socket->write(_protocol.isTypingMessage());
}

void ClientManager::sendInitSendingFile(QString fileName)
{
    _tmpFileName = fileName;  // Сохранение имени файла во временное поле
    _socket->write(_protocol.setInitSendingFileMessage(fileName));  // Отправка сообщения об инициализации отправки файла
}

void ClientManager::sendAcceptFile()
{
    // Отправка сообщения о принятии файла
    _socket->write(_protocol.setAcceptFileMessage());
}

void ClientManager::sendRejectFile()
{
    // Отправка сообщения об отклонении файла
    _socket->write(_protocol.setRejectFileMessage());
}

void ClientManager::readyRead()
{
    auto data = _socket->readAll();  // Чтение всех данных из сокета
    _protocol.loadData(data);  // Загрузка данных в объект протокола
    switch (_protocol.type()) {
    case ChatProtocol::Text:
        emit textMessageReceived(_protocol.message());  // Отправка сигнала о получении текстового сообщения
        break;
    case ChatProtocol::SetName:
        emit nameChanged(_protocol.name());  // Отправка сигнала об изменении имени
        break;
    case ChatProtocol::SetStatus:
        emit statusChanged(_protocol.status());  // Отправка сигнала об изменении статуса
        break;
    case ChatProtocol::IsTyping:
        emit isTyping();  // Отправка сигнала о наборе текста
        break;
    case ChatProtocol::InitSendingFile:
        emit initReceivingFile(_protocol.name(), _protocol.fileName(), _protocol.fileSize());  // Отправка сигнала об инициализации получения файла
        break;
    case ChatProtocol::AcceptSendingFile:
        sendFile();  // Отправка файла
        break;
    case ChatProtocol::RejectSendingFile:
        emit rejectReceivingFile();  // Отправка сигнала об отклонении получения файла
        break;
    case ChatProtocol::ConnectionACK:
        emit connectionACK(_protocol.myName(), _protocol.clientsName());  // Отправка сигнала об успешном подключении
        break;
    case ChatProtocol::NewClient:
        emit newClientConnectedToServer(_protocol.clientName());  // Отправка сигнала о подключении нового клиента
        break;
    case ChatProtocol::ClientDisconnected:
        emit clientDisconnected(_protocol.clientName());  // Отправка сигнала об отключении клиента
        break;
    case ChatProtocol::ClientName:
        emit clientNameChanged(_protocol.prevName(), _protocol.clientName());  // Отправка сигнала об изменении имени клиента
        break;
    default:
        break;
    }
}

void ClientManager::setupClient()
{
    _socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &ClientManager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &ClientManager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &ClientManager::readyRead);
}

void ClientManager::sendFile()
{
    // Отправка файла через сокет
    _socket->write(_protocol.setFileMessage(_tmpFileName));
}



