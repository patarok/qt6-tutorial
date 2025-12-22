#include <QCoreApplication>
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>
#include <QThreadPool>
#include <QFuture>
#include <QtConcurrent>
#include <QRunnable>
#include <QMutexLocker>
#include <QMutex>
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

    int count = 0;  // <- shared resource
    int max = 5;    // number of threads --1 at the beginning of our tutorial in the end say 3 or better 5

    QMutex mutex; // ONLY ONE for all the workers > see down here ⌄
                  // in the for loop we are actually setting up *!*

    for(int i = 0; i < max; ++i) // *!* FIVE times / 'max' times a **!**
    {
        Worker *worker = new Worker();  // **!** Worker instance on the heap...
        worker->setCount(&count);       // then we hand over the shared resource which is 'count' as a reference
                                        // EACH AND EVERY WORKER HAS THE SAME REFERENCE
        worker->setMutex(&mutex);       // then we hand over THAT ONE mutex!! 'mutex' (as a reference again)
        worker->setAutoDelete(true);    // each worker is set to use its AutoDelete

        QThreadPool::globalInstance()->start(worker); // according to the loop iteration all the 'max'(5) workers are
                                                      // subsequently started by the 'global Instance' of QThreadPool
                                                      // which will manage which thread gets to be managed
                                                      // into a CPU-thread at a certain time...
    }

    QThreadPool::globalInstance()->waitForDone();
    qInfo() << "Count: " << count;

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
