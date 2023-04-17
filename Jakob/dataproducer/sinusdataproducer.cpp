#include "sinusdataproducer.h"

sinusdataproducer::sinusdataproducer()
{
    m_begin = QDateTime::currentDateTime();
}

std::map<QDateTime, double> sinusdataproducer::getData()
{
    std::map<QDateTime, double> results;

    QDateTime end = QDateTime::currentDateTime();
    if(m_begin == end) return results;

    int msecPerSample = static_cast<int>(1000 / m_samplerate) > 0 ? static_cast<int>(1000 / m_samplerate) : 1;
    int msecStart = m_begin.time().msecsSinceStartOfDay();
    int msecToEnd = end.time().msecsSinceStartOfDay();

    for(int t = msecStart; t <= msecToEnd; t += msecPerSample)
    {
        double res = std::sin(2 * M_PI * m_frequency * static_cast<double>(t / 1000.f)) * m_amplitude;

        QDateTime time = QDateTime::currentDateTime();
        time.setTime(QTime::fromMSecsSinceStartOfDay(t));
        results.insert(std::pair<QDateTime, double>(time, res));
    }

    m_begin = end;

    return results;
}

void sinusdataproducer::setAmplitude(double amplitude)
{
    m_amplitude = amplitude;
}

double sinusdataproducer::getAmplitude()
{
    return m_amplitude;
}

void sinusdataproducer::setFrequency(double frequency)
{
    m_frequency = frequency;
}

double sinusdataproducer::getFrequency()
{
    return m_frequency;
}

void sinusdataproducer::setSampleRate(int rate)
{
    m_samplerate = rate;
}

int sinusdataproducer::getSampleRate()
{
    return m_samplerate;
}
