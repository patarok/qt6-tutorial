#include <QCoreApplication>
#include <QThread>

#include "manager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //being able to spawn loads of threads with the intention of making the app faster
    //may be tempting, but theres a limit to my love(memory) the machine will say sooner or later
    //either with a Penguin Kernel Panic, a wise Gnu hovering, or a blues screen appearing

    //for that reason we want to use Thread-Pooling
    //it is a comfortable way of managing Threads since the Qt's ThreadPool
    //kinda automagically limits your threads to the cores or 2xcores(dual-thread cores) of your machine

    QThread::currentThread()->setObjectName("THE Main Thread in main()");
    Manager manager;
    manager.start();

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
