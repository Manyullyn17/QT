#ifndef SINUSDATAPROVIDER_H
#define SINUSDATAPROVIDER_H

#include "dataproviderbase.h"
#include <QObject>
#include <QDebug>
#define _USE_MATH_DEFINES
#include <cmath>
#include <QTimer>

class SinusDataProvider : public DataProviderBase
{
    Q_OBJECT
public:
    SinusDataProvider();
    void run();
    Data getData();

    void setAmplitude(double amplitude);
    double getAmplitude();

    void setFrequency(double frequency);
    double getFrequency();

    void setSampleRate(int samples);
    int getSampleRate();

    void setRefreshIntervall(int msec);
    int getRefreshIntervall();
    void setAutoRefresh(bool refresh);
    void doRefresh();

private:
    void onRefreshExpired();

    double m_amplitude = 1;
    double m_frequency = 1;
    int m_sampleRate = 100;
    int m_refreshIntMs = 100;

    bool m_needsRefresh = false;
    QTimer m_refreshTimer;
    QDateTime m_begin, m_end, m_dataBegin;
};

#endif // SINUSDATAPROVIDER_H
