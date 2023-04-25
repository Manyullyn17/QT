#pragma once

#include "dataproducer.h"

class SawToothProducer : public DataProducer
{
public:
    SawToothProducer(double frequency = 1.0, double amplitude = 1.0, double sample_rate = 100.0);

public:
    std::map<QTime, double> getData(const QTime &from, const QTime &to ) const override;
    std::map<QTime, double> getData(int duration_msec) const override;

    QTime m_start_time;
};

