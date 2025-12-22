#include <QCoreApplication>
#include <QThread>
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

    QThread producerThread;
    QThread consumerThread;

    Worker producer;
    Worker consumer;

    producer.moveToThread(&producerThread);
    consumer.moveToThread(&consumerThread);

    producer.setProducer(true);

    producerThread.setObjectName("Producer Thread QThread typed Object.");
    consumerThread.setObjectName("Consumer Thread QThread typed Object.");

    producer.setObjectName("actual Producer worker");
    consumer.setObjectName("actual Consumer worker");

    QObject::connect(&producerThread, &QThread::started, &producer, &Worker::start);
    QObject::connect(&consumerThread, &QThread::started, &consumer, &Worker::start);

        QObject::connect(&producer, &Worker::produced, &consumer, &Worker::consume); // actually connect has 5 params of which the fifth is defaulting to
        QObject::connect(&producer, &Worker::finished, &consumer, &Worker::quit);    // autoconnect (Qt::AutoConnection)

        consumerThread.start();
        producerThread.start();
    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
