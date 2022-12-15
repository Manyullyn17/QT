#include "my_thread.h"
#include <QDebug>

MyThread::MyThread(const QString& name) :
    m_name{name}
{

}

void MyThread::run()
{
    for(int i = 0; i <= 100; i++)
    {
        qDebug() << m_name << " " << i;
    }
    quit();
}
