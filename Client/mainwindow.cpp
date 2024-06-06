#include "mainwindow.h"
#include "ChatItemWidget.h"
#include "ui_mainwindow.h"
#include "ClientManager.h"
#include <QFileDialog>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->centralwidget->setEnabled(false);
     _client = new ClientManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{

    connect(_client , &ClientManager::connected, [this](){
        ui->centralwidget->setEnabled(true);
        ui->btnSend->setEnabled(false);
        ui->actionConnect->setEnabled(false);

    });
    connect(_client, &ClientManager::disconnected, [this](){
        ui->centralwidget->setEnabled(false);
        ui->actionConnect->setEnabled(true);
    });
    connect(_client, &ClientManager::textMessageReceived, this, &MainWindow::dataReceived);
    connect(_client, &ClientManager::isTyping, this, &MainWindow::onTyping);

    connect(_client, &ClientManager::initReceivingFile, this, &MainWindow::onInitReceivingFile);
    connect(_client, &ClientManager::rejectReceivingFile, this, &MainWindow::onRejectReceivingFile);

    _client->connectToServer();
}

void MainWindow::dataReceived(QString message)
{
//    ui->lstMessage->addItem(data);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessage->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(167,255,237));
    ui->lstMessage->setItemWidget(listItemWidget,chatWidget);
}


void MainWindow::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage(message);
    ui->lnMessage->setText("");
//    ui->lstMessage->addItem(message);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessage->addItem(listItemWidget);
    ui->lstMessage->setItemWidget(listItemWidget,chatWidget);
}


void MainWindow::on_lnClientName_editingFinished()
{
    auto name = ui->lnClientName->text().trimmed();
    _client->sendName(name);
}


void MainWindow::on_cmbStatus_currentIndexChanged(int index)
{
    auto status = (ChatProtocol::Status)index;
    _client->sendStatus(status);
}

void MainWindow::onTyping()
{
    statusBar()->showMessage("Сервер печатает. . .",750);
}


void MainWindow::on_btnSendFile_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,"Select a file","/home");
    _client->sendInitSendingFile(fileName);
}

void MainWindow::onRejectReceivingFile()
{
    QMessageBox::critical(this,"Sending File","Operation rejected. . .");
}

void MainWindow::onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize)
{
    auto message = QString("Client (%1) wants to send a file. Do you want to accept it?\nFile Name:%2\nFile Size: %3 bytes").arg(clientName,fileName).arg(fileSize);
    auto result = QMessageBox::question(this,"Receiving File",message);
    if (result == QMessageBox::Yes)
    {
        _client->sendAcceptFile();
    }
    else
    {
        _client->sendRejectFile();
    }
}


void MainWindow::on_lnMessage_textChanged(const QString &arg1)
{
    ui->btnSend->setEnabled(arg1.trimmed().length()>0);

    _client->sendIsTyping();
}

