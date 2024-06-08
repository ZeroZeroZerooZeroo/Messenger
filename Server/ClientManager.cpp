#include "ClientManager.h"

#include <QDir>

ClientManager::ClientManager(QHostAddress ip, ushort port, QObject *parent)
    : QObject{parent},
      _ip(ip),
      _port(port)
{
    _socket = new QTcpSocket(this); // Создание объекта TCP-сокета
    setupClient(); // Вызов метода настройки клиента
}

ClientManager::ClientManager(QTcpSocket *client, QObject *parent)
    : QObject{parent},
    _socket(client)
{
    setupClient();
}

// Метод для подключения к серверу
void ClientManager::connectToServer()
{
    _socket->connectToHost(_ip, _port); // Установка соединения с сервером
}

// Метод для отключения от сервера
void ClientManager::disconnectFromHost()
{
    _socket->disconnectFromHost(); // Закрытие соединения с сервером
}

// Метод для отправки текстового сообщения
void ClientManager::sendMessage(QString message)
{
    _socket->write(_protocol.textMessage(message, name())); // Отправка сообщения через сокет
}

// Метод для отправки имени клиента
void ClientManager::sendName(QString name)
{
    _socket->write(_protocol.setNameMessage(name)); // Отправка имени через сокет
}

// Метод для отправки статуса клиента
void ClientManager::sendStatus(ChatProtocol::Status status)
{
    _socket->write(_protocol.setStatusMessage(status)); // Отправка статуса через сокет
}

// Метод для получения имени клиента
QString ClientManager::name() const
{
    auto id = _socket->property("id").toInt(); // Получение ID клиента из свойств сокета
    auto name = _protocol.name().length() > 0 ? _protocol.name() : QString("Client (%1)").arg(id); // Получение имени клиента с учётом ID
    return name; // Возвращение имени
}

// Метод для отправки уведомления о наборе текста
void ClientManager::sendIsTyping()
{
    _socket->write(_protocol.isTypingMessage()); // Отправка уведомления через сокет
}


// Метод для инициализации отправки файла
void ClientManager::sendInitSendingFile(QString fileName)
{
    _tmpFileName = fileName; // Сохранение имени файла
    _socket->write(_protocol.setInitSendingFileMessage(fileName)); // Отправка сообщения о начале отправки файла через сокет
}

// Метод для отправки подтверждения приема файла
void ClientManager::sendAcceptFile()
{
    _socket->write(_protocol.setAcceptFileMessage()); // Отправка подтверждения через сокет
}

// Метод для отправки отклонения приема файла
void ClientManager::sendRejectFile()
{
    _socket->write(_protocol.setRejectFileMessage()); // Отправка сообщения об отклонении через сокет
}
// Слот для обработки данных, готовых для чтения
void ClientManager::readyRead()
{
    auto data = _socket->readAll(); // Чтение всех доступных данных из сокета
    _protocol.loadData(data); // Загрузка полученных данных в протокол
    switch (_protocol.type()) { // Проверка типа сообщения
    case ChatProtocol::Text:
        emit textMessageReceived(_protocol.message(), _protocol.receiver()); // Эмитирование сигнала о получении текстового сообщения
        break;
    case ChatProtocol::SetName:{
        auto prevName = _socket->property("clientName").toString(); // Получение предыдущего имени клиента
        _socket->setProperty("clientName", name()); // Установка нового имени клиента
        emit nameChanged(prevName, name()); // Эмитирование сигнала об изменении имени клиента
        break;
    }
    case ChatProtocol::SetStatus:
        emit statusChanged(_protocol.status()); // Эмитирование сигнала об изменении статуса клиента
        break;
    case ChatProtocol::IsTyping:
        emit isTyping(); // Эмитирование сигнала о наборе текста клиентом
        break;
    case ChatProtocol::InitSendingFile:
        emit initReceivingFile(_protocol.name(), _protocol.fileName(), _protocol.fileSize()); // Эмитирование сигнала о начале приема файла
        break;
    case ChatProtocol::AcceptSendingFile:
        sendFile(); // Вызов метода для отправки файла
        break;
    case ChatProtocol::RejectSendingFile:
        emit rejectReceivingFile(); // Эмитирование сигнала об отклонении приема файла
        break;
    case ChatProtocol::SendFile:
        saveFile(); // Вызов метода для сохранения файла
        break;
    default:
        break;
    }
}

// Метод для настройки клиента
void ClientManager::setupClient()
{
    connect(_socket, &QTcpSocket::connected, this, &ClientManager::connected); // Подключение сигнала о подключении к серверу к соответствующему слоту
    connect(_socket, &QTcpSocket::disconnected, this, &ClientManager::disconnected); // Подключение сигнала об отключении от сервера к соответствующему слоту
    connect(_socket, &QTcpSocket::readyRead, this, &ClientManager::readyRead); // Подключение сигнала о готовности данных к чтению к соответствующему слоту
}

// Метод для отправки файла
void ClientManager::sendFile()
{
    _socket->write(_protocol.setFileMessage(_tmpFileName)); // Отправка файла через сокет
}

// Метод для сохранения файла
void ClientManager::saveFile()
{
    QDir dir; // Создание объекта QDir для работы с директориями
    dir.mkdir(name()); // Создание директории с именем клиента
    auto path = QString("%1/%2/%3_%4") // Формирование пути сохранения файла
                    .arg(dir.canonicalPath(), name(), QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"), _protocol.fileName());
    QFile file(path); // Создание файла по сформированному пути
    if (file.open(QIODevice::WriteOnly)) { // Открытие файла для записи
        file.write(_protocol.fileData()); // Запись данных в файл
        file.close(); // Закрытие файла
        emit fileSaved(path); // Эмитирование сигнала о сохранении файла
    }
}

