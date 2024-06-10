#include "ServerManager.h"

ServerManager::ServerManager(ushort port, QObject *parent)
    : QObject{parent}
{
    setupServer(port);
    setupDatabase();

}

// Метод записи в файл логов
void ServerManager::logToFile(const QString &message) {
    QFile file("server_log.txt");

    // ЕСли файл открыт
    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        // Запись текущей даты и времени в формате и строки сообщения
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "n";

        // Закрытие файла
        file.close();
    } else {
        // В случае ошибки
        qDebug() << "Ошибка: невозможно открыть файл журнала для записи.";
    }
}

// Метод для уведомления других клиентов о смене имени клиента
void ServerManager::notifyOtherClients(QString prevName, QString name)
{
    //Запись об изменении в файл логов
    auto logMessage = QString("Имя клиента изменено: %1 -> %2").arg(prevName).arg(name);
    logToFile(logMessage);

    // Создание сообщения о смене имени с помощью протокола
    auto message = _protocol.setClientNameMessage(prevName, name);

    foreach (auto cl, _clients) {

        // Получение имени текущего клиента
        auto clientName = cl->property("clientName").toString();

        if (clientName != name) {
            cl->write(message);
        }
    }
}

// Инициализация БД
void ServerManager::setupDatabase() {

    // Подключение к базе данных SQLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("chat_server.db");

    // ЕСли невозможно подключиться
    if (!db.open()) {
        qDebug() << "Ошибка: Невозможно подключиться к базе данных.";
    }

    // Создание таблицы сообщений
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS messages ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "sender TEXT, "
               "receiver TEXT, "
               "message TEXT, "
               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");

    // Если невозможно создать таблицу
    if (!query.isActive()) {
        qDebug() << "Ошибка: Невозможно создать таблицу" << query.lastError().text();
    }
}

// Метод для пересылки текстового сообщения другим клиентам
void ServerManager::onTextForOtherClients(QString message, QString receiver, QString sender)
{
    // Сохранение сообщения в БД
    QSqlQuery query;
    query.prepare("INSERT INTO messages (sender, receiver, message) VALUES (?, ?, ?)");
    query.addBindValue(sender);
    query.addBindValue(receiver);
    query.addBindValue(message);
    if (!query.exec()) {
        qDebug() << "Ошибка: Невозможно вставить сообщение" << query.lastError().text();
    }

    QString listItem;
    listItem = QString("%1: %2").arg(sender, message);  // Добавление имени отправителя перед сообщением

    auto msg = _protocol.textMessage(message, receiver);
    // Если сообщение предназначено всем клиентам
    if (receiver == "All") {

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

        foreach (auto cl, _clients) {

            // Получение имени текущего клиента
            auto clientName = cl->property("clientName").toString();

            // Если имя клиента совпадает с получателем
            if (clientName == receiver) {

                // Отправка ему сообщения
                cl->write(msg);

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

    // Определение ID нового клиента
    auto id = _clients.count() + 1;

    // Создание имени нового клиента
    auto clientName = QString("Клиент (%1)").arg(id);

    // Установка свойства ID для клиента
    client->setProperty("id", id);

    // Установка свойства "clientName" для клиента
    client->setProperty("clientName", clientName);

    // Запись в файл логов
    logToFile(QString("Добавлен новый клиент: %1 с  ID %2").arg(clientName).arg(id));

    // Подключение сигнала "disconnected" сокета к слоту onClientDisconnected
    connect(client, &QTcpSocket::disconnected, this, &ServerManager::onClientDisconnected);

    // Вызов сигнала newClientConnected
    emit newClientConnected(client);

    // Если это не первый клиент
    if (id > 1) {
        auto message = _protocol.setConnectionACKMessage(clientName, _clients.keys());

        // Отправка сообщения новому клиенту
        client->write(message);

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
    auto client = qobject_cast<QTcpSocket *>(sender());

    // Получение имени клиента
    auto clientName = client->property("clientName").toString();

    // Запись в файл логов
    logToFile(QString("Клиент отключен: %1").arg(clientName));

    // Удаление клиента из списка клиентов
    _clients.remove(clientName);

    auto message = _protocol.setClinetDisconnectedMessage(clientName);

    // Цикл по оставшимся клиентам
    foreach (auto cl, _clients) {
        // Отправка им сообщения об отключении клиента
        cl->write(message);
    }

    // Вызов сигнала clientDisconnected
    emit clientDisconnected(client);
}

void ServerManager::setupServer(ushort port)
{

    _server = new QTcpServer(this);

    // Подключение сигнала newConnection к слоту newClientConnectionReceived
    connect(_server, &QTcpServer::newConnection, this, &ServerManager::newClientConnectionReceived);

    // Начало прослушивания порта на всех адресах
    _server->listen(QHostAddress::Any, port);
}
