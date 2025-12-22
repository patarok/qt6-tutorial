#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QtConcurrent>
#include <QFuture>
#include <QList>
#include <numeric> // für std::accumulate

// Unsere "Pure Function" - Sie weiß nichts von anderen Threads oder globalen Variablen.
// Sie nimmt einen Wert und gibt einen neuen Wert zurück.
int doWork(int id)
{
    qInfo() << "Worker" << id << "startet auf:" << QThread::currentThread();

    int result = 0;
    for(int i = 0; i < 100; ++i) {
        result++; // Jeder arbeitet auf seiner eigenen lokalen Variable
        QThread::msleep(10);
    }

    qInfo() << "Worker" << id << "fertig. Lokales Ergebnis:" << result;
    return result;
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

    int max = 5;
    QList<int> indices = {1, 2, 3, 4, 5}; // Unsere IDs für die Worker

    qInfo() << "Main Thread:" << QThread::currentThread();

    // --- DER MONADISCHE SCHRITT ---
    // QtConcurrent::mapped startet die Funktion für jedes Element in der Liste.
    // Es gibt ein QFuture zurück, das die Ergebnisse EINSAMMELT, sobald sie fertig sind.

    QFuture<int> future = QtConcurrent::mapped(indices, doWork);

    // Wir "verketten" die Operation (monadisches Binding).
    // .then() wartet, bis ALLE Worker fertig sind, und nimmt dann die Liste der Ergebnisse.
    future.then([](QFuture<int> completedFuture) {

        QList<int> results = completedFuture.results();

        // Reduktion: Wir führen die Teilergebnisse zusammen.
        int totalCount = std::accumulate(results.begin(), results.end(), 0);

        qInfo() << "---";
        qInfo() << "Alle Threads fertig!";
        qInfo() << "Endgültiger Count (summiert):" << totalCount;

        QCoreApplication::quit(); // Beendet die Event-Loop
    });

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
