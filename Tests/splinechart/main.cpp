// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <qthread.h>

QT_USE_NAMESPACE

#define NUM_SAMPLES 100

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //![1]
    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");
    //![1]

    double samples[NUM_SAMPLES];
    for (int n = 0; n < NUM_SAMPLES; ++n)
        samples[n] = sin( 2*3.14159265359 * n/NUM_SAMPLES );

    for (int i = 0; i < NUM_SAMPLES; i++)
        series->append(i, samples[i]);

    //![2]
    //series->append(0, 6);
    //series->append(2, 4);
    //series->append(3, 8);
    //series->append(7, 4);
    //series->append(10, 5);
    //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    //![2]

    //![3]
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Have a Sine Wave");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-1.2, 1.2);
    //![3]

    //![4]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![4]

    //![5]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
    //![5]

    series->clear();
    for (int n = 0; n < NUM_SAMPLES; ++n)
        samples[n] = sin( (2*3.14159265359 * n/NUM_SAMPLES)-0.1 );

    for (int i = 0; i < NUM_SAMPLES; i++)
        series->append(i, samples[i]);

    chartView->update();

    return a.exec();
}
