#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QTimer>
#include <QtConcurrent>
#include "worker.h"


void testMain(){

    qInfo() << "Testing on main";

    Worker* worker = new Worker();
    worker->run();
    worker->deleteLater();

    qInfo() << "Testing...";
}

void testThread(){
    QThread* thread = new QThread();    // Do not try to customize QThread !
                                        // That wont work out. And even with loads of precaution
                                        // and steps taken to respect the nature of QThread,
                                        // this might blow the whole app up later on.
    thread->setObjectName("Worker Thread");
    qInfo() << "Testing on Worker Thread";
    Worker* worker = new Worker();

    worker->moveToThread(thread);

    QObject::connect(thread, &QThread::started, worker, &Worker::run);
    QObject::connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();

    qInfo() << "Testing...";
}

void testPool(){
    qInfo() << "Testing on Thread Pool";

    Worker* worker = new Worker();
    worker->setAutoDelete(true);

    QThreadPool::globalInstance()->start(worker);

    qInfo() << "Testing ...";

}

void testConcurrent(){
    qInfo() << "Testing on Concurrent";
    QScopedPointer<Worker> worker(new Worker());

    worker->run();
    qInfo() << "Testing...";
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

    QThread::currentThread()->setObjectName("Main Thread");

    //testMain();
    //testThread();
    //testPool();
    QFuture<void> foo = QtConcurrent::run(&testConcurrent);
    QFuture<void> bar = foo.then([](){
        qInfo() << "Finished in" <<  QThread::currentThread();
    });
    qInfo() << "but now?";

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
