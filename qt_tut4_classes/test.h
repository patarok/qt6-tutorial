#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr); // this essentially says we can have a parent connection (which will ease our mm exp)
    ~Test();

    static Test* getTest(QObject *parent);

    static Test* getTest(); // bad idea jeans ! >>
signals:

public slots:
};

#endif // TEST_H
