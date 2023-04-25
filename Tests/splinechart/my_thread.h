#ifndef MY_THREAD_H
#define MY_THREAD_H

#include <QThread>
#include <QString>
#include <QtCharts/QSplineSeries>

class MyThread: public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int samples, QSplineSeries *series);
    void run() override;

private:
    int m_samples;
    QSplineSeries *m_series;
    int m_offset = 0;
};

#endif // MY_THREAD_H
