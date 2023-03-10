#include "dataviewer.h"
#include <QAbstractAxis>
#include <QValueAxis>

DataViewer::DataViewer(DataProviderBase* dataProv, QChartView* chartView) : m_prov(dataProv), m_chartView(chartView)
{
    m_chart = new QChart();
    m_chart->legend()->hide();

    m_chart->addAxis(&m_xAxis, Qt::AlignBottom);
    m_chart->addAxis(&m_yAxis, Qt::AlignLeft);

    m_xAxis.setTickCount(3);
    m_xAxis.setFormat("dd.MM.yyyy hh:mm:ss");

    m_chart->addSeries(&m_series);
    m_series.attachAxis(&m_xAxis); // WICHTIIIIIG
    m_series.attachAxis(&m_yAxis); // WICHTIIIIIG

    connect(m_prov, &DataProviderBase::dataReady, this, &DataViewer::onDataReady);
}

QChart* DataViewer::getChart()
{
    return m_chart;
}

void DataViewer::setWindowSize(int msec)
{
    m_windowSize = msec;
}

int DataViewer::getWindowSize()
{
    return m_windowSize;
}

void DataViewer::onDataReady()
{
    Data d = m_prov->getData();
    if(d.points.size() == 0) return;

    m_data.reserve(m_data.size() + d.points.size());
    for(auto p : d.points)
    {
        m_data.push_back(QPointF(p.first.toMSecsSinceEpoch(), p.second));
    }

    QDateTime winEnd = QDateTime::fromMSecsSinceEpoch(m_data.last().x());
    QDateTime winBegin = winEnd.addMSecs(-m_windowSize);                

    if(d.points.size() != 1)
    {
        int deltaMsData = m_data.last().x() - m_data.first().x();
        int deltaPerPt = std::ceil(static_cast<double>(deltaMsData) / static_cast<double>(m_data.size()));
        int targetPts = static_cast<int>((m_windowSize / deltaPerPt) * 1.2);    // * 1.1 -> Sicherheitsüberschuss

        if(m_data.size() > targetPts)
        {
            m_data.erase(m_data.begin(), m_data.begin() + (m_data.count() - targetPts));
        }
    }
    else m_data.pop_front();

    m_series.replace(m_data);

    m_xAxis.setRange(winBegin, winEnd);
    m_xAxis.setTitleText(d.horizontalLabel);

    m_yAxis.setRange(d.yMin, d.yMax);
    m_yAxis.setTitleText(d.verticalLabel);
}
