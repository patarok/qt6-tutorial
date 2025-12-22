#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>


class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

    bool producer() const;
    void setProducer(bool newProducer);

signals:
    void produced(int value);   // signal which says : we have produced a value
    void finished();            // signal that says: we are done producing

public slots:
    void consume(int value);    // is going to consume a signal from somewhere else (in this case some other thread)
    void start();               // gonna be starting when we start in our thread. -> we can not start in our constructor.
    void quit();                // self explanatory

private:
    QTimer *m_timer;            // timers can not be started from another thread.
    bool m_producer;
    int m_count;

    void timeout();

};

#endif // WORKER_H
