#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <qforeach.h>

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

    QString line("Hello World");
    QString lineTwo("Look:");
    qInfo() << line;
    QString name;

    name = "Ein Name.";


    int pos = 504;
    int max = 7356;

    QString status = QString("Processing file %1 of %2").arg(pos).arg(max);
    qInfo() << "varname 'name':" << name;
    qInfo() << status;

    for(int i = 0; i < line.length(); i++)
    {
        QChar c = line.at(i);
        qInfo() << c;
    }

    // Comparing and Searching
    qInfo() << "Compare" << !line.compare("hello world", Qt::CaseInsensitive);
    qInfo() << "Starts" << line.startsWith("hello", Qt::CaseInsensitive);
    qInfo() << "Ends" << line.endsWith("hello", Qt::CaseInsensitive);
    qInfo() << "Contains" << line.contains("hello", Qt::CaseInsensitive); // can be issued with our without values to Case-Sensitivity ... they have defaults.
    qInfo() << "Index" << line.indexOf("lo", Qt::CaseInsensitive);

    //modifying and parsing
    line.append("\r\nThis is a Windows line return/newline ");
    lineTwo.append(" Today Bob said: \"Hello wife!\". Then he looked through the empty living room!");
    qInfo().noquote() << lineTwo << "\n";
    lineTwo.replace("!","?");
    lineTwo.remove("Look: Today");
    lineTwo.replace("through", "questioningly");
    lineTwo.replace(lineTwo.lastIndexOf('?'), 1, '.');
    qInfo().noquote() << "Then, again" << lineTwo;

    qInfo().noquote() << "\nUPPER:" << line.toUpper();
    qInfo().noquote() << "lower:" << line.toLower();
    qInfo().noquote() << "\nMid:" << line.mid(3, 5);
    QString splittable("Apfel, Orange, Birne, Banane");
    qInfo() << "\nbefore split: " << splittable << "\n";

    QStringList list = splittable.split(", ");

    qInfo() << "\nFOR:\n";
    for (QString item : list) {
        qInfo() << "sole: " << item << "\n";
    }
    qInfo() << "\nFOREACH:\n";
    foreach (QString item, list) {
        qInfo() << "sole: " << item << "\n";
    }

    forever


    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
