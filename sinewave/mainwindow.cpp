#include "mainwindow.h"
#include <QDebug>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(&m_sine_generator, &SineGenerator::doneGenerating, this, &MainWindow::on_sine_generated);

    m_sine_generator.frequency = FrequencyBox->value();
    m_sine_generator.sample_span_ms = 1000.0/SampleRateBox->value();
    m_sine_generator.amplitude = AmplitudeBox->value();

    sine_chart->legend()->hide();
    sine_chart->setTitle("Sine Chart");
    sine_chart->addSeries(m_data);

    m_axisX->setTitleText("Time [ms]");
    m_axisX->setRange(0, 1000);
    sine_chart->addAxis(m_axisX, Qt::AlignBottom);

    m_axisY->setTitleText("V");
    m_axisY->setRange(-1, 1);
    sine_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_data->attachAxis(m_axisX);
    m_data->attachAxis(m_axisY);

    SineChartView->setRenderHint(QPainter::Antialiasing);

    SineChartView->setChart(sine_chart);

    m_timer.setInterval(1000.0/UpdateRateBox->value());
    connect(&m_timer, &QTimer::timeout, &m_sine_generator, &SineGenerator::on_Timer);

    connect(&m_sine_generator, &SineGenerator::setRange, this, &MainWindow::setRange);
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_StartButton_clicked()
{
    if (m_started)  // stop
    {
        m_started = false;
        StartButton->setText("Start");
        m_sine_generator.quit();
        m_timer.stop();
    }
    else    // start
    {
        m_started = true;
        StartButton->setText("Stop");
        m_sine_generator.run();
        m_timer.start();
    }
}

void MainWindow::on_FrequencyBox_valueChanged(int arg1)
{
    m_sine_generator.frequency = arg1;
}

void MainWindow::on_AmplitudeBox_valueChanged(double arg1)
{
    m_sine_generator.amplitude = arg1;
    m_axisY->setRange(-arg1, arg1);
}


void MainWindow::on_SampleRateBox_valueChanged(int arg1)
{
    m_sine_generator.sample_span_ms = 1000.0/arg1;
}


void MainWindow::on_UpdateRateBox_valueChanged(int arg1)
{
    m_timer.setInterval(1000.0/UpdateRateBox->value());
}

void MainWindow::on_sine_generated()
{
    m_data->clear();

    for (int i = 0; i < m_sine_generator.dataX.length(); i++)
    {
        m_data->append(m_sine_generator.dataX[i], m_sine_generator.dataY[i]);
    }

    SineChartView->update();
    m_sine_generator.dataX.clear();
    m_sine_generator.dataY.clear();
}

void MainWindow::setRange(int rangeStart)
{
    m_axisX->setRange(rangeStart, rangeStart+1000);
}
