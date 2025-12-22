#include <QMutexLocker>
#include "worker.h"


Worker::Worker(QObject *parent)
    : QObject{parent}
{}

void Worker::setCount(int *newCount)
{
    m_count = newCount;
}

void Worker::setMutex(QMutex *newMutex)
{
    m_mutex = newMutex;
}


void Worker::run()
{
    //Threadpool runs in this code
    for (int i = 0; i < 10; ++i)
    {
        //m_mutex->lock();  // no way other threads could access it
                            // so we would take close care when which process would r/w
        //Convinience Class to the rescue:
        QMutexLocker locker(m_mutex); // locks here

        int value = *m_count;
        value++;
        *m_count = value; // Danger !! modifying at memory location ... now :
                          // we need to prevent other threads of doing so at the same time as we(this algo) does.
        qInfo() << QThread::currentThread() << *m_count;
        //unlocks when we go out of scope
        //m_mutex->unlock(); // <-- this would be here if we'd lock with m_mutex->lock(); ;*()
    }
    qInfo() << QThread::currentThread() << "Done";

}

