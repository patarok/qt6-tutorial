#include "test.h"
#include <QDebug>

Test::Test(QObject *parent)
    : QObject{parent}
{
    qInfo() << this << "Constructed" << parent;
}
Test::~Test()
{
    qInfo() << this << "Deconstructed" << this->parent();
}
void Test::message(QString foo){
    qInfo() << foo;
}

Test* Test::getTest(QObject *parent){ return new Test; }
