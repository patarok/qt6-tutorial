#include <QCoreApplication>
#include <QMap>
#include <QDebug>
#include <QRandomGenerator>
#include <QSharedPointer>
#include "cat.h"

using namespace Feline;

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

    //handling Strings lead to Lists (which are called Vector in CPP terminology)
    //and Vector/Lists of course lead to Maps/Dictionaries
    //in Qt we have QMap Class:

    QMap<int, QString>* luckies = new QMap<int, QString>(); // heap allocated
    QMap<int, QString> kittens; // stack allocated

    kittens.insert(0, QString("Rowr"));
    luckies->insert(1, QString("Mewr"));

    qInfo() << luckies;
    qInfo() << kittens;


    qInfo() << "My lucky number is: " << kittens.key("Rowr", -1);
    qInfo() << "The value to lucky number: " << luckies->key("Mewr", -1) << " is : " << luckies->value(luckies->key("Mewr", -1));

    qInfo() << "Honey! Look at all those cats! >> \n";
    CatDictionary myCats = Cat::getAllCats(); // <- this is the actual CatDictionary which contains all the cats we create in the for loop
    qInfo() << myCats;

    qInfo() << "Using static display method in Cat >> \n";
    Cat::displayCats(myCats);

    Cat::modifyCat(myCats, "pet1");
    qInfo() << "Display modified Cat >> \n";
    Cat::displayCats(myCats);
    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    addCat(myCats);
    // since we are using the dictionary by just adressing a key when inserting with addCat now...
    // we are actually throwing out what was there (the 'Testcat' which was there before)
    // and throw in a new one. we will see the Deconstructor doing its job on the second call to addCat

    qInfo() << "Display again after second addCat call :)) >> \n";
    addCat(myCats);

    qInfo() << "Is it true that a cat keyed --abracatdabra-- exists? : ";
    findCat(myCats, "abracatdabra");

    Cat::removeCat(myCats, "pet1");

    //--- cleanup
    qInfo() << "Clearing";
    myCats.clear();

    return a.exec();
}
