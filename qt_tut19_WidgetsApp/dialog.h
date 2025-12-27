#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_value_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    QMap<QString, int> m_types;
    bool readInt(QLineEdit *edit, int &out) const;
    //void reserveClearButtonSpace(QLineEdit *le);
};

#endif // DIALOG_H
