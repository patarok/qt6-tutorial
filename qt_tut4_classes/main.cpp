#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include "test.h"
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test* dog = Test::getTest(&a);
    dog->setObjectName("Spot");
    dog->setParent(&a);

    Test* cat = Test::getTest();
    cat->setObjectName("Princess Fortuna");
    cat->setParent(dog);

    // Trigger den Dump, während die App läuft
    QTimer::singleShot(1000, [&a]() {
        qInfo() << "\n=== QObject Tree ===";
        a.dumpObjectTree();
        qInfo() << "====================\n";
    });

    // Beende die App nach 3 Sekunden automatisch
    QTimer::singleShot(3000, &a, &QCoreApplication::quit);

    return a.exec(); // Einziger Aufruf von exec()
}
