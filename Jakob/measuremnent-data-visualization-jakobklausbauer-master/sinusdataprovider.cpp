#include "sinusdataprovider.h"

SinusDataProvider::SinusDataProvider() : m_begin(QDateTime::currentDateTime()), m_dataBegin(QDateTime::currentDateTime())
{
    m_data.horizontalLabel = "Time [s]";
    m_data.verticalLabel = "Value [-]";

    connect(&m_refreshTimer, &QTimer::timeout, this, &SinusDataProvider::onRefreshExpired);
    m_refreshTimer.setInterval(m_refreshIntMs);
}

void SinusDataProvider::run()
{
    m_begin = QDateTime::currentDateTime();

    while(true)
    {
        if(m_needsRefresh)
        {
            m_needsRefresh = false;

            if(m_begin.msecsTo(m_end) <= 0)
            {
                // Beginn und Ende ungefähr gleich
                continue;
            }

            if(m_begin.msecsTo(m_end) < static_cast<int>(1000 / m_sampleRate))
            {
                // zu kurze Zeitperiode, um einen Punkt abtasten zu können -> KEIN dataReady
                continue;
            }

            // Daten generieren
            m_data.points.clear();
            m_data.yMax = m_amplitude * 1.1;
            m_data.yMin = m_amplitude * (-1.1);

            int msecPerSample = static_cast<int>(1000 / m_sampleRate) > 0 ? static_cast<int>(1000 / m_sampleRate) : 1;

            int msecStart = m_dataBegin.time().msecsSinceStartOfDay();
            int msecSinceDataBegin = m_dataBegin.msecsTo(m_begin);
            int msecToEnd = m_dataBegin.msecsTo(m_end);

            for(int t = msecSinceDataBegin; (t <= msecToEnd) && (m_data.points.size() < m_sampleRate); t += msecPerSample)
            {
                double res = std::sin(2 * M_PI * m_frequency * (t / 1000.f)) * m_amplitude;

                QDateTime time = QDateTime::currentDateTime();
                time.setTime(QTime::fromMSecsSinceStartOfDay(msecStart + t));
                m_data.points.insert(std::pair<QDateTime, double>(time, res));
            }

            m_begin = m_end;

            emit dataReady();
        }

        msleep(1); // das busy waiting durch die m_needsRefresh Variable sollte man geg. ersetzen
    }
}

Data SinusDataProvider::getData()
{
    return m_data;
}

void SinusDataProvider::setAmplitude(double amplitude)
{
    m_amplitude = amplitude;
}

double SinusDataProvider::getAmplitude()
{
    return m_amplitude;
}

void SinusDataProvider::setFrequency(double frequency)
{
    m_frequency = frequency;
}

double SinusDataProvider::getFrequency()
{
    return m_frequency;
}

void SinusDataProvider::setSampleRate(int samples)
{
    m_sampleRate = samples;
}

int SinusDataProvider::getSampleRate()
{
    return m_sampleRate;
}

void SinusDataProvider::setRefreshIntervall(int msec)
{
    m_refreshIntMs = msec;
    m_refreshTimer.setInterval(m_refreshIntMs);
}

int SinusDataProvider::getRefreshIntervall()
{
    return m_refreshTimer.interval();
}

void SinusDataProvider::setAutoRefresh(bool refresh)
{
    if(refresh) m_refreshTimer.start();
    else m_refreshTimer.stop();
}

void SinusDataProvider::doRefresh()
{
    m_end = QDateTime::currentDateTime();
    m_needsRefresh = true;
}

void SinusDataProvider::onRefreshExpired()
{
    m_end = QDateTime::currentDateTime();
    m_needsRefresh = true;
}
