#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{

    qInfo() << this << Q_FUNC_INFO << QThread::currentThread();
}

Worker::~Worker()
{
    qInfo() << this << Q_FUNC_INFO << QThread::currentThread();
}

void Worker::run()
{
    qInfo() << this << Q_FUNC_INFO << QThread::currentThread();

    qInfo() << this << "Starting the loop" << QThread::currentThread();

    QScopedPointer<QEventLoop> loop(new QEventLoop);
    QScopedPointer<QTimer> timer(new QTimer);

    timer->setInterval(2000);


    // since Worker is in effect instantiated on the main thread...
    // and we are referring to 'work()' of worker ... Qt::AutoConnection
    // QThreadPool redirected work would happen in the main-thread
    // to rest assure everything is executed on the managed thread
    // ( 'Thread(pooled)' ), we are explicit on which connectionType we
    // want to use connect with

    //we are connecting:
    //timeout() signal from that QTimer that 'timer.data()' points to,
    //to 'this's(Worker) 'work()' method.
    //connect(timer.data(), &QTimer::timeout, this, &Worker::work);
    connect(timer.data(), &QTimer::timeout, this, &Worker::work, Qt::DirectConnection);

    //since loop would be there forever if we dont give it some signal
    //on which it should quit, we assign the 'finished' signal of 'this'
    //object to trigger the quit() slot method of 'loop.data()'
    //which is a QScopedPointer to a QEventLoop
    //connect(this, &Worker::finished, loop.data(), &QEventLoop::quit);
    connect(this, &Worker::finished, loop.data(), &QEventLoop::quit, Qt::DirectConnection);


    timer->start();
    loop->exec();  //Blocking the thread it is running on and executes just the event loop

    qInfo() << this << "Finished" << QThread::currentThread();
}

void Worker::work()
{
    qInfo() << this << Q_FUNC_INFO << QThread::currentThread();

    // TO DO - do something cool here

    emit finished();
}
