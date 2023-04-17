// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include "my_thread.h"

QT_USE_NAMESPACE

#define NUM_SAMPLES 100
#define OFFSET 10

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");

    MyThread thread(NUM_SAMPLES, series);

    /*
    double samples[NUM_SAMPLES];
    for (int n = 0; n < NUM_SAMPLES; ++n)
        samples[n] = sin( 2*3.14159265359 * (n + OFFSET)/NUM_SAMPLES );

    for (int i = 0; i < NUM_SAMPLES; i++)
        series->append(i, samples[i]);
    */

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Have a Sine Wave");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-1.2, 1.2);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    thread.run();

    while(true)
    {
        chartView->update();
    }

    return a.exec();
}
