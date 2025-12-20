#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QTimer>
#include <QDebug>
#include <QPoint>  // ← Das fehlt!



void do_logLevelInfo(){

    int x = 10;
    QString text = "Hello";
    QList<int> numbers = {1, 2, 3};

    qInfo() << "x =" << x;
    qInfo() << "Text:" << text;
    qInfo() << "Numbers:" << numbers;  // Gibt [1, 2, 3] aus

    QPoint p(10, 20);
    qInfo() << "Point:" << p;  // Gibt QPoint(10,20) aus

    QString fileName = "C:\\somefile.foo";
    //Formatierung mit qInfo():
    //cpp// Hex-Zahlen
    qInfo() << Qt::hex << 255;  // "ff"

    // Ohne Zeilenumbruch
    qInfo().nospace() << "x=" << 10 << ", y=" << 20;

    // Mehrere Werte
    qInfo("Loading file: %s", fileName.toStdString().c_str());


    qDebug()    << "Debug info (nur development)";
    qInfo()     << "Informational message";
    qWarning()  << "Warning - something might be wrong";
    qCritical() << "Critical error!";
}


void do_qt()
{
    QTextStream qin(stdin);
    QTextStream qout(stdout);

    qInfo("This application will first give info on LogLevels \nand then ask you for your name. \nAfter input, it will quit by issuing a fatal error by intent.\n\n"); //


    do_logLevelInfo();

    qout << "Please enter your name: " << Qt::flush;



    QString name = qin.readLine();
    qout << "Hello, " << name << "\n";

    qFatal("Fatal error - app will terminate!");
    //QCoreApplication::quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qt_tut1_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    // code goes here:

    QTimer::singleShot(0, &do_qt);


    return a.exec();
}
