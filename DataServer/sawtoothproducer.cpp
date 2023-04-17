#include "sawtoothproducer.h"

SawToothProducer::SawToothProducer(double frequency, double amplitude, double sample_rate)
    : DataProducer{frequency, amplitude, sample_rate}
    , m_start_time{QTime::currentTime()}
{
}

std::map<QTime, double> SawToothProducer::getData(int duration_msec) const
{
    QTime to = QTime::currentTime();
    QTime from = to.addMSecs(-duration_msec);
    return getData(from, to);
}

std::map<QTime, double> SawToothProducer::getData(const QTime &from, const QTime &to) const
{
    std::map<QTime, double> data;
    QTime actual_to = to.isValid() ? to : QTime::currentTime();
    //QTime to_minus_1sec = actual_to.addSecs(-1);
    double sample_span_ms = m_sample_rate ? 1000.0/m_sample_rate : 0;
    int from_msec = sample_span_ms * (from.msecsSinceStartOfDay() / sample_span_ms);
    if(from_msec < from.msecsSinceStartOfDay())
    {
        from_msec += sample_span_ms;
    }
    int to_msec = sample_span_ms * (actual_to.msecsSinceStartOfDay() / sample_span_ms) - sample_span_ms;

    double period = 1000.0 / m_frequency;
    for(int time_stamp = from_msec; time_stamp <= to_msec; time_stamp+=sample_span_ms)
    {
        double delta_time = static_cast<double>(time_stamp);

        data[QTime::fromMSecsSinceStartOfDay(time_stamp)] =
                2.0 * m_amplitude * ((delta_time / period - std::floor(delta_time / period + 0.5)));
    }
    return data;
}
