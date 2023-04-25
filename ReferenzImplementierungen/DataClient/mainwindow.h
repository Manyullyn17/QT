#pragma once

#include "ui_mainwindow.h"


#include <QtCharts/QtCharts>
#include <QMainWindow>
#include <QTime>
#include <QTimer>

class NetDataProducer;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(NetDataProducer& producer, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void produceAndDisplayData();
    void on_update_rate_input_valueChanged(int arg1);

private:
    NetDataProducer& m_producer;

    bool m_active = false;
    QTimer m_update_data_timer;
    int m_update_rate;


};
