#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client Test;
    Test.Connect();

    return a.exec();
}
