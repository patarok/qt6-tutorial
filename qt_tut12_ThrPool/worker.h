#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QRunnable>

class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
    void run() Q_DECL_OVERRIDE; // <-- this macro tells the compiler: "If I messed up the signature of run(),
                                // don't let me compile."

signals:
    void started();   //not the best way
    void finished();

public slots:
    void work();

private:

};

#endif // WORKER_H
