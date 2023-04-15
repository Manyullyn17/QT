#pragma once

#include "ui_mainwindow.h"


#include <QtCharts/QtCharts>
#include <QMainWindow>
#include <QTime>
#include <QTimer>

class DataProducer;
class DataServer;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_produceSineDataButton_clicked();
    void on_startButton_clicked();
    void produceAndDisplayData();
    void on_update_rate_input_valueChanged(int ur);

    void on_sawButton_clicked();

    void on_sineButton_clicked();

    void on_frequency_input_valueChanged(int freq);

    void on_amplitude_input_valueChanged(double amp);

    void on_sample_rate_input_valueChanged(int sr);

private:
    enum WaveForm
    {
        SINE,
        SAW
    };

    WaveForm m_wave_form;
    void setWaveForm(WaveForm wave_form);
    QTime m_start_time{QTime::currentTime()};
    QTime m_segment_start_time{m_start_time};
    DataProducer* m_data_producer;
    DataServer* m_data_server;

    bool m_active = false;
    QTimer m_update_data_timer;
    int m_update_rate;

    QChart* m_chart;
    QChartView* m_chart_view;
};
