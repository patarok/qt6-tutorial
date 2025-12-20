#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "test.h"
#include <QScopedPointer>


typedef QList<Test*> testList; // using typedef here as a convenient way to spare us writing the typed brackets and stuff over and over

testList getList()
{
    testList list;
    for(int i = 0; i < 5 ; i++)
    {
        list.append(new Test());
        list.last()->setObjectName("Test_" + QString::number(i));
    }

    return list;
}

// display a list of pointers

void display(testList list)
{
    foreach(Test* item, list)
    {
        qInfo() << item;
    }
}

void testScope()
{
    QScopedPointer<Test> ptr(new Test());
    ptr->message("Hello");
}

void work(QSharedPointer<Test> ptr){
    ptr->message("Working");
}


void finish(QSharedPointer<Test> ptr)
{
    ptr->message("Finished");
}

void step(QSharedPointer<Test> ptr){
    ptr->message("Stepping");
    for(int i = 0; i < 3; i++){
        work(ptr);
    }
    finish(ptr);
}

void testShared(Test* test)
{
    QSharedPointer<Test> ptr(test);
    ptr->message("Starting");
    step(ptr);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.
    testList list = getList();
    display(list);

    qInfo() << "Deleting...";
    qDeleteAll(list); // deletes all the Objects from the entire list
    // but since there still is a sh..load of dangling pointers now we want to delete them:
    list.clear();

    //testScope();
    testShared(new Test());

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
