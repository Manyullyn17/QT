#include "mainwindow.h"

#include "dataserver.h"
#include "sawtoothproducer.h"
#include "sinedataproducer.h"

#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , m_wave_form(SAW)
    , m_data_producer{new SawToothProducer}
    , m_data_server{new DataServer{*m_data_producer}}
{
    setupUi(this);
    host_input->setDisabled(true);

    m_chart  = new QChart;
    m_chart_view = new QChartView(m_chart);
    m_chart_view->setRenderHint(QPainter::Antialiasing);

    main_layout->addWidget(m_chart_view, 5, 1);
    m_data_producer->setFrequency(frequency_input->value());
    m_data_producer->setAmplitude(amplitude_input->value());
    m_data_producer->setSampleRate(sample_rate_input->value());

    m_update_rate = update_rate_input->value();
    connect(&m_update_data_timer, SIGNAL(timeout()),
            this, SLOT(produceAndDisplayData()));
}

MainWindow::~MainWindow()
{
    delete m_data_server;
    delete m_data_producer;
}


void MainWindow::on_produceSineDataButton_clicked()
{
    produceAndDisplayData();
}

void MainWindow::on_startButton_clicked()
{
    if (!m_active)
    {
        auto host = host_input->text();
        int port = port_input->value();
        port_input->setDisabled(true);

        m_data_server->startServer(host, port);

        m_update_data_timer.start(1000/m_update_rate);
        m_active = true;
        startButton->setText("Stop");
    }
    else
    {
        m_data_server->stopServer();
        m_update_data_timer.stop();
        m_active = false;

        port_input->setDisabled(false);
        startButton->setText("Start");
    }
}

void MainWindow::produceAndDisplayData()
{
    QTime current_time = QTime::currentTime();
    const auto& data = m_data_producer->getData(m_segment_start_time, current_time);

    m_dataOutputTable->clearContents();
    m_dataOutputTable->setRowCount(data.size());
    int row = 0;

    QLineSeries *series = new QLineSeries();
    series->setName("data");
    //series->setPointsVisible();

    for(const auto& data_point : data)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(
            data_point.first.toString("hh:mm:ss.zzz"));
        m_dataOutputTable->setItem(row, 0, newItem);

        QTableWidgetItem* valueItem = new QTableWidgetItem(tr("%1").arg(data_point.second));
        m_dataOutputTable->setItem(row, 1, valueItem);
        row++;

        double delta_time = data_point.first.msecsSinceStartOfDay(); //- m_start_time.msecsSinceStartOfDay();
        series->append(delta_time, data_point.second);

    }

    m_chart->removeAllSeries();
    m_chart->addSeries(series);
    m_chart->legend()->hide();
    m_chart->setTitle("Chart");
    //m_chart->createDefaultAxes();
    for(auto axis : m_chart->axes())
    {
        m_chart->removeAxis(axis);
    }

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(3);
    axisX->setFormat("hh:mm:ss.zzz");
    axisX->setTitleText("time");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%.1f");
    axisY->setTitleText("[V]");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_segment_start_time = current_time;
}


void MainWindow::on_update_rate_input_valueChanged(int ur)
{
    m_update_rate = ur;
    if (m_update_data_timer.isActive())
    {
        m_update_data_timer.stop();
        m_update_data_timer.start(1000/m_update_rate);
    }
}


void MainWindow::on_sawButton_clicked()
{
    setWaveForm(SAW);
}


void MainWindow::on_sineButton_clicked()
{
    setWaveForm(SINE);
}

void MainWindow::setWaveForm(WaveForm wave_form)
{
    if (wave_form == m_wave_form)
        return;

    auto freq = m_data_producer->getFrequency();
    auto amp = m_data_producer->getAmplitude();
    auto sr = m_data_producer->getSampleRate();
    delete m_data_producer;
    switch(wave_form)
    {
    case SINE:
        m_data_producer = new SineDataProducer{freq, amp, sr};
        break;
    case SAW:
        m_data_producer = new SawToothProducer{freq, amp, sr};
        break;
    default:
        assert(false);
    }
    m_wave_form = wave_form;
}


void MainWindow::on_frequency_input_valueChanged(int freq)
{
    m_data_producer->setFrequency(freq);
}


void MainWindow::on_amplitude_input_valueChanged(double amp)
{
    m_data_producer->setAmplitude(amp);
}


void MainWindow::on_sample_rate_input_valueChanged(int sr)
{
    m_data_producer->setSampleRate(sr);
}

