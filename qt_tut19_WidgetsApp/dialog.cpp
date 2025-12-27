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

    // Validators
    ui->lineEdit_multiplier->setValidator(new QIntValidator(0, 999, this));
    ui->lineEdit_multiplier->setReadOnly(true);
    ui->lineEdit_value->setValidator(new QIntValidator(0, 999, this));
    ui->lineEdit_result->setValidator(new QIntValidator(0, 999, this));

    // Initial value
    ui->lineEdit_value->setPlaceholderText("0");
    ui->lineEdit_value->setText(QString::number(1));

    // Fix the width of all numeric line edits according to font metrics
    const QList<QLineEdit*> edits = {
        ui->lineEdit_value,
        ui->lineEdit_multiplier,
        ui->lineEdit_result
    };

    for (QLineEdit* le : edits) {
        QFontMetrics fm(le->font());
        int numDigits = 6;  // max digits to allow

        int digitWidth = fm.horizontalAdvance(QLatin1Char('9')) * numDigits;

        // frame / margins
        int frame = le->contentsMargins().left() + le->contentsMargins().right();

        // approximate clear button width: use PM_SmallIconSize or PM_ButtonIconSize
        int clearButtonWidth = le->style()->pixelMetric(QStyle::PM_SmallIconSize, nullptr, le);

        int totalWidth = digitWidth + frame + clearButtonWidth + 4;

        le->setMinimumWidth(totalWidth);
        le->setMaximumWidth(totalWidth);
    }




    ui->lineEdit_value->setClearButtonEnabled(true);
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::readInt(QLineEdit *edit, int &out) const
{
    const QString s = edit->text().trimmed();
    if (s.isEmpty()) return false;

    bool ok = false;
    const int v = s.toInt(&ok);
    if (!ok) return false;

    out = v;
    return true;
}

void Dialog::on_pushButton_clicked()
{
    int value = 0;
    int mult  = 0;

    if (!readInt(ui->lineEdit_value, value)) {
        ui->lineEdit_result->clear();
        return;
    }

    if (!readInt(ui->lineEdit_multiplier, mult)) {
        ui->lineEdit_result->clear();
        return;
    }

    const int result = value * mult;
    ui->lineEdit_result->setText(QString::number(result));
}

void Dialog::on_lineEdit_value_textChanged(const QString &)
{
    on_pushButton_clicked();
}

void Dialog::on_comboBox_currentIndexChanged(int)
{
    const QString key = ui->comboBox->currentText();
    if (!m_types.contains(key)) {
        ui->lineEdit_multiplier->clear();
        ui->lineEdit_result->clear();
        return;
    }

    const int m = m_types.value(key);
    ui->lineEdit_multiplier->setText(QString::number(m));
    on_pushButton_clicked();
}
