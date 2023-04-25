#include "mainwindow.h"

#include "netdataproducer.h"

#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(NetDataProducer& producer, QWidget *parent)
    : QMainWindow(parent)
    , m_producer(producer)
{
    setupUi(this);

    m_update_rate = update_rate_input->value();
    connect(&m_update_data_timer, SIGNAL(timeout()),
            this, SLOT(produceAndDisplayData()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_startButton_clicked()
{
    if (!m_active)
    {
        auto host = host_input->text();
        auto port = port_input->value();

        bool connected = m_producer.connect(host, port);

        if (!connected)
        {
            info_label->setText("Connection refused! Please check settings.");
            info_label->setStyleSheet("color: red");
            return;
        }

        m_update_data_timer.start(1000/m_update_rate);
        m_active = true;

        startButton->setText("Stop");
        info_label->setText("Running");
        info_label->setStyleSheet("color: black");

        host_input->setDisabled(true);
        port_input->setDisabled(true);
    }
    else
    {
        m_update_data_timer.stop();
        m_active = false;

        host_input->setDisabled(false);
        port_input->setDisabled(false);
        startButton->setText("Start");

        info_label->setText("Please click \"Start\"!");
        info_label->setStyleSheet("color: black");
    }
}

void MainWindow::produceAndDisplayData()
{
    int duration_msec = m_update_rate ? static_cast<int>(1000 / m_update_rate) : 0;
    const auto& data = m_producer.getData(duration_msec);

    table->clearContents();
    table->setRowCount(data.size());
    int row = 0;

    for(const auto& data_point : data)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(
            data_point.first.toString("hh:mm:ss.zzz"));
        table->setItem(row, 0, newItem);

        QTableWidgetItem* valueItem = new QTableWidgetItem(tr("%1").arg(data_point.second));
        table->setItem(row, 1, valueItem);

        //qDebug() << data_point.first.toString("hh:mm:ss.zzz") << ": " << data_point.second;
        row++;
    }
}


void MainWindow::on_update_rate_input_valueChanged(int arg1)
{
    m_update_rate = arg1;
    if (m_update_data_timer.isActive())
    {
        m_update_data_timer.stop();
    }

    if (m_update_rate > 0)
    {
        m_update_data_timer.start(1000/m_update_rate);
    }
}

