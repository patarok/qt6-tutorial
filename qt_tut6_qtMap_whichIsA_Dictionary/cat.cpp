#include "cat.h"
#include <QDebug>
#include <QRandomGenerator>

//using namespace Feline;

namespace Feline {
Cat::Cat(QObject *parent)
    : QObject{parent}
{
    qInfo() << "this constructed" << this;
}

Cat::~Cat(){
    qInfo() << "this destructed" << this << " with the name: " << this->name() ;
}

QString Cat::name() const{
    return m_name;
}

void Cat::setName(const QString &fooName)
{
    this->m_name = fooName;
}

void Cat::setAge(int age)
{
    this->m_age = age;
}

int Cat::age() const
{
    return this->m_age;
}

Cat* Cat::getCat(QObject *parent)
{
    return new Cat();
}



CatDictionary Cat::getAllCats()
{
    CatDictionary cats;
    for (int var = 0; var < 5; ++var) {
        QSharedPointer<Cat> ptr(new Cat());
        ptr->setAge(QRandomGenerator::global()->bounded(1, 5));
        ptr->setName("unknown");
        cats.insert("pet" + QString::number(var), ptr);
    }

    return cats;
}

void Cat::displayCats(CatDictionary &cats)
{
    foreach(const QString key, cats.keys()){
        QSharedPointer<Cat> ptr = cats.value(key);
        qInfo() << key << ptr->name() << ptr->age() << ptr.data();
    }
}

void Cat::modifyCat(CatDictionary &cats, QString key)
{
    if(cats.contains(key))
        qInfo() << "Modifying: " << key;
    cats[key]->setAge(99);
    cats[key]->setName("Fluffy");
    displayCats(cats);
}

void Cat::removeCat(CatDictionary &cats, QString key)
{
    if(!cats.contains(key))
    {
        qInfo() << "Container does not contain requested element. Stopping.";
        return;
    }
    qInfo() << "removing: " << cats.value(key)->name();
    cats.remove(key);
}


void addCat(CatDictionary &dictionary)
{
    qInfo() << "adding and inserting.";
    QSharedPointer<Cat> ptr(new Cat());
    ptr->setAge(1);
    ptr->setName("Testcat");
    //dictionary.insert("abracatdabra", ptr);
    dictionary["abracatdabra"] = ptr; // whilst doing this to !INSERT!(a new 'Cat') is technically possible,
    //  it bears or "CATers" :)) ..the peril of overwriting an already existing Cat with the key "abracatdabra" already existant in the Map(dictionary)
    Cat::displayCats(dictionary);
}

// void findCat(CatDictionary &dictionary, QString key)
// {
//     qInfo() << "Exists:" << dictionary.contains(key);
// }
void findCat(CatDictionary &dictionary, QString key)
{
    qInfo() << "Exists:" << dictionary.contains(key);
    qInfo() << "is named:" << dictionary.value(key)->name();
    auto iter = dictionary.find(key);
    if(iter != dictionary.end())
        qInfo() << iter.key() << iter.value();
}

}
