#include "test.h"


Test::Test(QObject *parent) : QObject{parent}
{}

void Test::doStuff()
{
    qInfo() << "Doing stuff";
    emit close();
}
