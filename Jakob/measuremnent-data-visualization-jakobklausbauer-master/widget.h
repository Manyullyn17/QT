#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>

#include "sinusdataprovider.h"
#include "dataviewer.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLineSeries* m_series;
    SinusDataProvider* m_prov;
    DataViewer* m_viewer;
    QSpinBox* m_ui_amp;
    QSpinBox* m_ui_frequency;
    QSpinBox* m_ui_samplerate;
    QSpinBox* m_ui_updaterate;
    QSpinBox* m_ui_winSize;
    QTableView* m_tbl;

    void onAmpChanged();
    void onFrequencyChanged();
    void onSampleRateChanged();
    void onUpdateRateChanged();
    void onWinSizeChanged();
};
#endif // WIDGET_H
