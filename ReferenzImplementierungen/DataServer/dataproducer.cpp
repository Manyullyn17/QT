#include "dataproducer.h"

DataProducer::DataProducer(double frequency, double amplitude, double sample_rate)
    : m_frequency{frequency}
    , m_amplitude{amplitude}
    , m_sample_rate{sample_rate}
{

}

DataProducer::~DataProducer()
{

}


double DataProducer::getFrequency() const
{
    return m_frequency;
}

void DataProducer::setFrequency(double newFrequency)
{
    m_frequency = newFrequency;
}

double DataProducer::getAmplitude() const
{
    return m_amplitude;
}

void DataProducer::setAmplitude(double newAmplitude)
{
    m_amplitude = newAmplitude;
}

double DataProducer::getSampleRate() const
{
    return m_sample_rate;
}

void DataProducer::setSampleRate(double newSample_rate)
{
    m_sample_rate = newSample_rate;
}
