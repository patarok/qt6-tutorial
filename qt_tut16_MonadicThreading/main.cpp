#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QtConcurrent>
#include <QFuture>
#include <QList>
#include <cmath>

// Simulation einer rechenintensiven mathematischen Operation (z.B. Signalverarbeitung)
// Diese Funktion ist "Pure": Sie hängt nur von ihren Eingabewerten ab.
double transformData(int rawValue)
{
    // Wir zeigen an, welcher Thread gerade diesen spezifischen Wert verarbeitet
    // qInfo() << "Thread" << QThread::currentThreadId() << "verarbeitet Wert:" << rawValue;

    // Simulation eines komplexen Algorithmus (z.B. Normalisierung und Logarithmus)
    double step1 = std::pow(rawValue, 2.0);
    double step2 = std::sqrt(step1 + 0.5);

    // Künstliche Verzögerung, um reale Last zu simulieren
    QThread::msleep(QRandomGenerator::global()->bounded(5, 20));

    return std::log10(step2);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 1. UNSERE DATEN: Ein großer Datensatz (z.B. 100 Sensor-Messwerte)
    QList<int> rawDataSet;
    for(int i = 1; i <= 100; ++i) rawDataSet << i;

    qInfo() << "Starte parallele Transformation von" << rawDataSet.size() << "Werten...";
    qInfo() << "Main Thread ist frei und bereit für UI/Events:" << QThread::currentThread();

    // 2. MAP-PHASE (Monadisch):
    // QtConcurrent teilt die 100 Werte automatisch auf alle verfügbaren Kerne auf.
    // Ein M3 mit 8 Kernen würde hier ca. 12-13 Werte pro Kern gleichzeitig bearbeiten.
    QFuture<double> processingFuture = QtConcurrent::mapped(rawDataSet, transformData);

    // 3. CONTINUATION (Der monadische "Bind"):
    // Wenn alle 100 Werte transformiert wurden, wird dieser Block ausgeführt.
    processingFuture.then(QtFuture::Launch::MainThread, [](QFuture<double> completedFuture) {

        // Hier liegen nun die transformierten Daten vor
        QList<double> results = completedFuture.results();

        // 4. REDUCE-PHASE: Statistische Auswertung
        double sum = std::accumulate(results.begin(), results.end(), 0.0);
        double average = sum / results.size();

        qInfo() << "--------------------------------------------------";
        qInfo() << "Transformation abgeschlossen!";
        qInfo() << "Anzahl verarbeiteter Elemente:" << results.size();
        qInfo() << "Berechneter Durchschnittswert:" << average;
        qInfo() << "--------------------------------------------------";

        QCoreApplication::quit();
    });

    return a.exec();
}
