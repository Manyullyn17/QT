#include <my_thread.h>

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread thread1("A");
    MyThread thread2("B");
    MyThread thread3("C");

    thread1.start();
    thread2.start();
    thread3.start();

    return a.exec();
}
