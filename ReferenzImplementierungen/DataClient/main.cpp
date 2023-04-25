#include "mainwindow.h"
#include "netdataproducer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NetDataProducer producer{};
    MainWindow w{producer};
    w.show();
    return a.exec();
}
