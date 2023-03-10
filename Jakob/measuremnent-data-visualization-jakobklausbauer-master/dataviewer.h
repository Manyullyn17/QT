#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QObject>
#include <QChart>
#include <QChartView>
#include <QDateTimeAxis>
#include <QValueAxis>

#include "dataproviderbase.h"

class DataViewer : public QObject
{
    Q_OBJECT
public:
    DataViewer(DataProviderBase* dataProv, QChartView* chartView);

    QChart* getChart();

    void setWindowSize(int msec);
    int getWindowSize();
private:
    void onDataReady();

    int m_windowSize = 5000;
    QDateTimeAxis m_xAxis;
    QValueAxis m_yAxis;
    QList<QPointF> m_data;
    QLineSeries m_series;
    DataProviderBase* m_prov;
    QChart* m_chart;
    QChartView* m_chartView;
};

#endif // DATAVIEWER_H
