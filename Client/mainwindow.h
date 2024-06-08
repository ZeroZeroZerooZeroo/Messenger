#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientManager.h"

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
    // Обработчик нажатия на "Connect" в меню
    void on_actionConnect_triggered();

    void on_btnSend_clicked();

    // Обработчик полученных данных
    void dataReceived(QString message);

    // Обработчик завершения редактирования имени клиента
    void on_lnClientName_editingFinished();

    // Обработчик изменения статуса
    void on_cmbStatus_currentIndexChanged(int index);

    // СОбработчик события "typing"
    void onTyping();

    // Обработчик нажатия на кнопку отправки файла
    void on_btnSendFile_clicked();

    // Обработчик отклоненного файла
    void onRejectReceivingFile();

    // Обработчик начала получения файла
    void onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize);

    // Обработчик оповещения о подтверждении подключения
    void onConnectionACK(QString myName, QStringList clientsName);

    // Обработчик добавления нового клиента
    void onNewClientConnectedToServer(QString clienName);

    // Обработчик изменения имени клиента
    void onClientNameChanged(QString prevName, QString clientName);

    // Обработчик оповещения о отключении клиента
    void onClientDisconnected(QString clientName);

private:
    Ui::MainWindow *ui;
    ClientManager *_client;
    void setupClient();
};
#endif
