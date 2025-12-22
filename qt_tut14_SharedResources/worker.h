#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>
#include <QFuture>
#include <QtConcurrent>
#include <QRunnable>

class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:

    // QRunnable interface
public:
    void run() Q_DECL_OVERRIDE;

    void setCount(int *newCount);

    void setMutex(QMutex *newMutex);

private:
    int *m_count;
    QMutex *m_mutex;
};

#endif // WORKER_H
