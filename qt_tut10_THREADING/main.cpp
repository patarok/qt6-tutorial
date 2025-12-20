#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include "worker.h"

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

    QThread::currentThread()->setObjectName("Main Thread");

    qInfo() << "Starting" << QThread::currentThread();
    qInfo() << "Doing stuff now." << QThread::currentThread();

    //Worker worker;
    //worker.run(); // called here in main it puts the main thread to bed for 500ms between each for loop iteration

    //but we want:
    Worker *worker = new Worker();  // no Parent!! because parent and child protecting each others existance,
                                    // can not live in separate threads
    QThread thread;
    thread.setObjectName("Worker Thread 1 Codename Fuzzy Kitten");
    worker->moveToThread(&thread);  // can not move a child to a different dimension(thread) than its parent.
                                    // but you can indeed just move a top-hierarchy parent to a thread and it will carry its children over there.

    QObject::connect(&thread, &QThread::started, worker, &Worker::run);

    thread.start();

    qInfo() << "Doing stuff concurrently" << QThread::currentThread();
    for (int i = 0; i < 10; ++i) {
        qInfo() << "Working on step" << QString::number(i) << "in thread: " << QThread::currentThread() << "considered Thread 0 or root-thread.";
        QThread::currentThread()->msleep(500);
    }



    qInfo() << "Finished" << QThread::currentThread();

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
