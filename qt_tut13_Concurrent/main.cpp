#include <QCoreApplication>
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>
#include <QFuture>
#include <QtConcurrent>

void test()
{
    qInfo() << "Test" << QThread::currentThread();

}

int testRandom(int max)
{
    qInfo() << "Random" << QThread::currentThread();
    QThread::currentThread()->msleep(5000);

    return QRandomGenerator::global()->bounded(max);
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

    qInfo() << "Build Test done.";  // after adding the dependency to the CMakeLists.txt file or like in this project,
                                    // or to the project's '.pro' file in a qmake project, its good to try building


    QThread::currentThread()->setObjectName("OUR main THREAD");  // in modern Versions of Qt6 this should already carry the name
                                                                 // 'Main Thread'
    qInfo() << "Starting" << QThread::currentThread();

    // TODO - thread!

  //test(); // <- obviously not threaded

  //QtConcurrent::run(test);  // first its the function name and then the params .. pay attention if you come from Qt5

    QFuture<void> f1 = QtConcurrent::run(test);
    f1.waitForFinished();

    QFuture<int> f2 = QtConcurrent::run(testRandom, 100);

    qInfo() << "Random:" << f2.result();

    qInfo() << "Finished" << QThread::currentThread();



    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
