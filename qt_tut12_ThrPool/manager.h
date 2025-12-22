#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QThreadPool>
#include <QRunnable> // QRunnable is NOT a QObject!!!
#include <QRandomGenerator>
#include <QDebug>



class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

signals:
    void work();   //not the best way

public slots:
    void start();
    void started();
    void finished();
    void quit();

private:
};

#endif // MANAGER_H
