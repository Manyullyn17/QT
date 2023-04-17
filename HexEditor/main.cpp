#include "hexeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexEditor w;
    w.show();
    return a.exec();
}
