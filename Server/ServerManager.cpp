#include "ServerManager.h"

ServerManager::ServerManager(ushort port, QObject *parent)
    : QObject{parent}
{
    setupServer(port);
}

// Метод для уведомления других клиентов о смене имени клиента
void ServerManager::notifyOtherClients(QString prevName, QString name)
{
    // Создание сообщения о смене имени с помощью протокола
    auto message = _protocol.setClientNameMessage(prevName, name);
    // Цикл по списку клиентов
    foreach (auto cl, _clients) {
        // Получение имени текущего клиента из его свойств
        auto clientName = cl->property("clientName").toString();
        // Если клиент не тот, кто сменил имя
        if (clientName != name) {
            // Отправка ему сообщения
            cl->write(message);
        }
    }
}

// Метод для пересылки текстового сообщения другим клиентам
void ServerManager::onTextForOtherClients(QString message, QString receiver, QString sender)
{
    // Создание текстового сообщения с помощью протокола
    auto msg = _protocol.textMessage(message, receiver);
    // Если сообщение предназначено всем клиентам
    if (receiver == "All") {
        // Цикл по списку клиентов
        foreach (auto cl, _clients) {
            // Получение имени текущего клиента
            auto clientName = cl->property("clientName").toString();
            // Если клиент не отправитель
            if (clientName != sender) {
                // Отправка ему сообщения
                cl->write(msg);
            }
        }
    }
    else { // Если сообщение имеет конкретного получателя
        // Цикл по списку клиентов
        foreach (auto cl, _clients) {
            // Получение имени текущего клиента
            auto clientName = cl->property("clientName").toString();
            // Если имя клиента совпадает с получателем
            if (clientName == receiver) {
                // Отправка ему сообщения
                cl->write(msg);
                // Завершение метода
                return;
            }
        }
    }
}

// Слот, вызываемый при новом подключении клиента
void ServerManager::newClientConnectionReceived()
{
    // Получение сокета нового клиента
    auto client = _server->nextPendingConnection();

    // Определение идентификатора нового клиента
    auto id = _clients.count() + 1;
    // Создание имени нового клиента
    auto clientName = QString("Client (%1)").arg(id);
    // Установка свойства "id" для клиента
    client->setProperty("id", id);
    // Установка свойства "clientName" для клиента
    client->setProperty("clientName", clientName);

    // Подключение сигнала "disconnected" сокета к слоту onClientDisconnected
    connect(client, &QTcpSocket::disconnected, this, &ServerManager::onClientDisconnected);
    // Вызов сигнала newClientConnected с переданным клиентом
    emit newClientConnected(client);

    // Если это не первый клиент
    if (id > 1) {
        // Создание сообщения об успешном подключении с помощью протокола
        auto message = _protocol.setConnectionACKMessage(clientName, _clients.keys());
        // Отправка сообщения новому клиенту
        client->write(message);

        // Создание сообщения о новом клиенте с помощью протокола
        auto newClientMessage = _protocol.setNewClientMessage(clientName);
        // Цикл по списку существующих клиентов
        foreach (auto cl, _clients) {
            // Отправка им сообщения о новом клиенте
            cl->write(newClientMessage);
        }
    }
    // Добавление нового клиента в список клиентов
    _clients[clientName] = client;
}

// Слот, вызываемый при отключении клиента
    void ServerManager::onClientDisconnected()
{
    // Получение указателя на отправителя сигнала, приведенного к типу QTcpSocket
    auto client = qobject_cast<QTcpSocket *>(sender());
    // Получение имени клиента из его свойств
    auto clientName = client->property("clientName").toString();
    // Удаление клиента из списка клиентов
    _clients.remove(clientName);
    // Создание сообщения об отключении клиента с помощью протокола
    auto message = _protocol.setClinetDisconnectedMessage(clientName);
    // Цикл по оставшимся клиентам
    foreach (auto cl, _clients) {
        // Отправка им сообщения об отключении клиента
        cl->write(message);
    }

    // Вызов сигнала clientDisconnected с переданным клиентом
    emit clientDisconnected(client);
}

// Метод для настройки сервера
void ServerManager::setupServer(ushort port)
{
    // Создание объекта сервера
    _server = new QTcpServer(this);
    // Подключение сигнала newConnection объекта _server к слоту newClientConnectionReceived
    connect(_server, &QTcpServer::newConnection, this, &ServerManager::newClientConnectionReceived);
    // Начало прослушивания порта на всех адресах
    _server->listen(QHostAddress::Any, port);
}
