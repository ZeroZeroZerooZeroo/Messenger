#include "ChatItemWidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupClient();

}

MainWindow::~MainWindow()
{
    delete ui;
}


// Метод настройки клиента
void MainWindow::setupClient()
{
    // Создание нового объекта ClientManager
    _client = new ClientManager();
    // Подключение слота к сигналу подключения клиента
    connect(_client , &ClientManager::connected, [this](){
        // Включение центрального виджета окна
        ui->centralwidget->setEnabled(true);
    });
    // Подключение слота к сигналу отключения клиента
    connect(_client, &ClientManager::disconnected, [this](){
        // Выключение центрального виджета окна
        ui->centralwidget->setEnabled(false);
    });
    // Подключение слота для обработки получения текстового сообщения
    connect(_client, &ClientManager::textMessageReceived, this, &MainWindow::dataReceived);
    // Подключение слота для обработки события "typing"
    connect(_client, &ClientManager::isTyping, this, &MainWindow::onTyping);
    // Подключение слота для обработки начала получения файла
    connect(_client, &ClientManager::initReceivingFile, this, &MainWindow::onInitReceivingFile);
    // Подключение слота для обработки отклоненного файла
    connect(_client, &ClientManager::rejectReceivingFile, this, &MainWindow::onRejectReceivingFile);
    // Подключение сигнала изменения текста поля ввода сообщения к слоту отправки "typing"
    connect(ui->lnMessage, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);
    // Подключение слота для обработки подтверждения соединения
    connect(_client, &ClientManager::connectionACK, this, &MainWindow::onConnectionACK);
    // Подключение слота для обработки подключения нового клиента
    connect(_client, &ClientManager::newClientConnectedToServer, this, &MainWindow::onNewClientConnectedToServer);
    // Подключение слота для обработки изменения имени клиента
    connect(_client, &ClientManager::clientDisconnected, this, &MainWindow::onClientDisconnected);
    // Подключение слота для обработки отключения клиента
    connect(_client, &ClientManager::clientNameChanged, this, &MainWindow::onClientNameChanged);
}

// Обработчик действия "Connect" в меню
void MainWindow::on_actionConnect_triggered()
{
    // Подключение к серверу
    _client->connectToServer();
}

// Обработчик нажатия на кнопку отправки
void MainWindow::on_btnSend_clicked()
{
    // Получение и обрезка пробелов символов из введенного сообщения
    auto message = ui->lnMessage->text().trimmed();
    // Отправка сообщения выбранному получателю
    _client->sendMessage(message, ui->cmbDestination->currentText());
    // Очистка поля для ввода сообщения
    ui->lnMessage->setText("");
    // Установка фокуса на поле ввода сообщения
    ui->lnMessage->setFocus();

    // Создание нового виджета ChatItemWidget
    auto chatWidget = new ChatItemWidget();
    // Установка сообщения в виджет
    chatWidget->setMessage(message, true);
    // Создание нового элемента списка
    auto listWidgetItem = new QListWidgetItem();
    // Установка размера элемента списка
    listWidgetItem->setSizeHint(QSize(0, 65));
    // Добавление элемента списка в виджет
    ui->lstMessages->addItem(listWidgetItem);
    // Установка пользовательского виджета в элемент списка
    ui->lstMessages->setItemWidget(listWidgetItem, chatWidget);
}

// Обработчик получения данных
void MainWindow::dataReceived(QString message)
{
    // Создание нового виджета ChatItemWidget
    auto chatWidget = new ChatItemWidget();
    // Установка полученного сообщения в виджет
    chatWidget->setMessage(message);
    // Создание нового элемента списка
    auto listWidgetItem = new QListWidgetItem();
    // Установка размера элемента списка
    listWidgetItem->setSizeHint(QSize(0, 65));
    // Добавление элемента списка в виджет
    ui->lstMessages->addItem(listWidgetItem);
    // Установка фона элемента списка
    listWidgetItem->setBackground(QColor(167, 255, 237));
    // Установка пользовательского виджета в элемент списка
    ui->lstMessages->setItemWidget(listWidgetItem, chatWidget);
}

// Обработчик завершения редактирования имени клиента
void MainWindow::on_lnClientName_editingFinished()
{
    // Получение и обрезка пробелов символов из введенного имени
    auto name = ui->lnClientName->text().trimmed();
    // Отправка имени на сервер
    _client->sendName(name);
}

// Обработчик изменения статуса
void MainWindow::on_cmbStatus_currentIndexChanged(int index)
{
    // Приведение индекса к типу статуса
    auto status = (ChatProtocol::Status)index;
    // Отправка статуса на сервер
    _client->sendStatus(status);
}

// Обработчик события "typing"
void MainWindow::onTyping()
{
    // Отображение сообщения в statusBar
    statusBar()->showMessage("Server is typing...", 750);
}

// Обработчик нажатия на кнопку отправки файла
void MainWindow::on_btnSendFile_clicked()
{
    // Открытие диалога выбора файла
    auto fileName = QFileDialog::getOpenFileName(this, "Select a file", "/home");
    // Отправка запроса на отправку файла
    _client->sendInitSendingFile(fileName);
}

// Обработчик отклоненного файла
void MainWindow::onRejectReceivingFile()
{
    // Отображение сообщения об отклонении
    QMessageBox::critical(this, "Sending File", "Operation rejected...");
}

// Обработчик начала получения файла
void MainWindow::onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize)
{
    // Формирование сообщения о запросе на получение файла
    auto message = QString("Client (%1) wants to send a file. Do you want to accept it?\nFile Name:%2\nFile Size: %3 bytes")
          .arg(clientName, fileName)
          .arg(fileSize);
    // Открытие диалога подтверждения получения файла
    auto result = QMessageBox::question(this, "Receiving File", message);
    // Если пользователь согласен
    if (result == QMessageBox::Yes) {
        // Отправка подтверждения
        _client->sendAcceptFile();
    }
    else {
        // Отправка отклонения
        _client->sendRejectFile();
    }
}

// Обработчик подтверждения подключения
void MainWindow::onConnectionACK(QString myName, QStringList clientsName)
{
    // Очистка списка получателей
    ui->cmbDestination->clear();
    // Добавление предопределенных получателей в начало списка
    clientsName.prepend("All");
    clientsName.prepend("Server");
    // Добавление имен всех клиентов в список получателей
    foreach (auto client, clientsName) {
        ui->cmbDestination->addItem(client);
    }
    // Установка заголовка окна с именем текущего клиента
    setWindowTitle(myName);
}

// Обработчик добавления нового клиента
void MainWindow::onNewClientConnectedToServer(QString clienName)
{
    // Добавление имени нового клиента в список получателей
    ui->cmbDestination->addItem(clienName);
}

// Обработчик изменения имени клиента
void MainWindow::onClientNameChanged(QString prevName, QString clientName)
{
    // Поиск и замена имени клиента в списке получателей
    for (int i = 0; i < ui->cmbDestination->count(); ++i) {
        if (ui->cmbDestination->itemText(i) == prevName) {
            ui->cmbDestination->setItemText(i, clientName);
            return;
        }
    }
}

// Обработчик отключения клиента
void MainWindow::onClientDisconnected(QString clientName)
{
    // Поиск и удаление имени клиента из списка получателей
    for (int i = 0; i < ui->cmbDestination->count(); ++i) {
        if (ui->cmbDestination->itemText(i) == clientName) {
            ui->cmbDestination->removeItem(i);
            return;
        }
    }
}

