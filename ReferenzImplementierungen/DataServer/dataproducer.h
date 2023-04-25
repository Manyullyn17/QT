#pragma once

#include <map>
#include <QTime>

class DataProducer
{
public:
    DataProducer(double frequency = 1.0, double amplitude = 1.0, double sample_rate = 100.0);
    virtual ~DataProducer();
    virtual std::map<QTime, double> getData(const QTime& from, const QTime& to = QTime{}) const = 0;
    virtual std::map<QTime, double> getData(int duration_msec) const = 0;

    double getFrequency() const;
    void setFrequency(double newFrequency);

    double getAmplitude() const;
    void setAmplitude(double newAmplitude);

    double getSampleRate() const;
    void setSampleRate(double newSample_rate);

protected:
    double m_frequency;
    double m_amplitude;
    double m_sample_rate;
};

