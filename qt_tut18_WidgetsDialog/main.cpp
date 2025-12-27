#include "dialog.h"
#include <QApplication>
#include <QThread>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QThread::currentThread()->setObjectName("Main Thread");

    Dialog w;
    w.show();
    return a.exec();
}
