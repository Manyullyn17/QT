#include "mainwindow.h"

#include <QChart>
#include <QChartView>
#include <QLineSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , chart{new QChart}
{
    setupUi(this);

    chart->legend()->hide();
    QChartView* chart_view = new QChartView(chart);

    main_layout->addWidget(chart_view);
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_input_textChanged()
{
    const auto& text = input->toPlainText();
    const auto& lines = text.split("\n");
    QLineSeries* series = new QLineSeries;
    //series->setPointsVisible();
    int x = 0;
    for (const auto& line : lines)
    {
        bool ok = false;
        double value = line.toDouble(&ok);

        if (ok)
        {
            series->append(x++, value);
        }
    }
    chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();

}


