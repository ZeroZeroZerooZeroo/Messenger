#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ChatProtocol.h"
#include "ServerManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newClientConnected(QTcpSocket *client);
    void clientDisconnected(QTcpSocket *client);
    void setClientName(QString name);
    void setClientStatus(ChatProtocol::Status status);
private:
    Ui::MainWindow *ui;
    ServerManager *_server;

private://методы
    void setupServer();
};
#endif // MAINWINDOW_H
