#include <QCoreApplication>
#include "test.h"

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

    Test test;

    // Connect 'test' and Tests "close()-signal" to QCoreApplication typed and instantiated 'a' to a's "quit" ...
    // in 99% of all cases this works just fine, since the default is auto-connection ..and when we are not in auto-mode,
    // we need Qt::QueuedConnection
    QObject::connect(&test, &Test::close, &a, &QCoreApplication::quit, Qt::QueuedConnection);
    // this is because:
    // Qt chooses a connection type automatically:
    // Qt::AutoConnection (default)
    // If sender and receiver are in the same thread, it behaves as direct call (DirectConnection)
    // If they are in different threads, it behaves as queued call (QueuedConnection)


    test.doStuff();

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    int value = a.exec();

    qInfo() << "Exit value:" << value;
}
