#ifndef CAT_H
#define CAT_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QSharedPointer>

namespace Feline {

class Cat;

typedef QMap<QString, QSharedPointer<Cat>> CatDictionary;

class Cat : public QObject
{
    Q_OBJECT
public:
    explicit Cat(QObject *parent = nullptr);
    ~Cat();

    QString name() const;
    void setName(const QString &fooName);

    int age() const;
    void setAge(int age);

    QString makeSound(QString intention = "canihascheeseburger");

    static Cat* getCat(QObject *parent = nullptr);
    static CatDictionary getAllCats();
    static void displayCats(CatDictionary& cats);
    static void modifyCat(CatDictionary& cats, QString key);
    static void removeCat(CatDictionary& cats, QString key);
signals:

private:
    QString m_name;
    int m_age;

};

void addCat(CatDictionary &dictionary);
void findCat(CatDictionary &dictionary, QString key);
}

#endif // CAT_H
