#include "ChatItemWidget.h"
#include "ui_ChatItemWidget.h"

#include <QTime>

ChatItemWidget::ChatItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatItemWidget)
{
    ui->setupUi(this);
}

ChatItemWidget::~ChatItemWidget()
{
    delete ui;
}

// Метод для отображения сообщения
void ChatItemWidget::setMessage(QString message, bool isMyMessage)
{
    if(isMyMessage)
        // Выравнивание текста сообщения по правому краю, если сообщение принадлежит пользователю
        ui->lblMessage->setAlignment(Qt::AlignRight);

    // Установка текста сообщения
    ui->lblMessage->setText(message);

    // Установка текущго времени
    ui->lblTime->setText(QTime::currentTime().toString("HH:mm"));
}
