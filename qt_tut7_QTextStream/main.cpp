#include <QCoreApplication>
#include <QTextStream>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString name;
    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    QTextStream qin(stdin);
    QTextStream qout(stdout); // if we do not want to write to the actual terminal output and do not REALLY log something,
                              // we might use it with qout set to 'stderr' to log whilst developing ? not so sure right now.

    //--- endl
    qout << "Please enter your name: " << Qt::endl;         //whilst this would put a newline and then flush, its also possible to
    qout << "...or better enter it here: " << Qt::flush;    //just flush
    qout << "Mad Max" << Qt::endl;                         //which will show the line will be kept

    //--- readLine/readChar
                                                            // so now we really do some

    qout << "So your actual name is ?: " << Qt::flush;

    // If the stream "thinks" it's at the end, reset the status
    qin.resetStatus();

    name = qin.readLine().trimmed();

    qout << "hi, " << name;

    qout.flush();
    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
