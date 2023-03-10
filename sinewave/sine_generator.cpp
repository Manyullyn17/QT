#include "sine_generator.h"
#include <QDebug>
#include <QtMath>

SineGenerator::SineGenerator()
{

}

void SineGenerator::run()
{
    QTime startTime = QTime::currentTime();
    m_startTime_msecs = startTime.msecsSinceStartOfDay();
}

void SineGenerator::generateSine(QTime from, QTime to)
{
    int timeStamp = from.msecsSinceStartOfDay() - m_startTime_msecs;

    int from_msec = sample_span_ms * (from.msecsSinceStartOfDay() / sample_span_ms);
    if (from_msec < from.msecsSinceStartOfDay())
        from_msec += sample_span_ms;

    int to_msec = sample_span_ms * (to.msecsSinceStartOfDay() / sample_span_ms);

    int delta_time;

    for(int i = from_msec; i <= to_msec; i++)
    {
        delta_time = timeStamp - m_startTime_msecs;
        dataY.append(amplitude * sin(2 * M_PI * static_cast<double>(delta_time) * (frequency/1000.0)));
        dataX.append(timeStamp);
        timeStamp += sample_span_ms;
    }

    emit doneGenerating();
}

void SineGenerator::on_Timer()
{
    QTime from = QTime::currentTime();
    QTime to = QTime::currentTime();
    to = to.addMSecs(1000/sample_span_ms);
    emit setRange(from.msecsSinceStartOfDay()-m_startTime_msecs);
    generateSine(from, to);
}
