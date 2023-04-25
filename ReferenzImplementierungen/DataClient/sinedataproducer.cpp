#include "sinedataproducer.h"
#include <math.h>

SineDataProducer::SineDataProducer(double frequency, double amplitude, double sample_rate)
    : m_frequency(frequency)
    , m_amplitude(amplitude)
    , m_sample_rate(sample_rate)
    , m_start_time{QTime::currentTime()}
{
}

std::map<QTime, double> SineDataProducer::getData(const QTime &from, const QTime &to) const
{
    std::map<QTime, double> data;
    QTime actual_to = to.isValid() ? to : QTime::currentTime();
    //QTime to_minus_1sec = actual_to.addSecs(-1);
    double sample_span_ms = 1000.0/m_sample_rate;
    int from_msec = sample_span_ms * (from.msecsSinceStartOfDay() / sample_span_ms);
    if(from_msec < from.msecsSinceStartOfDay())
    {
        from_msec += sample_span_ms;
    }
    int to_msec = sample_span_ms * (actual_to.msecsSinceStartOfDay() / sample_span_ms) - sample_span_ms;

    for(int time_stamp = from_msec; time_stamp <= to_msec; time_stamp+=sample_span_ms)
    {
        int delta_time = time_stamp - m_start_time.msecsSinceStartOfDay();
        data[QTime::fromMSecsSinceStartOfDay(time_stamp)] =
                m_amplitude * std::sin(2*M_PI*static_cast<double>(delta_time)*(m_frequency/1000.0));
    }
    return data;
}

double SineDataProducer::getFrequency() const
{
    return m_frequency;
}

void SineDataProducer::setFrequency(double newFrequency)
{
    m_frequency = newFrequency;
}

double SineDataProducer::getAmplitude() const
{
    return m_amplitude;
}

void SineDataProducer::setAmplitude(double newAmplitude)
{
    m_amplitude = newAmplitude;
}

double SineDataProducer::getSampleRate() const
{
    return m_sample_rate;
}

void SineDataProducer::setSampleRate(double newSample_rate)
{
    m_sample_rate = newSample_rate;
}
