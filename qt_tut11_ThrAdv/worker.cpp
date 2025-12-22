#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{
    m_producer = false;
    m_count = 0;
}

Worker::~Worker()
{
    qInfo() << "destroying -> this:" << this << "and: " << this->parent();
}

bool Worker::producer() const
{
    return m_producer;
}

void Worker::setProducer(bool newProducer)
{
    m_producer = newProducer;
}

void Worker::consume(int value)
{
    qInfo() << this << "Consuming: " << value << QThread::currentThread();
}

void Worker::start()
{
    // init for our privates can go here too, but in this case doesn't really matter
    // but what is important is that we may want to set Qt-"parent-child relationships"
    // in the 'start()' if we are messing with threading
    qInfo() << this << "Starting" << QThread::currentThread();
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &Worker::timeout); // every time this timer fires we call our 'timeout()'

    if(m_producer)
    {
        qInfo() << this << "Starting timer" << QThread::currentThread();
        m_timer->setInterval(1000); // milliseconds as almost always for time-related functions like sleep and interval
        m_timer->start();
    }
}

void Worker::quit()
{
    qInfo() << this << "is quitting:" << QThread::currentThread();
    m_timer->stop();
    emit finished();
}

void Worker::timeout()
{
    int value = QRandomGenerator::global()->bounded(1000);
    qInfo() << this << "Producing:" << value << QThread::currentThread();
    emit produced(value);
    m_count++;
    if(m_count == 5)
        quit();
}
