#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    // lets assume some heavy lifting going on here,
    // so we have to take care about threading.
    qInfo() << QThread::currentThread();
    QThread::currentThread()->msleep(60000);

}

