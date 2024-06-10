#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "ServerManager.h"
#include "ClientChatWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    // Метод для записи в файл логов
    void logToFile(const QString &message);

private slots:

    // Обработчик события подключения нового клиента
    void newClientConnected(QTcpSocket *client);

    // СОбработчик события отключения клиента
    void clientDisconnected(QTcpSocket *client);

    // СОбработчик изменения имени клиента
    void setClientName(QString prevName, QString name);

    // Обработчик изменения статуса клиента
    void setClientStatus(ChatProtocol::Status status);

    // Обработчик запроса на закрытие вкладки чата клиента
    void on_tbClientsChat_tabCloseRequested(int index);

    // Обработчик запроса на отключение всех клиентов
    void on_btnDisconnectAll_clicked();

private:

    Ui::MainWindow *ui;
    ServerManager *_server;
    void seupServer();
};
#endif
