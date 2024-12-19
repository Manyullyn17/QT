
#include <QCoreApplication>
#include "test.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test lol = 420;

    qDebug() << lol.getBitches();
    lol.setBitches(69);
    qDebug() << lol.getBitches();

    return a.exec();
}
