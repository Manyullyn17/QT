#ifndef DATAPROVIDERBASE_H
#define DATAPROVIDERBASE_H

#include <QThread>
#include <QObject>
#include <QTime>
#include <QLineSeries>
#include <map>

struct Data
{
    std::map<QDateTime, double> points;
    double yMax, yMin;
    QString horizontalLabel;
    QString verticalLabel;
};

class DataProviderBase : public QThread
{
    Q_OBJECT
public:
    DataProviderBase();
    ~DataProviderBase();
    virtual void run() override = 0;
    virtual Data getData() = 0;

signals:
    void dataReady();

protected:
    Data m_data;
};



#endif // DATAPROVIDERBASE_H
