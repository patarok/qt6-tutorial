#include <QCoreApplication>
#include <QDebug>
#include "cat.h"


void test(Cat &cat){
    qInfo() << "Addr " << &cat;
}

void test2(Cat *cat){
    qInfo() << "Addr " << cat;
}


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


    Cat death;
    death.setObjectName("the grim reaper");
    Cat kitty;
    kitty.setObjectName("the grim kitty");

    test(kitty);
    test2(&kitty);

    test(death);
    test2(&death);

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    qInfo() << &kitty;

    return a.exec();
}
