#ifndef SINUSDATAPRODUCER_H
#define SINUSDATAPRODUCER_H

#include <map>
#include <QDateTime>

class sinusdataproducer
{
public:
    sinusdataproducer();
    std::map<QDateTime, double> getData();

    void setAmplitude(double amplitude);
    double getAmplitude();

    void setFrequency(double frequency);
    double getFrequency();

    void setSampleRate(int rate);
    int getSampleRate();

private:
    QDateTime m_begin;
    double m_amplitude = 1, m_frequency = 1;
    int m_samplerate = 100;
    const int m_maxSeconds = 10;
};

#endif // SINUSDATAPRODUCER_H
