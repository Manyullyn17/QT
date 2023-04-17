#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_chart = new QChart();
    m_chart->legend()->hide();

    m_chart->addAxis(&m_axisX, Qt::AlignBottom);
    m_chart->addAxis(&m_axisY, Qt::AlignLeft);

    m_axisX.setTickCount(3);
    m_axisX.setFormat("hh:mm:ss");

    m_chart->addSeries(&m_series);
    m_series.attachAxis(&m_axisX);
    m_series.attachAxis(&m_axisY);

    ui->u_chart->setChart(m_chart);
    ui->u_chart->setRenderHint(QPainter::Antialiasing);

    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::onTimeOut);
    m_timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_u_producebutton_clicked()
{
    std::map<QDateTime, double> data = m_prod.getData();
    qDebug() << data.size();

    for(auto p : data)
    {
        qDebug() << p.first.toMSecsSinceEpoch();
        m_series.append(p.first.toMSecsSinceEpoch(), p.second);
    }

    while(m_series.count() > m_maxPts)
    {
        m_series.remove(0);
    }

    m_axisX.setRange(QDateTime::fromMSecsSinceEpoch(m_series.at(0).x()), QDateTime::fromMSecsSinceEpoch(m_series.at(m_series.count() - 1).x()));
    m_axisY.setRange(-(m_prod.getAmplitude() * 1.1), m_prod.getAmplitude() * 1.1);

    qDebug() << m_series.count();
}

void MainWindow::onTimeOut()
{
    on_u_producebutton_clicked();
}

void MainWindow::on_u_freqBox_valueChanged(int arg1)
{
    m_prod.setFrequency(arg1);
}

void MainWindow::on_u_ampBox_valueChanged(int arg1)
{
    m_prod.setAmplitude(arg1);
}

void MainWindow::on_u_sampleBox_valueChanged(int arg1)
{
    m_prod.setSampleRate(arg1);
}

void MainWindow::on_u_updateRateBox_valueChanged(int arg1)
{
    m_timer.setInterval(1000 / arg1);
}

void MainWindow::on_u_startbutton_clicked()
{
    if(m_timer.isActive())
    {
        m_timer.stop();
        ui->u_startbutton->setText("Start");
    }
    else
    {
        m_timer.start();
        ui->u_startbutton->setText("Stop");
    }
}

