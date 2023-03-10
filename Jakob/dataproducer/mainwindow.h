#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QTimer>

#include "sinusdataproducer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_u_producebutton_clicked();

    void on_u_freqBox_valueChanged(int arg1);

    void on_u_ampBox_valueChanged(int arg1);

    void on_u_sampleBox_valueChanged(int arg1);

    void on_u_updateRateBox_valueChanged(int arg1);

    void on_u_startbutton_clicked();

private:
    void onTimeOut();

    Ui::MainWindow *ui;
    sinusdataproducer m_prod;
    QDateTimeAxis m_axisX;
    QValueAxis m_axisY;
    QLineSeries m_series;
    QChart* m_chart;
    const int m_maxPts = 100;
    QTimer m_timer;
};
#endif // MAINWINDOW_H
