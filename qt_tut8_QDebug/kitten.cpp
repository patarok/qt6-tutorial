#include "kitten.h"
#include <QObject>
#include <QDebug>

Kitten::Kitten(QObject *parent)
{

}

void Kitten::meow()
{
    //qInfo() << "meow" << Qt::endl;
    qWarning() << "Meow! I am hungry!!!!";
}
