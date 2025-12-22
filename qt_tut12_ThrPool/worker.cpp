#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{
        qInfo() << "Created" << this << QThread::currentThread();
}

Worker::~Worker()
{
    qInfo() << "Destructed" << this << QThread::currentThread();
}

void Worker::work()
{
    qInfo() << "WORKING" << this << QThread::currentThread();
}

void Worker::run()
{
    // Starting in the thread
    qInfo() << "Started running: " << this << QThread::currentThread();
    emit started();


    // WORK THAT REALLY HAS TO BE THREADED SHOULD GO HERE
    // or to do so should call the required methods...
    // BUT ALWAYS FROM WITHIN ---HERE--- !!-> the 'run()' method of a Worker.
    for (int i = 0; i < 3; ++i) {
        qInfo() << "Running" << this << QThread::currentThread();
        QThread::currentThread()->msleep(1000);
    }

    // Finishing in the thread
    qInfo() << "Finishing the run of: " << this << QThread::currentThread();
    emit finished();
}




