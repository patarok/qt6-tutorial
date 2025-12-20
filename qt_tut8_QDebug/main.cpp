#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "kitten.h"
#include "QSysInfo"
#include <QStorageInfo>
#include <QDir>

#ifdef _WIN32
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif
// up here we have a nice trick to make clear-screen work, no matter if its Linux or Windows

// but there are other ways to evaluate which system we are on
// Qt also uses MACROs for that issue (Q_OS_OPENBSD, Q_OS_MACOS, ...)
// see below:

// at either compile-time
void compileTime()
{
#ifdef Q_OS_LINUX
    qInfo() << "Hello from Linux";
#endif
#ifdef Q_OS_WINDOWS
    qInfo() << "Hello from Linux";
#endif
}
// according to the operating system you run the IDE on, you may see the line greyed out or not
// actually I would do this above our actual code at the very beginning so we can hand over some glob to each method ???


void runTime()
{
    QSysInfo info;
    qInfo() << "Hello from: " << info.prettyProductName();
    qInfo() << "(" << info.kernelType() << ")";
}
// QSysInfo carries loads of information like architecture, pretty product name, kernel name, kernel version and more.

//even more information on where we are is available through different modules


// since we touched the issue directories with the former showcase function,
// we can now proceed on to QDir
void whichDir()
{

    qInfo() << "we're in : " << QDir::currentPath(); // this is where our application sees as its starting point,
                                                     // usually we can assume (for a CLI app) this should be the directory the application was started from.
    // and again there is more to it. If you wanna know more F1 yourself.
}

void whichRoot()
{
    QStorageInfo root = QStorageInfo::root();
    qInfo() << "we're at : " << root.rootPath(); // whats set as root path for the system we run our application on.
    // its the same here ... there is way more info you can look up in the documentation or the IDE tooltip, when you hover over the typename
    // like: fileSystemType, isReadOnly, bytesFree, etc., etc.
}

// we go full-on with dirs and files now:
// Listing
void test_list(QString path, bool recursive = false)
{

    QDir root(path);
    if(!root.exists())
    {
        qWarning() << "Path not found" << path;
        return;
    }

    QFileInfoList list = root.entryInfoList(QDir::Filter::NoDotAndDotDot | QDir::Filter::AllEntries);

    foreach(QFileInfo fi, list)
    {
        qInfo() << "--------------------";
        qInfo() << "Name" << fi.fileName();
        qInfo() << "Path" << fi.filePath();
        qInfo() << "Absolute" << fi.absoluteFilePath();
        qInfo() << "Created" << fi.birthTime().toString();
        qInfo() << "Modified" << fi.lastModified().toString();
        qInfo() << "Size" << fi.size();

        QString type = "Uknown";
        fi.isDir() ? type = "Dir" : type = "File";
        qInfo() << "Type" << type;

        if(recursive && fi.isDir()) test_list(fi.absoluteFilePath());
    }

}

// Modifying
void test_modify(QDir root)
{
    if(root.exists("test"))
    {
        qInfo() << "Test folder already exists";
        return;
    }

    if(root.mkdir("test"))
    {
        QDir dir("test");
        qInfo() << "Created" << dir.absolutePath();

        if(root.rename("test","test2"))
        {
            qInfo() << "Renamed" << dir.absolutePath(); //notice this points to a dir that no longer exists!
            qInfo() << "Test" << dir.exists();

            if(root.exists("test2"))
            {
                if(!root.rmdir("test2"))
                {
                    qInfo() << "Failed - could not remove the directory!";
                }
            }
        }
    }
}
// more about it in the next tutorial

using namespace std;


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch(type){
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s \n(%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s \n(%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s \n(%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s \n(%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s \n(%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    default:
        fprintf(stderr, "Other: %s \n(%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}

void test()
{
    qDebug() << "test"; // testing different warning levels here
    qInfo() << "test";
    qWarning() << "test";
    qCritical() << "test";
    //qFatal() << "test";

    Kitten kitty;
    kitty.meow();
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IOLBF, 1024); // weird output on some not so common Terminal applications
                                         //and the internal Terminal Output piping in '3 Application Output' in QtCreator
    setvbuf(stdin, NULL, _IONBF, 0);    // Disable buffering for Input also for the very same reason
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.
    QTextStream qin(stdin);
    cout << "Starting" << endl;


    QString command;
    bool running = true;
    do
    {
        cout << "Enter a command (start, stop, test, clear, which, where, dir or exit)" << endl;

        // weird behaviour for some terminals on Windows could probably prevented by doing:
        qin.resetStatus(); // or that lines at the very top of main just before bringing up QCoreApplication a: setvbuf(stdin, NULL, _IONBF, 0); // Disable buffering for Input
        command = qin.readLine();
        qInfo() << "You entered: " << command;

        //--- Install
        if(command.toUpper() == "START") qInstallMessageHandler(myMessageOutput);

        //--- Uninstall
        if(command.toUpper() == "STOP") qInstallMessageHandler(0);

        //--- Test
        if(command.toUpper() == "TEST") test();

        //--- Clear
        if(command.toUpper() == "CLEAR") CLEAR_SCREEN() ;

        //--- Which
        if(command.toUpper() == "WHICH") runTime();

        //--- Where
        if(command.toUpper() == "WHERE") whichRoot();

        //--- DIR
        if(command.toUpper() == "DIR") whichDir();

        //--- Exit
        if(command.toUpper() == "EXIT" || command.toUpper() == "QUIT")
        {
            cout.flush();
            running = false;

        }
    }
    while(running);



    cout << "\n Finished \n";
    return 0;

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec(); // this actually fires the application execution loop which could introduce problems if we think we are
                     // programming a very procedural commandline application, because the QCoreApplication is not designed for that.
}
