#ifndef SINE_GENERATOR_H
#define SINE_GENERATOR_H

#include <QThread>
#include <QString>
#include <QTime>
#include <QVector>

class SineGenerator: public QThread
{
    Q_OBJECT
public:
    explicit SineGenerator();
    void run() override;
    //std::map<QTime, double> data;
    int frequency;
    double sample_span_ms;
    double amplitude;
    QVector<double> dataY;
    QVector<int> dataX;

private:
    void generateSine(QTime from, QTime to);
    int m_startTime_msecs;

signals:
    void doneGenerating();
    void setRange(int rangeStart);

public slots:
    void on_Timer();
};

#endif // SINE_GENERATOR_H
