#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include "sine_generator.h"
#include <QLineSeries>
#include <QTimer>
#include <QValueAxis>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_StartButton_clicked();
    void on_AmplitudeBox_valueChanged(double arg1);
    void on_SampleRateBox_valueChanged(int arg1);
    void on_UpdateRateBox_valueChanged(int arg1);
    void on_sine_generated();
    void on_FrequencyBox_valueChanged(int arg1);

private:
    bool m_started = false;
    SineGenerator m_sine_generator;
    QChart *sine_chart = new QChart();
    QLineSeries *m_data = new QLineSeries();
    QTimer m_timer;
    QValueAxis *m_axisX = new QValueAxis();
    QValueAxis *m_axisY = new QValueAxis();

public slots:
    void setRange(int from);
};
#endif // MAINWINDOW_H
