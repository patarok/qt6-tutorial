#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

void basics()
{
    QFile file("test.txt"); // if we omit a path its gonna be in the current dir
                            // it should be a logical assumption for any reasonable programmer, that
                            // pathing cant be done by issuing 'magic literals' into this method.
                            // normally we would use stuff from the former lesson, where we learned to get:
                            // -system we are running on, which may make a difference in how we have to separate dir hierarchy
                            // -system root path
                            // -current dir
                            // and according to what you wanna do or what makes sense for your application to store WHERE
                            // we concetenate from the dynamically collected information...


    if(!file.open(QIODevice::ReadWrite)) // this is opening the file in read-and-write mode, but we can opt for other ways too like: Append etc.
    {
        qCritical() << "Could not open file!";
        qCritical() << file.errorString();
        return;
    }

    qInfo() << "Writing file...";
    file.write(QByteArray("Hello World"));
    file.flush(); // pushes the data to the disk

    qInfo() << "Reading file...";
    file.seek(0);
    qInfo() << file.readAll();

    file.close(); // this also does a file-flush

    // we could at any time earlier in the application make changes like appending stuff for
    // kinda a log-stream file, by issuing: file.flush(); // this essentially pushes all the changes made to the opened file to the disk
}

bool writeFile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() << file.errorString();
        return false;
    }

    QTextStream stream(&file);
    for(int i = 0; i < 5; i++)
    {
        stream << QString::number(i) << " Hello World\r\n";
    }

    file.close();
    return true;
}

void readFile(QString filename)
{
    QFile file(filename);
    if(!file.exists())
    {
        qCritical() << "File not found";
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << file.errorString();
        return;
    }

    QTextStream stream(&file);
    //QString data = stream.readAll();

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        qInfo() << line;
    }

    file.close();
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

    //--- Basics
    basics();

    //--- Writing
    writeFile("test.txt");

    //--- Reading
    readFile("testssdsad.txt");

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}


