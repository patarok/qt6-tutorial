#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    m_types.insert("Fish", 2);
    m_types.insert("Cat", 5);
    m_types.insert("Dog", 6);
    m_types.insert("Mouse", 12);

    ui->setupUi(this);

    ui->comboBox->addItems(m_types.keys());
    ui->comboBox->setCurrentIndex(0);

    ui->lineEdit_multiplier->setValidator(new QIntValidator(0, 999, this));
    ui->lineEdit_multiplier->setReadOnly(true);
    ui->lineEdit_value->setValidator(new QIntValidator(0, 999, this));
    ui->lineEdit_result->setValidator(new QIntValidator(0, 999, this));

    ui->lineEdit_value->setText(QString::number(1));

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    int result = ui->lineEdit_value->text().toInt() * ui->lineEdit_multiplier->text().toInt();
    ui->lineEdit_result->setText(QString::number(result));
}


void Dialog::on_lineEdit_value_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok);

    if (ok) {
        // Use the integer value
        // The validator ensures this will be in range [0, 999]
        on_pushButton_clicked();
    } else {
        // Empty string or invalid (shouldn't happen with validator)
    }
}




void Dialog::on_comboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    int m = m_types.value(ui->comboBox->currentText());
    ui->lineEdit_multiplier->setText(QString::number(m));
    on_pushButton_clicked();
}

