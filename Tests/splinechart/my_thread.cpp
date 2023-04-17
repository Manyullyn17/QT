#include "my_thread.h"
#include <QDebug>

MyThread::MyThread(int samples, QSplineSeries *series) :
    m_samples{samples}, m_series{series}
{

}

void MyThread::run()
{
    m_series->clear();

    double samples[m_samples];
    for (int n = 0; n < m_samples; ++n)
        samples[n] = sin( 2*3.14159265359 * (n + m_offset)/m_samples);

    for (int i = 0; i < m_samples; i++)
        m_series->append(i, samples[i]);

    if (m_offset++ >= m_samples)
        m_offset = 0;
}
