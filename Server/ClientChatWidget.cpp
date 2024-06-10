#include "ClientChatWidget.h"
#include "ui_ClientChatWidget.h"

ClientChatWidget::ClientChatWidget(QTcpSocket *client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientChatWidget)
{
    ui->setupUi(this);
    _client = new ClientManager(client, this);
    connect(_client, &ClientManager::disconnected, this, &ClientChatWidget::clientDisconnected); // Соединение сигнала "disconnected" клиента с методом clientDisconnected
    connect(_client, &ClientManager::textMessageReceived, this, &ClientChatWidget::textMessageReceived); // Соединение сигнала "textMessageReceived" клиента с методом textMessageReceived
    connect(_client, &ClientManager::isTyping, this, &ClientChatWidget::onTyping); // Соединение сигнала "isTyping" клиента с методом onTyping
    connect(_client, &ClientManager::nameChanged, this, &ClientChatWidget::onClientNameChanged); // Соединение сигнала "nameChanged" клиента с методом onClientNameChanged
    connect(_client, &ClientManager::statusChanged, this, &ClientChatWidget::statusChanged); // Соединение сигнала "statusChanged" клиента с методом statusChanged
    connect(_client, &ClientManager::initReceivingFile, this, &ClientChatWidget::onInitReceivingFile); // Соединение сигнала "initReceivingFile" клиента с методом onInitReceivingFile
    connect(_client, &ClientManager::fileSaved, this, &ClientChatWidget::onFileSaved); // Соединение сигнала "fileSaved" клиента с методом onFileSaved
    connect(ui->lnMessage, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping); // Соединение сигнала "textChanged" текстового поля с методом sendIsTyping клиента

    dir.mkdir(_client->name()); // Создание директории с именем клиента
    dir.setPath("./" + _client->name()); // Установка пути директории
    loadMessageHistory(_client->name()); // Загрузка истоии клиента
}

void ClientChatWidget::disconnect()
{
    _client->disconnectFromHost(); // Отключение клиента от хоста
}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}

void ClientChatWidget::clearMessageHistory()
{
    ui->lstMessages->clear(); // Очистка списка сообщений
}

void ClientChatWidget::clientDisconnected()
{
    ui->wdgSendMessage->setEnabled(false); // Отключение виджета отправки сообщения
}

void ClientChatWidget::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed(); // Получение текста сообщения
    _client->sendMessage(message); // Отправка сообщения
    ui->lnMessage->setText(""); // Очистка текстового поля
    ui->lstMessages->addItem(message); // Добавление сообщения в список сообщений
}

// Метод для загрузки истории сообщений
void ClientChatWidget::loadMessageHistory(const QString &clientName) {

    QSqlDatabase db = QSqlDatabase::database();

    // Объект для выполнения SQL-запросов
    QSqlQuery query;

    // Запрос выбирает отправителя, сообщение и время для сообщений, где отправитель или получатель равен заданному имени пользователя
    query.prepare("SELECT sender, message, timestamp FROM messages WHERE sender = ? OR receiver = ? ORDER BY timestamp");

    // Привязка значение clientName к первому параметру запроса
    query.addBindValue(clientName);

    // Привязка значение clientName ко второму параметру запроса (для receiver)
    query.addBindValue(clientName);

    if (query.exec()) {
        // Если запрос выполнен успешно
        while (query.next()) {
            // Получение значения поля "sender" как строку
            QString sender = query.value(0).toString();

            // ППолучение значения поля "message" как строку
            QString message = query.value(1).toString();

            // Получение значения поля "timestamp" как строку
            QString timestamp = query.value(2).toString();

            // Добавление сообщение в lstMessages
            ui->lstMessages->addItem(QString("[%1] %2: %3").arg(timestamp, sender, message));
        }
    } else {
        // Если запрос не удалось выполнить
        qDebug() << "Ошибка: невозможно выбрать сообщения" << query.lastError().text();
    }
}

void ClientChatWidget::textMessageReceived(QString message, QString receiver)
{
    if (receiver == "Server" || receiver == "All") { // Если сообщение для сервера или всех
        ui->lstMessages->addItem(message); // Добавление сообщения в список сообщений
    }
    if(receiver != "Server"){ // Если сообщение не для сервера
        emit textForOtherClients(message, receiver, _client->name()); // Отправка сигнала с текстом для других клиентов
    }
}

void ClientChatWidget::onTyping()
{
    emit isTyping(QString("%1 печатает. . .").arg(_client->name())); // Отправка сигнала о наборе текста
}

void ClientChatWidget::onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize)
{
    auto message = QString("Клиент (%1) хочет отправить файл. Вы хотите его принять?\nИмя файла:%2\nРазмер файла: %3 байта")
                       .arg(clientName, fileName)
                       .arg(fileSize); // Формирование сообщения о предложении получения файла
    auto result = QMessageBox::question(this, "Получение файла", message); // Показ диалога с вопросом о приеме файла
    if (result == QMessageBox::Yes) { // Если пользователь согласен
        _client->sendAcceptFile(); // Отправка запроса на прием файла
    } else {
        _client->sendRejectFile(); // Отправка запроса на отклонение файла
    }
}

void ClientChatWidget::onFileSaved(QString path)
{
    auto message = QString("Файл сохранен здесь:\n%1").arg(path); // Формирование сообщения о сохранении файла
    QMessageBox::information(this, "Файл сохранен.", message); // Показ диалога с информацией о сохранении файла
}

void ClientChatWidget::on_lblOpenFolder_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(_client->name())); // Открытие директории клиента
}

void ClientChatWidget::onClientNameChanged(QString prevName, QString name)
{
    // Очистка текущего окна истории сообщений
    clearMessageHistory();

    // Загруска истории сообщений для нового клиента
    loadMessageHistory(name);

    QFile::rename(dir.canonicalPath(), name); // Переименование директории клиента

    emit clientNameChanged(prevName, name); // Отправка сигнала об изменении имени клиента
}

