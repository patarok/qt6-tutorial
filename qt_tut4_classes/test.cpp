#include "test.h"
#include <QObject>
#include <QDebug>

Test::Test(QObject *parent) : QObject(parent) {
    qInfo() << "when this: " << this << "was constructed, \"" << parent << "\" got set as its parent.";
}

Test::~Test()
{
    foreach(QObject* child, children())
    {
        qInfo() << child << "was set as a (QObject-)child of object = " << this;
    }
    qInfo() << "When" << this->objectName() << "was deconstructed, it deconstructed the Parent: " << parent()->objectName() << " which was: " << parent();
}

Test* Test::getTest(QObject *parent){ return new Test; }

Test* Test::getTest(){ return new Test; } // bad idea jeans ! >>
