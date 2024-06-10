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
    auto clientName = QString("Клиент (%1)").arg(id);

    // Запись в файл логов
    logToFile(QString("Добавлен новый клиент: %1").arg(clientName));

    ui->lstClients->addItem(QString("Добавлен новый клиент: %1").arg(id)); // Добавление записи о новом клиенте в список клиентов

    auto chatWidget= new ClientChatWidget(client, ui->tbClientsChat); // Создание виджета чата нового клиента

    ui->tbClientsChat->addTab(chatWidget, QString("Клиент (%1)").arg(id)); // Добавление вкладки для нового виджета чата

    connect(chatWidget, &ClientChatWidget::clientNameChanged, this, &MainWindow::setClientName); // Подключение сигнала об изменении имени клиента

    connect(chatWidget, &ClientChatWidget::statusChanged, this, &MainWindow::setClientStatus); // Подключение сигнала об изменении статуса клиента
    connect(chatWidget, &ClientChatWidget::isTyping, [this](QString name){

        this->statusBar()->showMessage(name, 1000); // Показ сообщения в statusBar, когда клиент набирает текст

    });

    connect(ui->btnDisconnectAll, &QPushButton::clicked, this, &MainWindow::on_btnDisconnectAll_clicked);// Подключение сигнала об отключении всех клиентов

    connect(chatWidget, &ClientChatWidget::textForOtherClients, _server, &ServerManager::onTextForOtherClients); // Подключение сигнала о сообщении для других клиентов
}

// Слот для обработки события отключения клиента
void MainWindow::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt(); // Получение ID отключившегося клиента

    auto clientName = QString("Клиент (%1)").arg(id);

    logToFile(QString("Клиент отключен: %1").arg(clientName));

    ui->lstClients->addItem(QString("Клиент отключен: %1").arg(id)); // Добавление записи об отключении клиента
}

// Функция для записи в файл логов
void MainWindow::logToFile(const QString &message) {
    QFile file("server_log.txt");

    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " - " << message << "\n";
        file.close();
    } else {
        qDebug() << "Ошибка: невозможно открыть файл журнала для записи.";
    }
}

// Слот для обработки изменения имени клиента
void MainWindow::setClientName(QString prevName, QString name)
{
    auto widget = qobject_cast<QWidget *>(sender());

    auto index = ui->tbClientsChat->indexOf(widget);

    ui->tbClientsChat->setTabText(index, name); // Установка нового имени клиента во вкладке

    _server->notifyOtherClients(prevName, name); // Уведомление других клиентов об изменении имени
}

// Слот для обработки изменения статуса клиента
void MainWindow::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget *>(sender());

    auto index = ui->tbClientsChat->indexOf(widget);

    QString iconName = ":/icons/"; // Путь к иконкам

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

    auto icon = QIcon(iconName);

    ui->tbClientsChat->setTabIcon(index, icon); // Установка иконки
}

    void MainWindow::seupServer()
{
    _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &MainWindow::newClientConnected); // Подключение сигнала о новом клиенте к слоту
    connect(_server, &ServerManager::clientDisconnected, this, &MainWindow::clientDisconnected); // Подключение сигнала об отключении клиента
}

// Слот для обработки запроса на закрытие вкладки чата клиента
void MainWindow::on_tbClientsChat_tabCloseRequested(int index)
{
    auto chatWidget = qobject_cast<ClientChatWidget *>(ui->tbClientsChat->widget(index));

    chatWidget->disconnect(); // Отключение клиента

    ui->tbClientsChat->removeTab(index); // Удаление вкладки
}


void MainWindow::on_btnDisconnectAll_clicked()
{
    for (int i = 0; i < ui->tbClientsChat->count(); ++i) {
        auto chatWidget = qobject_cast<ClientChatWidget *>(ui->tbClientsChat->widget(i));
        if(chatWidget) {
            chatWidget->disconnect();
        }
    }
}

