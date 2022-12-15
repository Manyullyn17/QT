#ifndef MY_THREAD_H
#define MY_THREAD_H

#include <QThread>
#include <QString>

class MyThread: public QThread
{
    Q_OBJECT
public:
    explicit MyThread(const QString& name);
    void run() override;

private:
    QString m_name;
};

#endif // MY_THREAD_H
