#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    seupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Слот для обработки события подключения нового клиента
void MainWindow::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt(); // Получение ID нового клиента
    ui->lstClients->addItem(QString("New Client added: %1").arg(id)); // Добавление записи о новом клиенте в список клиентов
    auto chatWidget= new ClientChatWidget(client, ui->tbClientsChat); // Создание виджета чата нового клиента
    ui->tbClientsChat->addTab(chatWidget, QString("Client (%1)").arg(id)); // Добавление вкладки для нового виджета чата

    connect(chatWidget, &ClientChatWidget::clientNameChanged, this, &MainWindow::setClientName); // Подключение сигнала об изменении имени клиента к слоту
    connect(chatWidget, &ClientChatWidget::statusChanged, this, &MainWindow::setClientStatus); // Подключение сигнала об изменении статуса клиента к слоту
    connect(chatWidget, &ClientChatWidget::isTyping, [this](QString name){
        this->statusBar()->showMessage(name, 750); // Показ сообщения в статус-баре, когда клиент набирает текст
    });

    connect(chatWidget, &ClientChatWidget::textForOtherClients, _server, &ServerManager::onTextForOtherClients); // Подключение сигнала о сообщении для других клиентов к слоту на сервере
}

// Слот для обработки события отключения клиента
void MainWindow::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt(); // Получение ID отключившегося клиента
    ui->lstClients->addItem(QString("Client disconnected: %1").arg(id)); // Добавление записи об отключении клиента в список клиентов
}


// Слот для обработки изменения имени клиента
void MainWindow::setClientName(QString prevName, QString name)
{
    auto widget = qobject_cast<QWidget *>(sender()); // Получение указателя на виджет-источник сигнала
    auto index = ui->tbClientsChat->indexOf(widget); // Получение индекса вкладки этого виджета
    ui->tbClientsChat->setTabText(index, name); // Установка нового имени клиента на вкладке
    _server->notifyOtherClients(prevName, name); // Уведомление других клиентов об изменении имени
}

// Слот для обработки изменения статуса клиента
void MainWindow::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget *>(sender()); // Получение указателя на виджет-источник сигнала
    auto index = ui->tbClientsChat->indexOf(widget); // Получение индекса вкладки этого виджета
    QString iconName = ":/icons/"; // Базовый путь к иконкам

    // Проверка статуса и установка соответствующей иконки
    switch (status) {
    case ChatProtocol::Available:
        iconName.append("available.png");
        break;
    case ChatProtocol::Away:
        iconName.append("away.png");
        break;
    case ChatProtocol::Busy:
        iconName.append("busy.png");
        break;
    default:
        iconName = "";
        break;
    }

    auto icon = QIcon(iconName); // Создание объекта иконки
    ui->tbClientsChat->setTabIcon(index, icon); // Установка иконки на вкладку
}

// Метод для настройки сервера
    void MainWindow::seupServer()
{
    _server = new ServerManager(); // Создание объекта сервера
    connect(_server, &ServerManager::newClientConnected, this, &MainWindow::newClientConnected); // Подключение сигнала о новом клиенте к слоту
    connect(_server, &ServerManager::clientDisconnected, this, &MainWindow::clientDisconnected); // Подключение сигнала об отключении клиента к слоту
}

// Слот для обработки запроса на закрытие вкладки чата клиента
void MainWindow::on_tbClientsChat_tabCloseRequested(int index)
{
    auto chatWidget = qobject_cast<ClientChatWidget *>(ui->tbClientsChat->widget(index)); // Получение указателя на виджет закрываемой вкладки
    chatWidget->disconnect(); // Отключение клиента
    ui->tbClientsChat->removeTab(index); // Удаление вкладки
}

