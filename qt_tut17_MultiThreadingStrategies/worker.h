#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QDebug>
#include <QEventLoop>
#include <QScopedPointer>
#include <QTimer>


class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

signals:
    void finished();

    // QRunnable interface
public:
    void run() Q_DECL_OVERRIDE;

public slots:
    void work();

private:
    QTimer timer;
};

#endif // WORKER_H
